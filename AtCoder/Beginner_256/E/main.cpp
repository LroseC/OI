#include <vector>
#include <iostream>
#include <algorithm>

using i64 = long long;
using vint = std::vector<int>;
using PII = std::pair<int, int>;
const int N = 2e5 + 10;

int stk[N], top;

int dfs(int u, vint &vis, vint &fa, vint &w)
{
	if (vis[u]) {
		int res = w[u];
		while (top && stk[top] != u) {
			res = std::min(res, w[stk[top]]);
			--top;
		}
		if (!top) return 0;
		return res;
	}
	vis[u] = 1;
	stk[++top] = u;
	return dfs(fa[u], vis, fa, w);
}

int main(void)
{
	//Think twice, code once.
	std::ios::sync_with_stdio(false);
	int n; std::cin >> n;
	vint fa(n), w(n), vis(n);
	for (int i = 0; i < n; ++i) {
		std::cin >> fa[i];
		--fa[i];
	}
	for (int i = 0; i < n; ++i) {
		std::cin >> w[i];
	}
	i64 res = 0;
	for (int i = 0; i < n; ++i)
		if (!vis[i]) {
			top = 0;
			res += dfs(i, vis, fa, w);
		}
	std::cout << res << '\n';
	return 0;
}
