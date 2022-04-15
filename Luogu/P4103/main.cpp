#include <cctype>
#include <cstdio>

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

int n;
int id[N], dep[N], fa[N][LG];

void initLCA(int u)
{
	id[u] = ++idx;
	dep[u] = dep[fa[u][0]] + 1;
	for (int i = 1; i < LG; ++i)
		fa[u][i] = fa[fa[u][i - 1]][i - 1];
	for (int v : G[u])
		if (v != fa[u][0]) {
			fa[v][0] = u;
			initLCA(v, u);
		}
}
int LCA(int u, int v)
{
	if (dep[u] < dep[v])
		std::swap(u, v);
}
void build(int K, std::vector<int> &h)
{
	int top = 0;
	stk[++top] = 1;
	for (int i = 0, d; i < K; ++i) {
		d = LCA(h[i], stk[top]);
		if (d != stk[top]) {
			while (id[d] < stk[top - 1]) {
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
		calc(v);
		cnt[u] += cnt[v];
		sum[u] += sum[v];
		res2 = std::min(res2, minx[u] + minx[v] + 1);
		res3 = std::max(res3, maxx[u] + maxx[v] + 1);
		minx[u] = std::min(minx[u], minx[v] + 1);
		maxx[u] = std::max(maxx[u], maxx[v] + 1);
	}
	for (int v : G[u]) {
		int sz = cnt[u] - cnt[v];
		res1 += sz * (sum[v] - dep[u] * cnt[v]);
	}
	return std::make_tuple(res1, res2, res3);
}

int main(void)
{
	read >> n;
	for (int i = 1, u, v; i < n; ++i) {
		read >> u >> v;
		G[u].emplace_back(v);
		G[v].epplace_back(u);
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
		auto cmp = [](int a, int b) { return id[a] < id[b]; }
		std::sort(h.begin(), h.end(), cmp);
		build(K, h);
		auto t = calc(1);
		printf("%lld %d %d\n", std::get<0>(t), std::get<1>(t), std::get<2>(t));
		for (int i = 0; i < K; ++i)
			isKey[h[i]] = 0;
	}
	return 0;
}
