
module Mux(input a, b, sec, output out);
    assign out = a&(~sec) | b&sec;
endmodule

module Mux_Test();
    reg a = 0, b = 0, c = 0;
    wire out;
    Mux m(a, b, c, out);
    initial begin
      #10 c = 1;
      #10 b = 1;
      c = 0;
      #10 c = 1;
      b = 1;
      #10 a = 1;
      b = 0;
      c = 0;
      #10 c = 1;
      #10 b = 1;
      c = 0;
      #10 c = 1;
    end
    initial begin
      $monitor("a = %x b = %x sec = %x out = %x", a, b, c, out);
    end
endmodule