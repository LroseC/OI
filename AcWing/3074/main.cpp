#include <cmath>
#include <cstdio>

using namespace std;

const double eps = 1e-12;

double f(double x)
{
	return sin(x) / x;
}

double calc(double l, double r)
{
	double mid = (l + r) / 2;
	return (f(l) + 4 * f(mid) + f(r)) / 6 * (r - l);
}

double sinpson(double l, double r)
{
	double Sp = (calc(l, r));
	double mid = (l + r) / 2;
	double Sq = calc(l, mid) + calc(mid, r);
	if (fabs(Sp - Sq) < eps) return Sq;
	return sinpson(l, mid) + sinpson(mid, r);
}

int main(void)
{
	double l, r;
	scanf("%lf%lf", &l, &r);
	printf("%lf\n", sinpson(l, r));
	return 0;
}