module FullAdder(input a, b, c, output carry, sum);
    wire s1, c1, c2;
    assign s1 = a ^ b;
    assign c1 = a & b;
    assign c2 = s1 & c;
    assign carry = c1 | c2;
    assign sum = c ^ s1;
endmodule

module FullAdder_Test();
    reg a = 0, b = 0, c = 0;
    wire carry, sum;
    FullAdder fullAdder(a, b, c, carry, sum);
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
        $monitor("a = %d, b = %d, c = %d, carry = %d, sum = %d", a, b, c, carry, sum);
    end
endmodule