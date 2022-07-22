#include <vector>
#include <climits>
#include <iostream>
#include <algorithm>

#define read std::cin
using i32 = int;
using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;
using vi32 = std::vector<i32>;
using vi64 = std::vector<i64>;
using PII = std::pair<int, int>;

const i32 N = 2e5 + 10;

i32 n, res = 0;
i32 fa[N], l[N], r[N], lim[N];
vi32 G[N];

void dfs(int u)
{
	for (int v : G[u]) {
		dfs(v);
		lim[u] = std::min(r[u], lim[u] + lim[v]);
	}
	if (lim[u] < l[u]) {
		++res;
		lim[u] = r[u];
	}
}
void work(void)
{
	read >> n;
	for (int i = 2; i <= n; ++i) {
		read >> fa[i];
		G[fa[i]].emplace_back(i);
	}
	for (int i = 1; i <= n; ++i) {
		read >> l[i] >> r[i];
	}
	dfs(1);
	printf("%d\n", res);
	res = 0;
	for (int i = 1; i <= n; ++i)
		G[i].clear();
	std::fill(lim + 1, lim + 1 + n, 0);
}

int main(void)
{
	//Think twice, code once.
#ifndef DEBUG
	std::ios::sync_with_stdio(false);
#endif
	i32 tt; read >> tt;
	while (tt--) {
		work();
	}
	return 0;
}
