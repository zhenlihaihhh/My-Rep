module SRFF(input r, clock, s, output q, q_dot);
    wire r_out, s_out;
    assign r_out = r & clock;
    assign s_out = s & clock;
    assign q = ~(q_dot | r_out);
    assign q_dot = ~(q | s_out);
endmodule

module Mux(input a, b, sec, output out);
    assign out = a&(~sec) | b&sec;
endmodule

module D_Trigger(input d, clk, load, output q, q_dot);
    wire in, d_dot, clk_dot, q1, q1_dot, s_out, r_out;
    Mux mux(q, d, load, in);
    assign clk_dot =  ~clk;
    assign d_dot = ~in;
    assign s_out = d_dot & clk_dot;
    assign r_out = in & clk_dot;
    assign q1 = ~(r_out | q1_dot);
    assign q1_dot = ~(s_out | q1);
    SRFF srff(q1, clk, q1_dot, q, q_dot);
endmodule

module Register(input[15:0] in, input clk, load, output[15:0] out);
    wire[15:0] out_dot;
    generate
        genvar i;
        for(i = 15;i >= 0; i = i - 1)
        begin
            D_Trigger g(in[i], clk, load, out[i], out_dot[i]);
        end
    endgenerate
endmodule

module Register_Test();
    reg[15:0] D = 16'h0000;
    reg Clk = 0, load = 0;
    wire[15:0] out;
    Register register(D, Clk, load, out);
    initial begin
        #10 load = 1;
        #10 D = 16'h0100;
        #10 Clk = 1;
        #10 D = 16'h0132;
        #10 Clk = 0;
        #10 load = 0;
        #10 Clk = 1;
        #10 load = 1;
        #10 Clk = 0;
        #10 Clk = 1;
    end
    initial begin
        $monitor("D = %x clk = %x load = %x out = %x ", D, Clk, load, out);
    end
endmodule