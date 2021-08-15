#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 100;
const double eps = 1e-8;
const double pi = 3.141592653589793238462643383;

double R;

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
	PDD operator-(const PDD &b) const
	{
		return {x - b.x, y - b.y};
	}
	PDD operator+(const PDD &b) const
	{
		return {x + b.x, y + b.y};
	}
};
PDD operator*(double a, PDD b)
{
	return {a * b.x, a * b.y};
}
double dot(PDD a, PDD b)
{
	return a.x * b.x + a.y * b.y;
}
double cross(PDD a, PDD b)
{
	return a.x * b.y - a.y * b.x;
}
double get_len(PDD a)
{
	return sqrt(dot(a, a));
}
double get_dist(PDD a, PDD b)
{
	return get_len(b - a);
}
PDD rotate(PDD a, double theta)
{
	return {a.x * cos(theta) - a.y * sin(theta), a.x * sin(theta) + a.y * cos(theta)};
}
PDD get_line_intersection(PDD p, PDD v, PDD q, PDD w)
{
	PDD u = p - q;
	double t = cross(w, u) / cross(v, w);
	return p + t * v;
}
PDD norm(PDD x)
{
	return 1 / get_len(x) * x;
}
double get_sector(PDD a, PDD b)
{
	double angle = acos(dot(a, b) / get_len(a) / get_len(b));
	if (sign(cross(a, b)) < 0) angle = -angle;
	return R * R * angle / 2;
}
bool on_segment(PDD e, PDD a, PDD b)
{
	return (!sign(cross(e - a, e - b)) && sign(dot(e - a, e - b)) <= 0);
}

int n;
PDD q[N], r;

double get_line_circle_intersection(PDD a, PDD b, PDD &pa, PDD &pb)
{
	auto e = get_line_intersection(a, b - a, r, rotate(b - a, pi / 2));
	auto mind = get_dist(e, r);
	if (!on_segment(e, a, b)) mind = min(get_dist(a, r), get_dist(b, r));
	if (cmpd(R, mind) <= 0) return mind;
	double len = sqrt(R * R - get_dist(e, r) * get_dist(e, r));
	pa = e + len * norm(a - b);
	pb = e + len * norm(b - a);
	return mind;
}

double Get_Area(PDD a, PDD b)
{
	double da = get_dist(a, r), db = get_dist(b, r);
	if (cmpd(da, R) <= 0 && cmpd(db, R) <= 0) return cross(a, b) / 2;
	if (!sign(cross(a, b))) return 0;
	PDD pa, pb;
	double mind = get_line_circle_intersection(a, b, pa, pb);
	if (cmpd(mind, R) >= 0) return get_sector(a, b);
	if (cmpd(da, R) <= 0) return cross(a, pb) / 2 + get_sector(pb, b);
	if (cmpd(db, R) <= 0) return get_sector(a, pa) + cross(pa, b) / 2;
	return get_sector(a, pa) + cross(pa, pb) / 2 + get_sector(pb, b);
}
double Work(void)
{
	double res = 0;
	for (int i = 0; i < n; ++i) {
		res += Get_Area(q[i], q[(i + 1) % n]);
	}
	return res;
}

int main(void)
{
	while (~scanf("%lf%d", &R, &n)) {
		for (int i = 0; i < n; ++i) scanf("%lf%lf", &q[i].x, &q[i].y);
		printf("%.2lf\n", fabs(Work()));
	}
	return 0;
}