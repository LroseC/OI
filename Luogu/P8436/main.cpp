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

using i32 = int;
using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;
using vi32 = std::vector<i32>;
using PII = std::pair<int, int>;
const int N = 5e5 + 10, M = 4e6 + 10;

i32 n, m, idx, cnt, dfnCnt;
i32 dfn[N], low[N], id[N];
i32 head[N], to[M], nex[M], isCut[M];
vi32 ver[N];

void addEdge(i32 u, i32 v)
{
	idx += 1;
	nex[idx] = head[u];
	head[u] = idx;
	to[idx] = v;
}

void tarjan(i32 u, i32 fa)
{
	dfn[u] = low[u] = ++dfnCnt;
	for (int e = head[u]; e; e = nex[e])
		if (to[e] != fa) {
			i32 v = to[e];
			if (!dfn[to[e]]) {
				tarjan(v, u);
				low[u] = std::min(low[u], low[v]);
				if (low[v] > dfn[u]) isCut[e] = isCut[e ^ 1] = 1;
			}
			else low[u] = std::min(low[u], dfn[v]);
		}
}
void get(i32 u, i32 fa)
{
	id[u] = cnt;
	ver[cnt].emplace_back(u);
	for (int e = head[u]; e; e = nex[e])
		if (!isCut[e] && !id[to[e]] && to[e] != fa) {
			get(to[e], u);
		}
}

int main(void)
{
	//Think twice, code once.
	read >> n >> m;
	for (int i = 1; i <= m; ++i) {
		i32 u, v;
		read >> u >> v;
		addEdge(u, v);
		addEdge(v, u);
	}
	for (int i = 1; i <= n; ++i)
		if (!dfn[i]) tarjan(i, i);
	for (int i = 1; i <= n; ++i)
		if (!id[i]) {
			cnt += 1;
			get(i, i);
		}
	printf("%d\n", cnt);
	for (int i = 1; i <= cnt; ++i, puts("")) {
		printf("%d ", ver[i].size());
		for (auto nd : ver[i]) printf("%d ", nd);
	}
	return 0;
}
