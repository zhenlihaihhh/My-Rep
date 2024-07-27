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

module Mux_4_Way_16(input[15:0] a, b, c, d, input[1:0] select, output[15:0] out);
    wire[15:0] outab, outcd;
    Mux_16 m1(a, b, select[0], outab);
    Mux_16 m2(c, d, select[0], outcd);
    Mux_16 m3(outab, outcd, select[1], out);
endmodule


module Mux_4_Way_16_Test();
    reg[15:0] a, b, c, d;
    reg[1:0] s = 2'b00;
    wire[15:0] out; 
    Mux_4_Way_16 m2(a, b, c, d, s, out);
    initial begin
        a = 16'h0001;
        b = 16'h1232;
        c = 16'h1111;
        d = 16'h1001;
        #10 s = 2'b01;
        #10 s = 2'b10;
        #10 s = 2'b11;
    end
    initial begin
        $monitor("a = %x b = %x c = %x d = %x s = %x out = %x", a, b, c, d, s, out);
    end
endmodule