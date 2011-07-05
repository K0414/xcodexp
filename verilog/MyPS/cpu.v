'timescale 1ns/10ps

module system;
wire clock, reset;

cpu cpu00(.clock(clock)), .reset(reset));

initial clock<=1'b0;
always #20 clock=~clock;

initial
begin
    #0 reset<=1'b1;
    #70 reset<=1'b0;
end

endmodule

module cpu(clock, reset);
input clock;
input reset;

wire [17:0] brbus;
wire [15:0] inst;
wire [2:0] ex_dest, mem_dest, wb_dest;
wire [19:0] wbbus;
wire [55:0] idbus;
wire [39:0] exbus;
wire [39:0] membus;

fetch_module fetch(.clock(clock), .reset(reset), .brbus(brbus), .inst(inst));

decode_module decode(.clock(clock), .reset(reset), .inst(inst),
		.ex_dest(ex_dest), .mem_dest(mem_dest), .wb_dest(wb_dest),
		.wbbus(wbbus), .brbus(brbus), .idbus(idbus));

alu_module alu(.clock(clock), .reset(reset), .idbus(idbus), .exbus(exbus),
		.ex_dest(ex_dest));

mem_module mem(.clock(clock), .reset(reset), .exbus(exbus), .membus(membus),
		.mem_dest(mem_dest));

wb_module wb(.clock(clock), .reset(reset), .membus(membus), .wbbus(wbbus),
		.wb_dest(wb_dest));

endmodule


'timescale 1ns/10ps
module fetch_module(clock, reset, brbus, inst);
input clock;
input reset;
input [17:0] brbus;
output [15:0] inst;

reg [15:0] pc;

wire brbus_valid;
wire brbus_taken;
wire [15:0] brbus_offset;

assign brbus_valid = brbus[17];
assign brbus_taken = brbus[16];
assign brbus_offset = brbus[15:0];

// fetch_module transaction

endmodule


'timescale 1ns/10ps
module decode_module(clock, reset, inst, ex_dest, mem_dest, wb_dest, wbbus,
		brbus, idbus);
input clock;
input reset;
input [15:0] inst;
input [2:0] ex_dest, mem_dest, wb_dest;
input [19:0] wbbus;
output [55:0] idbus;
output [17:0] brbus;
reg [15:0] ir;

wire wbbus_valid;
wire [2:0] wbbus_dest;
wire [15:0] wbbus_value;

wire idbus_valid;
wire [3:0] idbus_op;
wire [2:0] idbus_dest;
wire [15:0] idbus_value1;
wire [15:0] idbus_value2;
wire [15:0] idbus_stvalue;

wire brbus_valid;
wire brbus_taken;
wire [15:0] brbus_offset;

assign wbbus_valid=wbbus[19];
assign wbbus_dest=wbbus[18:16];
assign wbbus_value=wbbus[15:0];

// decode_module transaction

assign brbus[17]=brbus_valid;
assign brbus[16]=brbus_taken;
assign brbus[15:0]=brbus_offset;

assign idbus[55]=idbus_valid;
assign idbus[54:51]=idbus_op;
assign idbus[50:48]=idbus_dest;
assign idbus[47:32]=idbus_value1;
assign idbus[31:16]=idbus_value2;
assign idbus[15:0]=idbus_stvalue;

endmodule


'timescale 1ns/10ps
module alu_module(clock, reset, idbus, exbus, ex_dest);
input clock;
input reset;
input [55:0] idbus;
output [29:0] exbus;
output [2:0] ex_dest;

wire idbus_valid;
wire [3:0] idbus_op;
wire [2:0] idbus_dest;
wire [15:0] idbus_value1;
wire [15:0] idbus_value2;
wire [15:0] idbus_stvalue;

wire exbus_valid;
wire [3:0]exbus_op;
wire [2:0]exbus_dest;
wire [15:0]exbus_exresult;
wire [15:0]exbus_stvalue;

assign idbus_valid=idbus[55];
assign idbus_op=idbus[54:51];
assign idbus_dest=idbus[50:48];
assign idbus_value1=idbus[47:32];
assign idbus_value2=idbus[31:16];
assign idbus_stvalue=idbus[15:0];

// alu_module transaction

assign exbus[39]=exbus_valid;
assign exbus[38:35]=exbus_op;
assign exbus[34:32]=exbus_dest;
assign exbus[31:16]=exbus_exresult;
assign exbus[15:0]=exbus_stvalue;

endmodule


'timescale 1ns/10ps
module mem_decode(clock, reset, exbus, membus, mem_dest);
input clock;
input reset;
input [39:0] exbus;
output [39:0] membus;
output [2:0] mem_dest;

wire exbus_valid;
wire [3:0] exbus_op;
wire [2:0] exbus_dest;
wire [15:0] exbus_exresult;
wire [15:0] exbus_stvalue;

wire membus_valid;
wire [3:0] membus_op;
wire [2:0] membus_dest;
wire [15:0] membus_exresult;
wire [15:0] membus_memvalue;

assign exbus_valid=exbus[39];
assign exbus_op=exbus[38:35];
assign exbus_dest=exbus[34:32];
assign exbus_exresult=exbus[31:16];
assign exbus_stvalue=exbus[15:0];

// mem_module transaction

assign membus[39]=membus_valid;
assign membus[38:35]=membus_op;
assign membus[34:32]=membus_dest;
assign membus[31:16]=membus_exresult;
assign membus[15:0]=membus_stvalue;

endmodule


'timescale 1ns/10ps
module wb_module(clock, reset, membus, wbbus, wb_dest);
input clock;
input reset;
input [39:0] membus;
output [19:0] wbbus;
output [2:0] wb_dest;

wire membus_valid;
wire [3:0] membus_op;
wire [2:0] membus_dest;
wire [15:0] membus_exresult;
wire [15:0] membus_memresult;

wire wbbus_valid;
wire [2:0] wbbus_dest;
wire [15:0] wbbus_value;

assign membus_valid=membus[39];
assign membus_op=membus[38:35];
assign membus_dest=membus[34:32];
assign membus_exresult=membus[31:16];
assign membus_memresult=membus[15:0];

// wb_module transaction

assign wbbus[19]=wbbus_valid;
assign wbbus[18:16]=wbbus_dest;
assign wbbus[15:0]=wbbus_value;

endmodule


'timescale 1ns/10ps
module rom(raddr, rout);
input [11:0] raddr;
output [15:0] rout;

reg [15:0] rom[4095:0];
integer i;
initial
begin
		$readmemb("rom.vlog", rom);
		$display("\nLoad rom successfully!! \n\n");
end
assign rout = rom[raddr];

endmodule


'timescale 1ns/10ps
module ram(clock, raddr, rout, wen, waddr, win);
input clock;
input wen;
input [15:0] win;
input [11:0] raddr;
input [11:0] waddr;
output [15:0] rout;

reg [15:0] ram[4095:0];
assign rout = ram[raddr];

always @(posedge clock)
begin
		if (wen)
		begin
				ram[waddr] = win;
		end
end

endmodule


'timescale 1ns/10ps
module regfile(clock, raddr1, rout1, raddr2, rout2, wen, waddr, win);
input clock;
input wen;
input [15:0] win;
input [2:0] raddr1, raddr2;
input [2:0] waddr;
output [15:0] rout1, rout2;

reg [15:0] ram[7:0];
assign rout1 = ram[raddr1];
assign rout2 = ram[raddr2];

always @(posedge clock)
begin
		ram[0] <= 16'b0;
		if (wen)
		begin
				if (waddr != 0)
						ram[waddr] <= win;
		end
end

endmodule
