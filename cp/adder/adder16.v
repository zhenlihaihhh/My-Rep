module FullAdder(input a, b, c, output carry, sum);
    wire s1, c1, c2;
    assign s1 = a ^ b;
    assign c1 = a & b;
    assign c2 = s1 & c;
    assign carry = c1 | c2;
    assign sum = c ^ s1;
endmodule
module Bit_Adder_16(input[15:0] a, b, output[15:0] sum);
    wire[15:0] c;
    FullAdder g0(a[0], b[0], 1'b0, c[0], sum[0]);
    genvar i;
    generate
        for(i = 1;i < 16;i = i + 1)
        begin
            FullAdder g(a[i], b[i], c[i - 1], c[i], sum[i]);
        end
    endgenerate
endmodule

module Bit_Adder_16_Test();
    reg signed [15:0] a, b;
    wire signed [15:0] out;
    Bit_Adder_16 obj(a, b, out);
    initial begin
      a = 16'h0001;
      b = 16'h0213;
      #10 b = 16'h0001;
      #10 a = 16'h1331;
          b = 16'h0321;
      #10 a = 16'h8001;
          b = 16'h8003;
      #10 a = 1;
          b = -5;
    end
    initial begin
        $monitor("%x + %x = %x, %d + %d = %d", a, b, out, a, b, out);
        // 8001 + 8003 = 0004 溢出了
    end
endmodule