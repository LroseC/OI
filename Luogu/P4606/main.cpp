#include <cctype>
#include <cstdio>

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

void tarjan(int u)
{
	dfn[u] = low[u] = ++dfnCnt;
	stk[++top] = u;
	for (int v : G[u]) {
		if (!dfn[v]) {
			tarjan(v);
			low[u] = std::min(low[u], low[v]);
			if (low[v] == dfn[u]) {
				int square = ++idx;
				while (stk[top] != u) {
					G[idx].emplace_back(stk[top]);
					G[stk[top]].emplace_back(idx);
					--top;
				}
				G[idx].emplace_back(stk[top]);
				G[stk[top]].emplace_back(idx);
			}
		}
		else low[u] = std::min(low[u], dfn[v]);
	}
}

void getSon(int u, int fa)
{
}
void initCut(int u, int tp)
{
}

void solve(void)
{
	read >> n >> m;
	for (int i = 1; i <= m; ++i) {
		read >> u >> v;
		G[u].emplace_back(v);
		G[v].emplace_back(u);
	}
	tarjan(1, 0);
	getSon(1, 0);
	initCut(1, 1);
	for (int i = 1, sz; i <= m; ++i) {
		read >> sz;
		std::vector<int> city(sz);
		for (int j = 0; j < sz; ++j)
			read >> city[j];
		auto cmp = [](int a, int b)
		{ return id[a] < id[b]; };
		std::sort(city.begin(), city.end(), cmp);
		int top = 0;
		stk[++top] = 1;
		int res = 0;
		for (auto u : city) {
			int d = LCA(stk[top], u);
			if (d != stk[top]) {
				while (id[d] < id[stk[top - 1]]) {
					--top;
					res += dis[stk[top]] - dis[stk[top - 1]];
				}
				res += dis[stk[top]] - dis[d];
				if (d != stk[top - 1])
					stk[top] = d;
				else
					--top;
			}
		}
		printf("%d\n", res);
	}
}

int main(void)
{
	int T; read >> T;
	while (T--) {
		solve();
		clear();
	}
	return 0;
}
