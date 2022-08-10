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
using PII = std::pair<i32, i32>;
const int N =5e5 + 10;

i32 n, m, cnt;
vi32 G[N], ver[N];
i32 dfn[N], low[N], dfnCnt;
bool isCut[N];
i32 stk[N], top;

void tarjan(i32 u, i32 fa)
{
	i32 childCnt = 0;
	dfn[u] = low[u] = ++dfnCnt;
	if (!G[u].size()) {
		cnt += 1;
		ver[cnt].emplace_back(u);
		return;
	}
	stk[++top] = u;
	for (int v : G[u])
		if (v != fa) {
			if (!dfn[v]) {
				++childCnt;
				tarjan(v, u);
				low[u] = std::min(low[u], low[v]);
				if (u == fa || (low[v] >= dfn[u] && u != fa)) {
					isCut[u] = 1;
					cnt += 1;
					i32 tmp = -1;
					while (tmp != v) {
						tmp = stk[top];
						ver[cnt].emplace_back(stk[top]);
						top -= 1;
					}
					ver[cnt].emplace_back(u);
				}
			}
			else low[u] = std::min(low[u], dfn[v]);
		}
	if (u == fa && childCnt > 1) {
		isCut[u] = 1;
	}
}

int main(void)
{
	//Think twice, code once.
	read >> n >> m;
	for (int i = 1; i <= m; ++i) {
		i32 u, v;
		read >> u >> v;
		if (u == v) continue;
		G[u].emplace_back(v);
		G[v].emplace_back(u);
	}
	for (int i = 1; i <= n; ++i)
		if (!dfn[i]) tarjan(i, i);
	printf("%d\n", cnt);
	for (int i = 1; i <= cnt; ++i) {
		printf("%d ", ver[i].size());
		for (auto v : ver[i]) printf("%d ", v);
		puts("");
	}
	return 0;
}
