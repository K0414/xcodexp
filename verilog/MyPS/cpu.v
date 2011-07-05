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
