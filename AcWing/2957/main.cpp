#include <map>
#include <cmath>
#include <vector>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long double LD;
const int N = 1e4 + 10;
const double eps = 1e-18;

struct PII
{
	int x, y;
	bool operator<(const PII &b) const
	{
		return x == b.x ? y < b.y : x < b.x;
	}
};
struct PDD
{
	LD x, y;
	PDD operator+(const PDD &b) const
	{
		return {x + b.x, y + b.y};
	}
	PDD operator-(const PDD &b) const
	{
		return {x - b.x, y - b.y};
	}
};
PDD operator*(LD a, PDD b)
{
	return {a * b.x, a * b.y};
}
struct Line
{
	PDD st, ed;
	vector<int> ids;
};

int sign(LD x)
{
	if (fabs(x) < eps) return 0;
	if (x < 0) return -1;
	return 1;
}
int cmpd(LD x, LD y)
{
	return sign(x - y);
}
LD get_angle(PDD a)
{
	return atan2(a.y, a.x);
}
LD get_angle(Line a)
{
	return get_angle(a.ed - a.st);
}
LD dot(PDD a, PDD b)
{
	return a.x * b.x + a.y * b.y;
}
LD cross(PDD a, PDD b)
{
	return a.x * b.y - a.y * b.x;
}


bool cmp(Line a, Line b)
{
	LD A = get_angle(a), B = get_angle(b);
	if (!cmpd(A, B)) return sign(cross(b.ed - a.st, a.ed - a.st)) > 0;
	return A < B;
}
PDD get_intersection(PDD p, PDD v, PDD q, PDD w)
{
	PDD u = p - q;
	LD t = cross(u, w) / cross(w, v);
	return p + t * v;
}
PDD get_intersection(Line a, Line b)
{
	return get_intersection(a.st, a.ed - a.st, b.st, b.ed - b.st);
}
bool on_right(Line a, Line u, Line v)
{
	PDD it = get_intersection(u, v);
	return sign(cross(it - a.st, a.ed - a.st)) > 0;
}

int n;
int ki[N], vi[N];
Line line[N]; int cnt;
int q[N];
vector<int> ans;

void half_plane_intersection(void)
{
	sort(line + 1, line + 1 + cnt, cmp);
	int hh = 0, tt = -1;
	for (int i = 1; i <= cnt; ++i) {
		while (hh + 1 <= tt && on_right(line[i], line[q[tt]], line[q[tt - 1]])) --tt;
		while (hh + 1 <= tt && on_right(line[i], line[q[hh]], line[q[hh + 1]])) ++hh;
		q[++tt] = i;
	}
	while (hh + 1 <= tt && on_right(line[hh], line[q[tt]], line[q[tt - 1]])) --tt;
	while (hh + 1 <= tt && on_right(line[tt], line[q[hh]], line[q[hh + 1]])) ++hh;
	for (int i = hh; i <= tt; ++i)
		for (auto x : line[q[i]].ids) {
			ans.push_back(x);
		}
	sort(ans.begin(),ans.end());
	printf("%d\n", ans.size());
	for (int i = 0; i < ans.size(); ++i) printf("%d%c", ans[i], i == ans.size() - 1 ? '\n' : ' ');
}

int main(void)
{
	scanf("%d", &n);
	map<PII, vector<int>> ids;
	for (int i = 1; i <= n; ++i) scanf("%d", &ki[i]);
	for (int i = 1; i <= n; ++i) scanf("%d", &vi[i]);
	for (int i = 1; i <= n; ++i)
		ids[{ki[i], vi[i]}].push_back(i);
	line[++cnt] = {{0, 10000}, {0, 0}};
	line[++cnt] = {{0, 0}, {10000, 0}};
	for (auto& [k, v] : ids) {
		line[++cnt] = {{0, k.x}, {1, k.x + k.y}, v};
	}

	half_plane_intersection();
	return 0;
}