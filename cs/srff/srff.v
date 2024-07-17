module SRFF(input r, clock, s, output q, q_dot);
    wire r_out, s_out;
    assign r_out = r & clock;
    assign s_out = s & clock;
    assign q = ~(q_dot | r_out);
    assign q_dot = ~(q | s_out);
endmodule

module SRFF_Test();
    reg r = 0, s = 1, clock = 0;
    wire q, q_dot;
    SRFF srff(r, clock, s, q, q_dot);
    initial begin
        #10 s = 1;
        clock = 1;
        #10 clock = 1;
        s = 0;
        clock = 0;
        #10 clock = 1;
        #10 s = 1;
        clock = 0;
        #10 clock = 1;
    end
    initial begin
        $monitor("r = %x s = %x clock = %x, q = %x, q_dot = %x", r, s, clock, q, q_dot);
    end
endmodule