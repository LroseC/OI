#include <vector>
#include <cctype>
#include <cstdio>
#include <algorithm>

using namespace std;

#define int long long
typedef long long LL;
const int N = 2e5, M = 110;

inline int read(void)
{
	int res = 0, f = 1; char ch = getchar();
	while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
	while (isdigit(ch)) { res = res * 10 + ch - '0'; ch = getchar(); }
	return res * f;
}

int n, k, ans;
int r[N];
int dis[N], cost[N], pay[N];
int sumcost[N], sumpay[N];
int left[N], right[N];
vector<int> Rinv[N];
int f[N];
int tr[N << 2];
int add[N << 2];

void Maintain(int p)
{
	tr[p] = min(tr[p << 1], tr[p << 1 | 1]);
}
void Spread(int p)
{
	add[p << 1] += add[p];
	add[p << 1 | 1] += add[p];
	tr[p << 1] += add[p];
	tr[p << 1 | 1] += add[p];
	add[p] = 0;
}
void Build(int p = 1, int l = 0, int r = n)
{
	add[p] = 0;
	if (l == r) {
		tr[p] = f[l];
		return;
	}
	int mid = l + r >> 1;
	Build(p << 1, l, mid); Build(p << 1 | 1, mid + 1, r);
	Maintain(p);
}
void Add(int L, int R, int val, int p = 1, int l = 0, int r = n)
{
	if (L <= l && r <= R) {
		tr[p] += val;
		add[p] += val;
		return;
	}
	Spread(p);
	int mid = l + r >> 1;
	if (L <= mid) Add(L, R, val, p << 1, l, mid);
	if (R > mid) Add(L, R, val, p << 1 | 1, mid + 1, r);
	Maintain(p);
}
int Query(int L, int R, int p = 1, int l = 0, int r = n)
{
	if (L <= l && r <= R) {
		return tr[p];
	}
	Spread(p);
	int mid = l + r >> 1;
	int res = 0x3f3f3f3f;
	if (L <= mid) res = min(res, Query(L, R, p << 1, l, mid));
	if (R > mid) res = min(res, Query(L, R, p << 1 | 1, mid + 1, r));
	return res;
}

signed main(void)
{
	n = read(), k = read();
	for (int i = 2; i <= n; ++i) dis[i] = read();
	for (int i = 1; i <= n; ++i) cost[i] = read();
	for (int i = 1; i <= n; ++i) r[i] = read();
	for (int i = 1; i <= n; ++i) pay[i] = read();
	dis[0] = -0x3f3f3f3f, dis[n + 1] = 0x3f3f3f3f;

	for (int i = 1; i <= n; ++i) {
		sumpay[i] = sumpay[i - 1] + pay[i];
		sumcost[i] = sumcost[i - 1] + cost[i];
		left[i] = lower_bound(dis, dis + 1 + n, dis[i] - r[i]) - dis;
		right[i] = upper_bound(dis, dis + 1 + n, dis[i] + r[i]) - dis - 1;
		Rinv[right[i]].emplace_back(i);
	}
	for (int i = 1; i <= n; ++i) {
		f[i] = f[i - 1];
		for (auto x : Rinv[i - 1]) f[i] += pay[x];
	}
	for (int i = 1; i <= n; ++i) f[i] += cost[i];
	ans = f[n];
	for (int j = 1; j <= k; ++j) {
		Build();
		for (int i = 1; i <= n; ++i) {
			f[i] = Query(0, i - 1) + cost[i];
			for (auto x : Rinv[i]) Add(0, left[x] - 1, pay[x]);
		}
		ans = min(ans, Query(0, n));
	}
	printf("%lld\n", ans);
	return 0;
}