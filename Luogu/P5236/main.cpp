#include <vector>
#include <cctype>
#include <cstdio>
#include <cstdint>
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

using i32 = int32_t;
using i64 = int64_t;
using u32 = uint32_t;
using u64 = uint64_t;
using vi32 = std::vector<i32>;
using PII = std::pair<i32, i32>;
const int N = 2e4 + 10;

i32 n, m, q;
std::vector<i32> T[N];
std::vector<PII> G[N];
i32 low[N], dfn[N], id[N], stk[N], top, dfnCnt, dccCnt;

void tarjan(i32 u, i32 fa)
{
	low[u] = dfn[u] = ++dfnCnt;
	i32 sonCnt = 0;
	stk[++top] = u;
	for (auto e : G[u]) {
		i32 v = e.first, w = e.second;
		if (v == fa) continue;
		if (!dfn[v]) {
			sonCnt += 1;
			tarjan(v, u);
			low[u] = std::min(low[u], low[v]);
			if (u == fa || (u != fa && low[v] >= dfn[u])) {
				i32 tmp;
				dccCnt += 1;
				do {
					tmp = stk[top--];
					T[dccCnt + n].emplace_back(tmp);
					T[tmp].emplace_back(dccCnt + n);
					id[tmp] = dccCnt;
				} while (tmp != v);
				tmp = u;
				T[dccCnt + n].emplace_back(tmp);
				T[tmp].emplace_back(dccCnt + n);
				id[tmp] = dccCnt;
			}
		}
		else low[u] = std::min(low[u], dfn[v]);
	}
}

int main(void)
{
	//Think twice, code once.
	read >> n >> m >> q;
	for (int i = 1; i <= m; ++i) {
		i32 u, v, w;
		read >> u >> v >> w;
		G[u].emplace_back(v, w);
		G[v].emplace_back(u, w);
	}
	for (int i = 1; i <= n; ++i)
		if (!dfn[i]) {
			tarjan(i, i);
		}
	// for (int i = 1; i <= dccCnt; ++i) {
	// 	printf("%d:\n", i);
	// 	for (auto v : T[i + n]) {
	// 		printf("%d ", v);
	// 	}
	// 	puts("");
	// }
	return 0;
}
