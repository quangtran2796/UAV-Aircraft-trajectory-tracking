module DataOut_MUX(en1, en2, en3, en4, d1, d2, d3, d4, dout);
input en1, en2, en3, en4;
input [7:0] d1, d2, d3, d4;
output [7:0] dout;

reg [7:0] dout;

always @ (en1 or en2 or en3 or en4)
begin
	case ({en1, en2, en3, en4})
		4'b1000: dout = d1;
		4'b0100: dout = d2;
		4'b0010: dout = d3;
		4'b0001: dout = d4;
		default: dout = 8'hzz;
	endcase
//	if (en2)
//		dout = d2;
//	else
//		dout = 8'hzz;
end
endmodule
