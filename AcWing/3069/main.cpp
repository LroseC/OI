#include <cmath>
#include <cstdio>
#include <algorithm>

using namespace std;

const int N = 1010;
const double eps = 1e-8;

int sign(double x)
{
	if (fabs(x) < eps) return 0;
	return x < 0 ? -1 : 1;
}
int cmpd(double a, double b)
{
	return sign(a - b);
}
struct PDD
{
	double x, y;
	bool operator<(const PDD &b) const
	{
		return x == b.x ? y < b.y : x < b.x;
	}
};

struct Circle
{
	double x, y;
	double R;
};

int n;
Circle c[N];
PDD q[N];

double f(double x)
{
	int cnt = 0;
	for (int i = 1; i <= n; ++i) {
		double d = fabs(c[i].x - x), R = c[i].R;
		if (cmpd(d, R) < 0) {
			double len = sqrt(R * R - d * d);
			q[++cnt] = {c[i].y - len, c[i].y + len};
		}
	}
	if (!cnt) return 0;
	sort(q + 1, q + 1 + cnt);
	double res = 0;
	double st = q[1].x, ed = q[1].y;
	for (int i = 2; i <= cnt; ++i) {
		if (ed >= q[i].x) ed = max(q[i].y, ed);
		else {
			res += ed - st;
			st = q[i].x;
			ed = q[i].y;
		}
	}
	return res + ed - st;
}
double calc(double l, double r)
{
	double mid = (l + r) / 2;
	return (f(l) + 4 * f(mid) + f(r)) / 6 * (r - l);
}
double sinpson(double l, double r, double S)
{
	double mid = (l + r) / 2;
	double left = calc(l, mid), right = calc(mid, r);
	if (fabs(S - left - right) < eps) return left + right;
	return sinpson(l, mid, left) + sinpson(mid, r, right);
}

int main(void)
{
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%lf%lf%lf", &c[i].x, &c[i].y, &c[i].R);
	}
	printf("%.3lf\n", sinpson(-2000.0, 2000.0, calc(-2000.0, 2000.0)));
	return 0;
}