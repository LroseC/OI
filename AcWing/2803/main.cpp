#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 20, M = 510;
const double eps = 1e-8;

int cmpd(double a, double b)
{
	if (fabs(a - b) < eps) return 0;
	if (a < b) return -1;
	else return 1;
}
int sign(double x)
{
	if (fabs(x) < eps) return 0;
	if (x < 0) return -1;
	return 1;
}

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
PDD operator*(double a, PDD x)
{
	return {a * x.x, a * x.y};
}
double dot(PDD a, PDD b)
{
	return a.x * b.x + a.y * b.y;
}
double cross(PDD a, PDD b)
{
	return a.x * b.y - a.y * b.x;
}
struct Line
{
	PDD st, ed;
};
PDD get_intersection(PDD p, PDD v, PDD q, PDD w)
{
	auto u = p - q;
	double t = cross(u, w) / cross(w, v);
	return p + t * v;
}
PDD get_intersection(Line a, Line b)
{
	return get_intersection(a.st, a.ed - a.st, b.st, b.ed - b.st);
}
double get_angle(PDD a)
{
	return atan2(a.y, a.x);
}
bool cmp(Line a, Line b)
{
	double A = get_angle(a.ed - a.st), B = get_angle(b.ed - b.st);
	if (!cmpd(A, B)) return sign(cross(b.ed - a.st, a.ed - a.st)) > 0;
	return (A < B);
}
bool on_right(Line x, PDD point)
{
	return sign(cross(point - x.st, x.ed - x.st)) > 0;
}
bool on_right(Line x, Line a, Line b)
{
	auto t = get_intersection(a, b);
	return on_right(x, t);
}

int n, m, cnt;
PDD ans[10010];
PDD pt[52];
Line line[M];
int q[M];

double half_plain_intersection(void)
{
	sort(line + 1, line + 1 + cnt, cmp);
	int hh = 0, tt = -1;
	for (int i = 1; i <= cnt; ++i) {
		while (hh + 1 <= tt && on_right(line[i], line[q[tt]], line[q[tt - 1]])) --tt;
		while (hh + 1 <= tt && on_right(line[i], line[q[hh]], line[q[hh + 1]])) ++hh;
		q[++tt] = i;
	}
	while (hh + 1 <= tt && on_right(line[q[hh]], line[q[tt]], line[q[tt - 1]])) --tt;
	while (hh + 1 <= tt && on_right(line[q[tt]], line[q[hh]], line[q[hh + 1]])) ++hh;
	q[++tt] = q[hh];
	int k = 0;
	for (int i = hh; i < tt; ++i)
		ans[k++] = get_intersection(line[q[i]], line[q[i + 1]]);
	double res = 0;
	for (int i = 2; i < k; ++i) {
		res += cross(ans[i - 1] - ans[0], ans[i] - ans[0]);
	}
	return res / 2;
}

int main(void)
{
	scanf("%d", &n);
	while (n--) {
		scanf("%d", &m);
		for (int i = 0; i < m; ++i)
			scanf("%lf%lf", &pt[i].x, &pt[i].y);
		for (int i = 0; i < m; ++i)
			line[++cnt] = {pt[i], pt[(i + 1) % m]};
	}
	double res = half_plain_intersection();
	printf("%.3lf\n", res);
	return 0;
}