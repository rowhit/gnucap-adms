// these devices are provided by the simulator and need
// not be implemented
`include "discipline.h"

module vsource(p,n);
   inout p,n;
   electrical p,n;
   parameter real dc=0. from [0:inf);
endmodule

module capacitor(p,n);
   inout p,n;
   electrical p,n;
   parameter real c=0. from [0:inf);
endmodule

module R(p,n);
   inout p,n;
	electrical p,n;

	parameter real r=1e3 from [0:inf);
endmodule

module C(p,n);
   inout p,n;
	electrical p,n;

	parameter real c=1e-6 from [0:inf);
endmodule

module L(p,n);
   inout p,n;
	electrical p,n;

	parameter real l=1e-6 from [0:inf);
endmodule

// `ifdef USE_DEGR (FIXME, check gnucap capabilities)
module rcd_exp(p, n, e);
	inout p, n;
	output e;
	electrical p, n;
	degradational e;

	parameter real weight=1 from (0:inf);
	parameter real re1=1e3 from [0:inf);
	parameter real re0=1e3 from (-inf:inf);
	parameter real rc1=1e3 from (-inf:0];
	parameter real rc0=1e3 from (-inf:inf);
endmodule
// `endif
