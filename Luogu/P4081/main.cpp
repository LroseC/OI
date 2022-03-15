#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>

using namespace std;

using LL = long long;
const int N = 4e5 + 10;

int n, m;
int sa[N], rk[N], height[N], x[N], y[N], c[N];
int id[N], len[N];
int str[N]; char tmp[N];
int a[N], b[N];
int st[N][31], lg2[N];
int string_cnt;
LL ans[N];

void buildSA(void)
{
	m = 400000;
	for (int i = 0; i <= m; ++i) c[i] = 0;
	for (int i = 1; i <= n; ++i) ++c[x[i] = str[i]];
	for (int i = 1; i <= m; ++i) c[i] += c[i - 1];
	for (int i = n; i >= 1; --i) sa[c[x[i]]--] = i;
	for (int k = 1; k <= n; k <<= 1) {
		int num = 0;
		for (int i = n - k + 1; i <= n; ++i)
			y[++num] = i;
		for (int i = 1; i <= n; ++i)
			if (sa[i] > k) y[++num] = sa[i] - k;

		for (int i = 0; i <= m; ++i) c[i] = 0;
		for (int i = 1; i <= n; ++i) ++c[x[i]];
		for (int i = 1; i <= m; ++i) c[i] += c[i - 1];
		for (int i = n; i >= 1; --i) sa[c[x[y[i]]]--] = y[i], y[i] = 0;
		swap(x, y);
		x[sa[1]] = num = 1;
		for (int i = 2; i <= n; ++i) {
			int ynow = sa[i] + k <= n ? y[sa[i] + k] : 0;
			int ynex = sa[i - 1] + k <= n ? y[sa[i - 1] + k] : 0;
			x[sa[i]] = (y[sa[i]] == y[sa[i - 1]] && ynow == ynex) ? num : ++num;
		}
		if (num == n) break;
		m = num;
	}

	for (int i = 1; i <= n; ++i)
		rk[sa[i]] = i;
	for (int i = 1, k = 0; i <= n; ++i) {
		if (rk[i] == 1) continue;
		if (k) --k;
		int j = sa[rk[i] - 1];
		while (i + k <= n && j + k <= n && str[i + k] == str[j + k])
			++k;
		height[rk[i]] = k;
	}
}
void buildST(void)
{
	for (int i = 2; i <= n; ++i)
		lg2[i] = lg2[i >> 1] + 1;
	for (int i = 1; i <= n; ++i)
		st[i][0] = height[i];
	for (int k = 1; k <= 30; ++k)
		for (int i = 1; i + (1 << k - 1) <= n; ++i)
			st[i][k] = min(st[i][k - 1], st[i + (1 << k - 1)][k - 1]);
}
int queryHeight(int l, int r)
{
	++l; int t = lg2[r - l + 1];
	return min(st[l][t], st[r - (1 << t) + 1][t]);
}

int main(void)
{
	scanf("%d", &string_cnt);
	for (int i = 1; i <= string_cnt; ++i) {
		scanf("%s", tmp + 1);
		for (len[i] = 1; tmp[len[i]]; ++len[i])
			str[++n] = tmp[len[i]], id[n] = i;
		str[++n] = 'z' + i;
		--len[i];
		ans[i] = 1ll * len[i] * (len[i] + 1) / 2;
	}
	str[n--] = 0;

	buildSA();
	buildST();

	int last = 0, llast = 0;
	for (int i = n; i >= 1; --i) {
		if (id[sa[i]] != id[sa[last]])
			llast = last;
		last = i;
		a[i] = llast <= i ? 0 : queryHeight(i, llast);
	}

	for (int i = 1; i <= n; ++i) {
		int tmp = max(a[i], height[i]);
		ans[id[sa[i]]] -= tmp;
	}
	for (int i = 1; i <= string_cnt; ++i)
		printf("%lld\n", ans[i]);
	return 0;
}
