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
const int N = 1e5 + 10, M = 2e5 + 10;

i32 n, m, S = -1, T = -1;
i32 last[N], inEdge[N], outEdge[N];
vi32 G[N];
i32 stk[M], top;

void dfs(i32 u)
{
	i32 &e = last[u];
	while (e < G[u].size()) {
		i32 v = G[u][e];
		e += 1;
		dfs(v);
	}
	stk[++top] = u;
}

int main(void)
{
	//Think twice, code once.
	read >> n >> m;
	for (int i = 1; i <= m; ++i) {
		i32 u, v;
		read >> u >> v;
		G[u].emplace_back(v);
		inEdge[v] += 1;
		outEdge[u] += 1;
	}
	for (int i = 1; i <= n; ++i) {
		std::sort(G[i].begin(), G[i].end());
	}
	for (int i = 1; i <= n; ++i) {
		if (inEdge[i] == outEdge[i] + 1) {
			if (T != -1) {
				puts("No");
				return 0;
			}
			T = i;
		}
		else if (inEdge[i] + 1 == outEdge[i]) {
			if (S != -1) {
				puts("No");
				return 0;
			}
			S = i;
		}
		else if (inEdge[i] != outEdge[i]){
			puts("No");
			return 0;
		}
	}
	if (S == -1 && T == -1) {
		dfs(1);
	}
	else if (S != -1 && T != -1) {
		dfs(S);
	}
	else {
		puts("No");
		return 0;
	}
	for (int i = top; i >= 1; --i)
		printf("%d ", stk[i]);
	puts("");
	return 0;
}
