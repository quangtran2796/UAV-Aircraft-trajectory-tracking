module Switch_Mode(clk, RCV_Chan1, RCV_Chan2, RCV_Chan3, RCV_Chan4, MCU_Chan1, MCU_Chan2, MCU_Chan3, MCU_Chan4, PulWid_En, PulWid_Alter, Chan1, Chan2, Chan3, Chan4, Trigger, Alter);
input clk, RCV_Chan1, RCV_Chan2, RCV_Chan3, RCV_Chan4, MCU_Chan1, MCU_Chan2, MCU_Chan3, MCU_Chan4;
input [7:0] PulWid_En, PulWid_Alter;
output Chan1, Chan2, Chan3, Chan4, Trigger, Alter;

reg [19:0] count = 0;
reg Trigger = 0, flag = 0, pre_flag = 0, wait_flag = 0, Alter;

always @ (posedge clk)
begin
	if (PulWid_Alter >= 150)
		Alter = 1;
	else
		Alter = 0;
	pre_flag <= flag;
	if (PulWid_En >= 150) 
		flag = 1;
	else 
	begin
		flag = 0;
		Trigger = 0;
	end
	if ({pre_flag, flag} == 2'b01) 
		wait_flag = 1;
	if (wait_flag)
		if (count >= 5)
		begin
			count = 0;
			Trigger = 1;
			wait_flag = 0;
		end
		else count = count + 1;	
end

assign Chan1 = (Trigger == 0) ? RCV_Chan1 : MCU_Chan1;
assign Chan2 = (Trigger == 0) ? RCV_Chan2 : MCU_Chan2;
assign Chan3 = (Trigger == 0) ? RCV_Chan3 : MCU_Chan3;
assign Chan4 = (Trigger == 0) ? RCV_Chan4 : MCU_Chan4;
//assign Chan1 = MCU_Chan1;
//assign Chan2 = MCU_Chan2;
//assign Chan3 = MCU_Chan3;
//assign Chan4 = MCU_Chan4;

endmodule
