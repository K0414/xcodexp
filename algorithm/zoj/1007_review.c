/*********************************************************************
y(x) - y(1) = ¡Æ[(1-x)/(k*(k+x)*(k+1))]
*********************************************************************/

#include <stdio.h>

double func(double x) {
	int k;
	double res = 0.0;
	
	// why 10000 ?
	for(k=1; k<10000; k++) {
		res += (1-x) / (k*(k+x)*(k+1));
	}
	// ?
	res += (1-x) / (2*10000*10000) + 1;
	
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
