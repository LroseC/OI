#include <tuple>
#include <vector>
#include <cctype>
#include <cstdio>
#include <climits>
#include <algorithm>

struct FSI
{
	template<typename T>
	FSI& operator>>(T &res)
	{
		res = 0; T f = 1; char ch = getchar();
		while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
		while (isdigit(ch)) { res = res * 10 + ch - '0'; ch = getchar(); }
		res = res * f; return *this;
	}
} read;

using i64 = long long;
const int N = 1e6 + 10, LG = 22;

int n, m, stk[N];
int idx, id[N], dep[N], fa[N][LG];
bool isKey[N];
int cnt[N], minx[N], maxx[N];
i64 sum[N];
std::vector<int> G[N];

void initLCA(int u)
{
	id[u] = ++idx;
	dep[u] = dep[fa[u][0]] + 1;
	for (int i = 1; i < LG; ++i)
		fa[u][i] = fa[fa[u][i - 1]][i - 1];
	for (int v : G[u])
		if (v != fa[u][0]) {
			fa[v][0] = u;
			initLCA(v);
		}
}
int LCA(int u, int v)
{
	if (dep[u] < dep[v])
		std::swap(u, v);
	for (int i = LG - 1; i >= 0; --i)
		if (dep[fa[u][i]] >= dep[v])
			u = fa[u][i];
	if (u == v) return u;
	for (int i = LG - 1; i >= 0; --i)
		if (fa[u][i] != fa[v][i]) {
			u = fa[u][i];
			v = fa[v][i];
		}
	return fa[u][0];
}
void build(int K, std::vector<int> &h)
{
	int top = 0;
	stk[++top] = 1;
	G[1].clear();
	for (int i = 0, d; i < K; ++i) {
		if (h[i] == 1) continue;
		d = LCA(h[i], stk[top]);
		if (d != stk[top]) {
			while (id[d] < id[stk[top - 1]]) {
				G[stk[top - 1]].emplace_back(stk[top]);
				--top;
			}
			--top;
			if (stk[top] != d)
				G[d].clear();
			G[d].emplace_back(stk[top + 1]);
			if (stk[top] != d)
				stk[++top] = d;
		}
		stk[++top] = h[i];
		G[h[i]].clear();
	}
	for (int i = 2; i <= top; ++i)
		G[stk[i - 1]].emplace_back(stk[i]);
}
std::tuple<i64, int, int> calc(int u)
{
	cnt[u] = sum[u] = 0;
	minx[u] = 1e9;
	maxx[u] = -1e9;
	if (isKey[u]) {
		++cnt[u];
		sum[u] += dep[u];
		minx[u] = maxx[u] = 0;
	}
	i64 res1 = 0;
	int res2 = INT_MAX, res3 = INT_MIN;
	for (int v : G[u]) {
		auto t = calc(v);
		res1 += std::get<0>(t);
		res2 = std::min(res2, std::get<1>(t));
		res3 = std::max(res3, std::get<2>(t));
		cnt[u] += cnt[v];
		sum[u] += sum[v];
		res2 = std::min(res2, minx[u] + minx[v] + dep[v] - dep[u]);
		res3 = std::max(res3, maxx[u] + maxx[v] + dep[v] - dep[u]);
		minx[u] = std::min(minx[u], minx[v] + dep[v] - dep[u]);
		maxx[u] = std::max(maxx[u], maxx[v] + dep[v] - dep[u]);
	}
	for (int v : G[u]) {
		int sz = cnt[u] - cnt[v];
		res1 += sz * (sum[v] - 1ll * dep[u] * cnt[v]);
	}
	return std::make_tuple(res1, res2, res3);
}

int main(void)
{
	read >> n;
	for (int i = 1, u, v; i < n; ++i) {
		read >> u >> v;
		G[u].emplace_back(v);
		G[v].emplace_back(u);
	}
	initLCA(1);
	for (int i = 1; i <= n; ++i)
		G[i].clear();
	read >> m;
	for (int i = 1, K; i <= m; ++i) {
		read >> K;
		std::vector<int> h(K);
		for (int i = 0; i < K; ++i) {
			read >> h[i];
			isKey[h[i]] = 1;
		}
		auto cmp = [](int a, int b) { return id[a] < id[b]; };
		std::sort(h.begin(), h.end(), cmp);
		build(K, h);
		auto t = calc(1);
		printf("%lld %d %d\n", std::get<0>(t), std::get<1>(t), std::get<2>(t));
		for (int i = 0; i < K; ++i)
			isKey[h[i]] = 0;
	}
	return 0;
}
