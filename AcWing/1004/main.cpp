#include <vector>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

#define ll long long
const int N = 3e5 + 10;
const ll INF = 2e18;

struct PLL
{
	ll x, y;
};

int n, m;
char s[N];
int w[N];
int sa[N], rk[N], height[N], x[N], y[N], c[N];
int p[N], sz[N];
ll max1[N], max2[N], min1[N], min2[N];
PLL ans[N];
vector<int> hs[N];

void get_sa(void);
void get_height(void);
PLL calc(int x);

int main(void)
{
	scanf("%d", &n);
	m = 122;
	scanf("%s", s + 1);
	get_sa();
	get_height();

	for (int i = 1; i <= n; ++i) scanf("%d", &w[i]);

	for (int i = 2; i <= n; ++i) hs[height[i]].push_back(i);
	for (int i = 1; i <= n; ++i) {
		p[i] = i, sz[i] = 1;
		max1[i] = min1[i] = w[sa[i]];
		max2[i] = -INF, min2[i] = INF;
	}

	for (int i = n - 1; i >= 0; --i) {
		ans[i] = calc(i);
	}
	for (int i = 0; i < n; ++i) printf("%lld %lld\n", ans[i].x, ans[i].y);

	return 0;
}

void get_sa(void)
{
	for (int i = 1; i <= n; ++i) ++c[x[i] = s[i]];
	for (int i = 2; i <= m; ++i) c[i] += c[i - 1];
	for (int i = n; i >= 1; --i) sa[c[x[i]]--] = i;
	for (int k = 1; k <= n; k <<= 1) {
		int num = 0;
		for (int i = n - k + 1; i <= n; ++i) y[++num] = i;
		for (int i = 1; i <= n; ++i)
			if (sa[i] > k) y[++num] = sa[i] - k;
		for (int i = 1; i <= m; ++i) c[i] = 0;
		for (int i = 1; i <= n; ++i) ++c[x[i]];
		for (int i = 2; i <= m; ++i) c[i] += c[i - 1];
		for (int i = n; i >= 1; --i) sa[c[x[y[i]]]--] = y[i], y[i] = 0;

		swap(x, y);
		x[sa[1]] = 1, num = 1;
		for (int i = 2; i <= n; ++i)
			x[sa[i]] = (y[sa[i]] == y[sa[i - 1]] && y[sa[i] + k] == y[sa[i - 1] + k]) ? num : ++num;
		if (num == n) break;
		m = num;
	}
}
void get_height(void)
{
	for (int i = 1; i <= n; ++i) rk[sa[i]] = i;
	for (int i = 1, k = 0; i <= n; ++i) {
		if (rk[i] == 1) continue;
		if (k) --k;
		int j = sa[rk[i] - 1];
		while (i + k <= n && j + k <= n && s[i + k] == s[j + k]) ++k;
		height[rk[i]] = k;
	}
}
int find(int x) { return x == p[x] ? x : p[x] = find(p[x]); }
ll get(int x) { return x * (x - 1ll) / 2; }
PLL calc(int r)
{
	static ll cnt = 0, maxn = -INF;
	for (auto x : hs[r]) {
		int a = find(x), b = find(x - 1);
		cnt -= get(sz[a]) + get(sz[b]);
		p[b] = a;
		sz[a] += sz[b];
		cnt += get(sz[a]);
		if (max1[a] > max1[b])
			max2[a] = max(max2[a], max1[b]);
		else {
			max2[a] = max(max1[a], max2[b]);
			max1[a] = max1[b];
		}
		if (min1[a] < min1[b])
			min2[a] = min(min2[a], min1[b]);
		else {
			min2[a] = min(min1[a], min2[b]);
			min1[a] = min1[b];
		}
		maxn = max(maxn, max(max1[a] * max2[a], min1[a] * min2[a]));
	}
	if (maxn == -INF) return {cnt, 0};
	return {cnt, maxn};
}