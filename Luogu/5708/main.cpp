#include <cmath>
#include <cstdio>
using namespace std;
int main(void)
{
	double a, b, c; scanf("%lf%lf%lf", &a, &b, &c);
	double p = (a + b + c) / 2;
	printf("%.1lf\n", sqrt(p * (p - a) * (p - b) * (p - c)));
	return 0;
}