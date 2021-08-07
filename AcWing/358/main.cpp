#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

#define int long long
typedef long long LL;
const int N = 2e6 + 10, M = N << 1;

int n;
int idx = 1, head[N], nex[M], to[M], w[M];
int q[N];
LL ans, sum[N], s[N], d[N];
bool vis[N], instack[N];
int fu[N], fw[N];
int ed[N], cir_cnt, cir[N];

void AddEdge(int u, int v, int wi)
{
	nex[++idx] = head[u]; w[idx] = wi;
	head[u] = idx; to[idx] = v;
}

void dfs_c(int u, int from)
{
	vis[u] = instack[u] = 1;
	for (int e = head[u]; e; e = nex[e]) {
		if (e == (from ^ 1)) continue;
		int v = to[e];
		fu[v] = u, fw[v] = w[e];
		if (!vis[v]) dfs_c(v, e);
		else if (instack[v]) {
			LL sum = w[e];
			++cir_cnt;
			ed[cir_cnt] = ed[cir_cnt - 1];
			for (int i = u; i != v; i = fu[i]) {
				s[i] = sum;
				sum += fw[i];
				cir[++ed[cir_cnt]] = i;
			}
			s[v] = sum;
			cir[++ed[cir_cnt]] = v;
		}
	}
	instack[u] = 0;
}

int dfs_s(int u, int fa)
{
	LL d1 = 0, d2 = 0;
	for (int e = head[u]; e; e = nex[e]) {
		int v = to[e];
		if (vis[v] || v == fa) continue;
		int tmp = w[e] + dfs_s(v, u);
		if (tmp >= d1) d2 = d1, d1 = tmp;
		else if (tmp > d2) d2 = tmp;
	}
	ans = max(ans, d1 + d2);
	return d1;
}

signed main(void)
{
	scanf("%lld", &n);
	for (int u = 1; u <= n; ++u) {
		int v, w;
		scanf("%lld%lld", &v, &w);
		AddEdge(u, v, w);
		AddEdge(v, u, w);
	}
	for (int i = 1; i <= n; ++i)
		if (!vis[i])
			dfs_c(i, 0);
	memset(vis, 0, sizeof vis);
	for (int i = 1; i <= ed[cir_cnt]; ++i)
		vis[cir[i]] = 1;
	LL res = 0;
	for (int i = 1; i <= cir_cnt; ++i) {
		int sz = 0;
		ans = 0;
		for (int j = ed[i - 1] + 1; j <= ed[i]; ++j) {
			int k = cir[j];
			d[++sz] = dfs_s(k, 0);
			sum[sz] = s[k];
		}
		for (int j = 1; j <= sz; ++j)
			d[sz + j] = d[j], sum[sz + j] = sum[j] + sum[sz];

		int hh = 0, tt = -1;
		for (int j = 1; j <= (sz << 1); ++j) {
			if (hh <= tt && j - q[hh] >= sz) ++hh;
			if (hh <= tt) ans = max(ans, d[j] + sum[j] + d[q[hh]] - sum[q[hh]]);
			while (hh <= tt && d[j] - sum[j] >= d[q[tt]] - sum[q[tt]]) --tt;
			q[++tt] = j;
		}
		res += ans;
	}
	printf("%lld\n", res);

	return 0;
}