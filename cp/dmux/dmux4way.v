module Dmux(input in, sel, output a, b);
    assign a = in &  (~sel);
    assign b = in & sel;
endmodule


module Dmux_4_Way(input in, input[1:0] sel, output a, b, c, d);
    assign a = in & (~sel[0]) & (~sel[1]);
    assign b = in & (~sel[0]) & sel[1];
    assign c = in & sel[0] & (~sel[1]);
    assign d = in & sel[0] & sel[1];
endmodule
