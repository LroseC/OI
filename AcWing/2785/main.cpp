#include <cmath>
#include <random>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 5e4 + 10;
const double eps = 1e-12;
const double pi = 3.141592653589793238462643383;

struct PDD
{
	double x, y;
	inline PDD operator+(const PDD &b) const
	{
		return {x + b.x, y + b.y};
	}
	inline PDD operator-(const PDD &b) const
	{
		return {x - b.x, y - b.y};
	}
};
inline PDD operator*(double a, const PDD &b)
{
	return {a * b.x, a * b.y};
}
struct Line
{
	PDD st, ed;
};
struct Circle
{
	PDD p; double r;
};
inline int sign(double x)
{
	if (fabs(x) < eps) return 0;
	if (x < 0) return -1;
	return 1;
}
inline int cmpd(double a, double b)
{
	return sign(a - b);
}
inline double dot(PDD a, PDD b)
{
	return a.x * b.x + a.y * b.y;
}
inline double cross(PDD a, PDD b)
{
	return a.x * b.y - a.y * b.x;
}
inline double get_len(PDD a)
{
	return sqrt(dot(a, a));
}
inline PDD rotate(PDD a, double theta)
{
	return {a.x * cos(theta) + a.y * sin(theta), a.y * cos(theta) - a.x * sin(theta)};
}
inline bool out_circle(Circle c, PDD p)
{
	return cmpd(get_len(p - c.p), c.r) > 0;
}
inline PDD get_intersection(PDD p, PDD v, PDD q, PDD w)
{
	PDD u = p - q;
	double t = cross(u, w) / cross(w, v);
	return p + t * v;
}
inline PDD get_intersection(Line a, Line b)
{
	return get_intersection(a.st, a.ed - a.st, b.st, b.st - b.ed);
}
inline Line get_midline(Line a)
{
	PDD st = 0.5 * (a.st + a.ed);
	PDD v = rotate(a.ed - a.st, pi / 2);
	return {st, st + v};
}
inline Circle get_circle(PDD a, PDD b, PDD c)
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
	double a, p;
	scanf("%lf%lf", &a, &p);
	for (int i = 1; i <= n; ++i) {
		q[i] = rotate(q[i], a / 180 * pi);
		q[i].x /= p;
	}
	mt19937 myrand(time(NULL));
	shuffle(q + 1, q + 1 + n, myrand);
	Circle c({q[1], 0});
	for (int i = 1; i <= n; ++i)
		if (out_circle(c, q[i])) {
			c = {q[i], 0};
			for (int j = 1; j < i; ++j)
				if (out_circle(c, q[j])) {
					c = {0.5 * (q[i] + q[j]), 0.5 * get_len(q[j] - q[i])};
					for (int k = 1; k < j; ++k) {
						if (out_circle(c, q[k]))
							c = get_circle(q[i], q[j], q[k]);
					}
				}
		}

	printf("%.3lf\n", c.r);
	return 0;
}