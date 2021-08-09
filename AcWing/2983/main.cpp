#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long LL;
const int N = 5010;
struct PLL
{
	long long x, y;
	PLL operator-(const PLL &b) const
	{
		return {x - b.x, y - b.y};
	}
};
LL cross(PLL a, PLL b)
{
	return a.x * b.y - a.y * b.x;
}

int n, m;
int ans[N];
PLL a[N], b[N];
LL x1, y1, x2, y2;

int find(PLL Point)
{
	int l = 0, r = n, mid;
	while (l < r) {
		mid = l + r >> 1;
		if (cross(a[mid] - b[mid], Point - b[mid]) > 0) r = mid;
		else l = mid + 1;
	}
	return l;
}

int main(void)
{
	bool is_first = 1;
	while (scanf("%d", &n), n) {
		memset(ans, 0, sizeof ans);
		if (is_first) is_first = 0;
		else puts("");

		scanf("%d%lld%lld%lld%lld", &m, &x1, &y1, &x2, &y2);
		for (int i = 0; i < n; ++i) {
			LL u, l;
			scanf("%lld%lld", &u, &l);
			a[i] = {u, y1}, b[i] = {l, y2};
		}
		a[n] = {x1, y1}, b[n] = {x2, y2};
		for (int i = 1; i <= m; ++i) {
			LL x, y;
			scanf("%lld%lld", &x, &y);
			++ans[find({x, y})];
		}

		for (int i = 0; i <= n; ++i) printf("%d: %d\n", i, ans[i]);
	}
}