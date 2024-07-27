module DFF(input clock, data, output q, q_dot);
    wire d_bar, s_out, r_out;
    assign d_bar = ~data;
    assign s_out = data & clock;
    assign r_out = d_bar & clock;
    assign q = ~(q_dot | r_out);
    assign q_dot = ~(q | s_out);
endmodule

module DFF_Test();
    reg data = 0, clk = 1;
    wire q, q_dot;
    DFF dff(clk, data, q, q_dot);
    initial begin
        #10
        #10
        #10
        #10
        data = 1;
        #10 clk = 0;
        #10 clk = 1;
        #10 data = 0;

    end
    initial begin
        $monitor("data = %x clk = %x q = %x q_dot = %x", data, clk, q, q_dot);
    end
endmodule