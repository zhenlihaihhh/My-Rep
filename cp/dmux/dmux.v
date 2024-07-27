module Dmux(input in, sel, output a, b);
    assign a = in &  (~sel);
    assign b = in & sel;
endmodule


module Dmux_Test();
    reg in = 0, sel = 0;
    wire a, b;
    Dmux dmux(in, sel, a, b);
    initial begin
      #10 sel = 1;
      #10 sel = 0;
      in = 1;
      #10 sel = 1;
    end
    initial begin
        $monitor("in = %x sel = %x a = %x b = %x", in, sel, a, b);
    end
endmodule