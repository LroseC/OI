#include <cmath>
#include <vector>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 110;
const double eps = 1e-8, INF = 1e6;

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
	PDD operator+(const PDD &b) const
	{
		return {x + b.x, y + b.y};
	}
	PDD operator-(const PDD &b) const
	{
		return {x - b.x, y - b.y};
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
void Print(PDD x)
{
	printf("x = %lf, y = %lf\n", x.x, x.y);
}

int n;
vector<double> xs;
PDD tr[N][3];
PDD q[N];

bool on_segment(PDD p, PDD u, PDD v)
{
	return sign(dot(p - v, p - u)) <= 0;
}

PDD get_segment_intersection(PDD p, PDD v, PDD q, PDD w)
{
	if (!sign(cross(v, w))) return PDD({INF, INF});
	auto u = p - q;
	double t = cross(w, u) / cross(v, w);
	auto intersection = p + t * v;
	return (on_segment(intersection, p, p + v) && on_segment(intersection, q, q + w)) ? intersection : PDD({INF, INF});
}

double calc_line(double x, bool side)
{
	int cnt = 0;
	for (int i = 1; i <= n; ++i) {
		if (cmpd(tr[i][0].x, x) > 0 || cmpd(tr[i][2].x, x) < 0) continue;
		if (!cmpd(tr[i][0].x, x) && !cmpd(tr[i][1].x, x)) {
			if (side == 0)
				q[++cnt] = {tr[i][0].y, tr[i][1].y};
		}
		else if (!cmpd(tr[i][2].x, x) && !cmpd(tr[i][1].x, x)) {
			if (side == 1)
				q[++cnt] = {tr[i][1].y, tr[i][2].y};
		}
		else {
			int dcnt = 0;
			double d[3];
			for (int j = 0; j < 3; ++j) {
				auto tmp = get_segment_intersection(tr[i][j], tr[i][(j + 1) % 3] - tr[i][j], {x, -INF}, {0, 2 * INF});
				if (cmpd(tmp.x, INF)) d[dcnt++] = tmp.y;
			}
			sort(d, d + dcnt);
			q[++cnt] = {d[0], d[dcnt - 1]};
		}
	}
	sort(q + 1, q + 1 + cnt);
	double st = q[1].x, ed = q[1].y;
	double res = 0;
	for (int i = 2; i <= cnt; ++i) {
		if (cmpd(ed, q[i].x) >= 0) ed = max(ed, q[i].y);
		else {
			res += ed - st;
			st = q[i].x, ed = q[i].y;
		}
	}
	return res + ed - st;
}
double calc_area(double a, double b)
{
	return (calc_line(a, 0) + calc_line(b, 1)) * (b - a) / 2;
}

int main(void)
{
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		for (int j = 0; j < 3; ++j) {
			scanf("%lf%lf", &tr[i][j].x, &tr[i][j].y);
			xs.push_back(tr[i][j].x);
		}
		sort(tr[i], tr[i] + 3);
	}
	for (int i = 1; i <= n; ++i)
		for (int j = i + 1; j <= n; ++j)
			for (int a = 0; a < 3; ++a)
				for (int b = 0; b < 3; ++b) {
					auto tmp = get_segment_intersection(tr[i][a], tr[i][(a + 1) % 3] - tr[i][a], tr[j][b], tr[j][(b + 1) % 3] - tr[j][b]);
					if (tmp.y != INF) {
						xs.push_back(tmp.x);
					}
				}
	sort(xs.begin(), xs.end());
	double res = 0;
	for (int i = 1; i < xs.size(); ++i) {
		if (cmpd(xs[i], xs[i - 1]))
			res += calc_area(xs[i - 1], xs[i]);
	}
	printf("%.2lf\n", res);
	return 0;
}