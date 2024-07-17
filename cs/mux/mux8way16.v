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
module Mux8Way16(input[15:0] a, b, c, d, e, f, g, h, input[2:0] sel, output[15:0] out);
    wire[15:0] outad, outeh;
    Mux_4_Way_16 g1(a, b, c, d, sel[1:0], outad);
    Mux_4_Way_16 g2(e, f, g, h, sel[1:0], outeh);
    Mux_16 mux(outad, outeh, sel[2], out);
endmodule