#include <vector>
#include <cctype>
#include <cstdio>
#include <algorithm>

struct FSI
{
	template<typename T>
	FSI& operator>>(T &res)
	{
		res = 0; T f = 1; char ch = getchar();
		while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
		while (isdigit(ch)) { res = res * 10 + (ch - '0') * f; ch = getchar(); }
		return *this;
	}
} read;

using i64 = long long;
const int N = 1e5 + 10, LG = 20;

int n, m;
bool isKey[N];
int stk[N], f[N], g[N];
int idx, id[N], dep[N], fa[N][LG];
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
	for (int i = 0; i < K; ++i) {
		if (h[i] == 1) continue;
		int d = LCA(h[i], stk[top]);
		if (d != stk[top]) {
			while (id[d] < id[stk[top - 1]]) {
				--top;
				G[stk[top]].emplace_back(stk[top + 1]);
			}
			if (d != stk[top - 1])
				G[d].clear();
			--top;
			G[d].emplace_back(stk[top + 1]);
			if (d != stk[top])
				stk[++top] = d;
		}
		G[h[i]].clear();
		stk[++top] = h[i];
	}
	for (int i = 2; i <= top; ++i) {
		G[stk[i - 1]].emplace_back(stk[i]);
	}
}

int calc(int u)
{
	f[u] = g[u] = 1e9;
	for (int v : G[u]) {
		if ((isKey[u] && (isKey[v] && dep[v] == dep[u] + 1)) || calc(v) == -1)
			return -1;
	}
	if (!isKey[u]) {
		g[u] = 1;
		for (int v : G[u])
			g[u] += f[v];
	}
	int flag = 0;
	int tmp = 0;
	for (int v : G[u]) {
		if (isKey[v] && dep[v] == dep[u] + 1)
			++flag;
		if (isKey[v])
			tmp += f[v] + 1;
		else
			tmp += std::min(f[v] + 1, g[v]);
	}
	if (flag == 0)
		g[u] = std::min(g[u], tmp);
	if (isKey[u] || flag >= 2)
		f[u] = g[u];
	else {
		int sum = 0;
		for (int v : G[u])
			sum += g[v];
		for (int v : G[u]) {
			if (flag == 0)
				f[u] = std::min(f[u], sum - g[v] + f[v]);
			else if (isKey[v] && dep[v] == dep[u] + 1)
				f[u] = std::min(f[u], sum - g[v] + f[v]);
		}
	}
	return f[u];
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
		for (int j = 0; j < K; ++j) {
			read >> h[j];
			isKey[h[j]] = 1;
		}
		auto cmp = [](int a, int b) { return id[a] < id[b]; };
		std::sort(h.begin(), h.end(), cmp);
		build(K, h);
		printf("%d\n", calc(1));
		for (int j = 0; j < K; ++j)
			isKey[h[j]] = 0;
	}
	return 0;
}
