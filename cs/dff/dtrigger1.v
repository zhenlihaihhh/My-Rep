module SRFF(input r, clock, s, output q, q_dot);
    wire r_out, s_out;
    assign r_out = r & clock;
    assign s_out = s & clock;
    assign q = ~(q_dot | r_out);
    assign q_dot = ~(q | s_out);
endmodule

module D_Trigger1(input d, clk, output q, q_dot);
    wire d_dot, clk_dot, q1, q1_dot, s_out, r_out;
    assign clk_dot =  ~clk;
    assign d_dot = ~d;
    assign s_out = d_dot & clk_dot;
    assign r_out = d & clk_dot;
    assign q1 = ~(r_out | q1_dot);
    assign q1_dot = ~(s_out | q1);
    SRFF srff(q1, clk, q1_dot, q, q_dot);
endmodule


module D_TRigger_Test();
    reg D = 1, Clk = 0;
    wire q, q_dot;
    D_Trigger1 d_trigger(D, Clk, q, q_dot);
    initial begin
        #22 Clk = 1;
        #22 D = 0;
        #22 D = 0;
        Clk = 0;
        #22 Clk = 1;
        #22 D = 1;
    end
    initial begin
        $monitor("D = %x clk = %x q = %x q_dot = %x", D, Clk, q, q_dot);
    end
endmodule