#include <stdio.h>

double func(double x) {
	int k;
	double t,res = 0.0;
	
	if(fabs(x)<0.001)
		return 1.644934066848;
	
	for(k=1; ; k++) {
		t = 1.0/k - 1.0/(x+k);
		if(fabs(t/x) < 0.5e-7)
			break;
		res += t;
	}
	res /= x;
	
	return res;
}

int main() {
	double x;
	double psix;
	for(x=0.000; x<=2.000; x+=0.001) {
		psix = func(x);
		printf("%5.3f %16.12f\n", x, psix);
	}

	return 0;
}
