module HalfAdder(input a,
                input b ,
                output carry,
                output sum);
    assign carry = a & b;
    assign sum = a ^ b;
endmodule

module HalfAdder_Test();
    reg a = 0, b = 0;
    wire carry, sum;
    HalfAdder halfAdder(a, b , carry, sum);
    initial begin
      #10 b = 1;
      #10 b = 0;
      a = 1;
      #10 b = 1;
    end
    initial begin
        $monitor("a = %d, b = %d, carry = %d, sum = %d", a, b, carry, sum);
    end
endmodule