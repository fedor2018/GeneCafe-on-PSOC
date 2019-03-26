/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "beep.h"

//#define BEEP_DEBUG
uint16 delayl=0;
uint8 delayn=0;

void read_buz(char *s){
#ifdef BEEP_DEBUG
    extern char buf[21];
    sprintf(buf, "%s: %d,%d,%d %d-%d\r\n", s, 
        (uint16)BUZZER_ReadPeriod(),
        (uint16)BUZZER_ReadCounter(),
        (uint16)BUZZER_ReadStatus(),
        Pin_Buzzer_Read(),
        Pin_Led_Read());
    UART_UartPutString(buf);
#endif
}

int beep_stat(){
    if(BUZZER_ReadStatus()==BUZZER_STATUS_RUNNING || delayl>0){
        return 1;
    }
    return 0;
}

void beep_init(){
    BEEP_OFF;
    BUZZER_Init();
    read_buz("s");
    isr_BUZ_StartEx(ISR_BUZ_Handler);
}

void beep_set(uint16 delay){
    BUZZER_WritePeriod(1);
    BUZZER_WriteCounter(BEEP_DELAY_ms(delay));//
}

void beepn(uint16 delay, uint8 num){
    if(beep_stat()){
        return;
    }
    delayl=delay;
    delayn=num;
    beep_set(delayl);
    BEEP_ON;
    BUZZER_Start();
}

void beep(uint16 delay){
    beepn(delay,0);
}

CY_ISR(ISR_BUZ_Handler){
//    read_buz("i");
    BUZZER_ClearInterrupt(BUZZER_INTR_MASK_TC);
    if(BEEP_IS_ON){
        BEEP_OFF;
        if(delayn>0){
            beep_set(delayl);
            BUZZER_Start();
        }
    }else{
        if(delayn>0){
            delayn--;
            beep_set(delayl);
            BEEP_ON;
            BUZZER_Start();
        }
    }
}

/* [] END OF FILE */
