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

module D_Trigger_Test();
    reg in = 1, clk = 0, load = 1;
    wire q, q_dot;
    D_Trigger d_trigger(in, clk, load, q, q_dot);
    initial begin
        #10 clk = 1;
        #10 in = 0;
        #10 clk = 0;
        #10 clk = 1;
        #10 load = 0;
        #10 in = 0;
        clk = 1;
        #10 in = 1;
        clk = 0;
        #10 clk = 1;
    end
    initial begin
        $monitor("in = %x clk = %x load = %x out = %x", in, clk, load, q);
    end
endmodule