#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

double objectFunct(double x)
{
	return x*x*x*x - 4*x*x + 5;
}

double minimum_sa(double (*objectFunction)(double x), double x1, double x2)
{
	double x = x2;
	double T = 10000;
	double delta = 0;
	double df = 0;
	double p = 0;
	int i = 0;
	while (T > 0.00001) {
		for (i = 0; i < 10; i++) {
			delta = (double)(rand() % 10000 - rand() % 10000) / 10000;
			df = objectFunction(x) - objectFunction(x + delta);
			if (df > 0) {
				x = x + delta;
			} else {
				if (p > exp(-1 * df / T)) {
					x = x + delta;
				}
			}
		}
		T = 0.98 * T;
	}
	return x;
}
int main()
{
	double x = 0;
	double y = 0;
	x = minimum_sa(objectFunct, 0, 1000);
	y = objectFunct(x);
	printf("x = %lf    y = % lf\n", x, y);
	return 0;
}
