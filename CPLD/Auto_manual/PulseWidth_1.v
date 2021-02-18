module PulseWidth_1(clk, en, PulIn, d);
input clk, en, PulIn;
output [7:0] d;

reg [7:0] d = 8'h00, temp = 8'h00;
reg pre_PulIn, pre_en;

always @ (posedge clk)
begin
	pre_PulIn <= PulIn;
	pre_en <= en;
	if (en)
	begin
		if ({pre_PulIn, PulIn} == 2'b01)
			temp = 0;
		else if ({pre_PulIn, PulIn} == 2'b10)
			d = temp;
		else if ({pre_PulIn, PulIn} == 2'b11)
			temp = temp + 1;
	end
	if ({pre_en, en} == 2'b10)
	begin
		d = temp;
		temp = 0;
	end
end
endmodule
