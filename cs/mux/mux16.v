module Mux(input a, b, select, output out);
    assign out = a&(~select) | b&select;
endmodule

module Mux_16(input[15:0] a, b,input select, output[15:0] out);
    genvar i;
    generate
        for(i = 0;i < 16;i = i + 1)
        begin
          Mux m(a[i], b[i], select, out[i]);
        end
    endgenerate
endmodule
module Mux_16_Test();
    reg[15:0] a, b;
    reg select;
    wire[15:0] out;
    Mux_16 m1(a, b, select, out);
    initial begin
        a = 16'h0001;
        b = 16'h1232;
        select = 0;
        #10 select = 1;
    end
    initial begin
        $monitor("a = %x b = %x select = %x out = %x", a, b, select, out);
    end
endmodule