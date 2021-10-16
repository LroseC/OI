#include <vector>
#include <cctype>
#include <cstdio>
#include <climits>
#include <algorithm>

using namespace std;

typedef long long LL;
const int N = 4e5 + 10;

template<typename T = int>
inline T read(void)
{
	T res = 0, f = 1; char ch = getchar();
	while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
	while (isdigit(ch)) { res = res * 10 + ch - '0'; ch = getchar(); }
	return res * f;
}
template<typename T>
inline void write(T x, char end = '\n')
{
	static char buf[50]; int p = -1;
	if (x == 0) putchar('0');
	if (x < 0) { putchar('-'); x = -x; }
	while (x) { buf[++p] = x % 10; x /= 10; }
	while (~p) { putchar(buf[p] + '0'); --p; } putchar(end);
}

struct Vector
{
	int x, y;
	Vector(void) {}
	Vector(int _x, int _y) : x(_x), y(_y) {}
	bool operator<(const Vector &b) const
	{
		if (x != b.x) return x < b.x;
		return y < b.y;
	}
};
inline void Print(Vector x)
{
	printf("x = %d, y = %d\n", x.x, x.y);
}

int n;
Vector p[N];

inline LL sq(LL x) { return x * x; }
inline bool cmp_y(Vector a, Vector b)
{
	if (a.y != b.y) return a.y < b.y;
	return a.x < b.x;
}
inline LL Getdis(Vector a, Vector b)
{
	return sq(a.x - b.x) + sq(a.y - b.y);
}

LL solve(int l, int r)
{
	if (l == r) return LLONG_MAX;
	int mid = l + r >> 1;
	LL lans = solve(l, mid), rans = solve(mid + 1, r);
	LL mindis = min(lans, rans);
	static vector<Vector> tmp; tmp.clear();
	for (int i = l; i <= r; ++i)
		if (sq(abs(p[i].x - p[mid + 1].x)) <= mindis)
			tmp.emplace_back(p[i]);
	sort(tmp.begin(), tmp.end(), cmp_y);
	auto it = tmp.begin();
	auto jt = tmp.begin();
	while (it != tmp.end()) {
		while (jt != tmp.end() && sq(jt->y - it->y) <= mindis) ++jt;
		for (auto at = it; at != jt; ++at) {
			auto bt = at;
			++bt;
			while (bt != jt) {
				mindis = min(mindis, Getdis(*at, *bt));
				++bt;
			}
		}
		++it;
	}
	return mindis;
}

int main(void)
{
	n = read();
	for (int i = 1; i <= n; ++i) {
		p[i].x = read();
		p[i].y = read();
	}
	sort(p + 1, p + 1 + n);
	write(solve(1, n));
	return 0;
}