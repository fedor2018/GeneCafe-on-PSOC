
//`#start header` -- edit after this line, do not edit this line
// ========================================
//
// Copyright YOUR COMPANY, THE YEAR
// All Rights Reserved
// UNPUBLISHED, LICENSED SOFTWARE.
//
// CONFIDENTIAL AND PROPRIETARY INFORMATION
// WHICH IS THE PROPERTY OF your company.
//
// ========================================
`include "cypress.v"
//`#end` -- edit above this line, do not edit this line
// Generated on 03/20/2019 at 08:43
// Component: btn_press
module btn_press (
	output reg end_b,
	input   clk,
	input   start,
	input   stop,
	output  reg [7:0] cnt
);

//reg end_p=1'b0;
//`#start body` -- edit after this line, do not edit this line
//reg [7:0] cnt;
always @(posedge clk) begin
    if(start) begin
        end_b=1'b0;
        cnt=8'b0;
    end
    if(stop || cnt==8'hFF)begin
        end_b=1'b1;
    end
    if(end_b==1'b0) begin
        cnt=cnt+8'b1;
    end
end
//        Your code goes here

//`#end` -- edit above this line, do not edit this line
endmodule
//`#start footer` -- edit after this line, do not edit this line
//`#end` -- edit above this line, do not edit this line
