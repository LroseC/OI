#include <cmath>
#include <ctime>
#include <random>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 1e5 + 10;
const double eps = 1e-12;
const double pi = 3.141592653589793238462643383;

struct PDD
{
	double x, y;
	PDD operator+(const PDD &b) const
	{
		return {x + b.x, y + b.y};
	}
	PDD operator-(const PDD &b) const
	{
		return {x - b.x, y - b.y};
	}
};
struct Line
{
	PDD st, ed;
};
struct Circle
{
	PDD p; double r;
};
PDD operator*(double a, PDD b)
{
	return {a * b.x, a * b.y};
}
int sign(double x)
{
	if (fabs(x) < eps) return 0;
	if (x < 0) return -1;
	return 1;
}
int cmp(double a, double b)
{
	return sign(a - b);
}
double dot(PDD a, PDD b)
{
	return a.x * b.x + a.y * b.y;
}
double cross(PDD a, PDD b)
{
	return a.x * b.y - a.y * b.x;
}

double get_len(PDD x)
{
	return sqrt(dot(x, x));
}
PDD get_intersection(PDD p, PDD v, PDD q, PDD w)
{
	PDD u = p - q;
	double t = cross(u, w) / cross(w, v);
	return p + t * v;
}
bool out_circle(Circle c, PDD p)
{
	return cmp(get_len(p - c.p), c.r) > 0;
}
PDD rotate(PDD a, double theta)
{
	return {a.x * cos(theta) + a.y * sin(theta), a.y * cos(theta) - a.x * sin(theta)};
}
Line get_midline(Line x)
{
	PDD st = 0.5 * (x.st + x.ed);
	PDD v = rotate(x.ed - x.st, pi / 2);
	return {st, st + v};
}
PDD get_intersection(Line a, Line b)
{
	return get_intersection(a.st, a.ed - a.st, b.st, b.ed - b.st);
}
Circle get_circle(PDD a, PDD b, PDD c)
{
	auto u = get_midline({a, b}), v = get_midline({b, c});
	PDD p = get_intersection(u, v);
	double r = get_len(p - a);
	return {p, r};
}

int n;
PDD q[N];

int main(void)
{
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) scanf("%lf%lf", &q[i].x, &q[i].y);
	mt19937 myrand(time(NULL));
	shuffle(q + 1, q + 1 + n, myrand);
	Circle c({q[1], 0});
	for (int i = 1; i <= n; ++i) {
		if (out_circle(c, q[i])) {
			c = Circle({q[i], 0});
			for (int j = 1; j < i; ++j)
				if (out_circle(c, q[j])) {
					c = Circle({0.5 * (q[i] + q[j]), 0.5 * get_len(q[i] - q[j])});
					for (int k = 1; k < j; ++k)
						if (out_circle(c, q[k]))
							c = get_circle(q[i], q[j], q[k]);
				}
		}
	}
	printf("%.10lf\n", c.r);
	printf("%.10lf %.10lf\n", c.p.x, c.p.y);
	return 0;
}