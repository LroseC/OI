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
const int N = 3e5 + 10, LG = 20;

struct Edge
{
	int v, w;
	Edge(void) {}
	Edge(int _v, int _w) { v = _v, w = _w; }
};

int n, m;
int idx, id[N];
int dep[N], fa[N][LG], minx[N][LG];
int stk[N];
bool isKey[N];
std::vector<Edge> G[N], OG[N];

i64 dp(int u, int fa)
{
	i64 res = 0;
	for (auto t : G[u])
		if (t.v != fa) {
			if (isKey[t.v]) res += t.w;
			else res += std::min(0ll + t.w, dp(t.v, u));
		}
	return res;
}
void initLCA(int u)
{
	id[u] = ++idx;
	dep[u] = dep[fa[u][0]] + 1;
	for (int i = 1; i < LG; ++i) {
		fa[u][i] = fa[fa[u][i - 1]][i - 1];
		minx[u][i] = std::min(minx[u][i - 1], minx[fa[u][i - 1]][i - 1]);
	}
	for (auto t : G[u])
		if (t.v != fa[u][0]) {
			fa[t.v][0] = u;
			minx[t.v][0] = t.w;
			initLCA(t.v);
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
int getMin(int u, int v)
{
	if (dep[u] < dep[v])
		std::swap(u, v);
	int res = INT_MAX;
	for (int i = LG - 1; i >= 0; --i)
		if (dep[fa[u][i]] >= dep[v]) {
			res = std::min(res, minx[u][i]);
			u = fa[u][i];
		}
	return res;
}

int main(void)
{
	read >> n;
	for (int i = 1, u, v, w; i < n; ++i) {
		read >> u >> v >> w;
		G[u].emplace_back(v, w);
		G[v].emplace_back(u, w);
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

		int top = 0;
		stk[++top] = 1;
		G[1].clear();
		for (int i = 0, d; i < K; ++i) {
			if ((d = LCA(stk[top], h[i])) != stk[top]) {
				while (id[d] < id[stk[top - 1]]) {
					G[stk[top - 1]].emplace_back(stk[top], getMin(stk[top - 1], stk[top]));
					--top;
				}
				if (stk[top - 1] != d) {
					G[d].clear();
					G[d].emplace_back(stk[top], getMin(d, stk[top]));
					stk[top] = d;
				}
				else {
					G[d].emplace_back(stk[top], getMin(d, stk[top]));
					--top;
				}
			}
			stk[++top] = h[i];
			G[h[i]].clear();
		}
		for (int i = 2; i <= top; ++i)
			G[stk[i - 1]].emplace_back(stk[i], getMin(stk[i - 1], stk[i]));

		printf("%lld\n", dp(1, 1));
		for (int i = 0; i < K; ++i)
			isKey[h[i]] = 0;
	}
	return 0;
}
