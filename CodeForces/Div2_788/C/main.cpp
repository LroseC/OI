#include <vector>
#include <iostream>
#include <algorithm>

using i64 = long long;
using PII = std::pair<int, int>;
using vint = std::vector<int>;
const int mod = 1e9 + 7, N = 5e5 + 10;

int inva[N];

void dfs(int u, vint &b, vint &vis)
{
	if (vis[u]) return;
	vis[u] = 1;
	dfs(inva[b[u]], b, vis);
}

int main(void)
{
	//Think twice, code once.
	std::ios::sync_with_stdio(false);
	int tt; std::cin >> tt;
	while (tt--) {
		int n; std::cin >> n;
		std::vector<int> a(n), b(n), c(n), vis(n);
		for (int i = 0; i < n; ++i) {
			std::cin >> a[i];
			inva[a[i]] = i;
		}
		for (int i = 0; i < n; ++i) {
			std::cin >> b[i];
		}
		for (int i = 0; i < n; ++i) {
			std::cin >> c[i];
			if (c[i] != 0) dfs(i, b, vis);
		}
		int res = 1;
		for (int i = 0; i < n; ++i)
			if (!vis[i]) {
				dfs(i, b, vis);
				if (a[i] != b[i])
					res = 1ll * res * 2 % mod;
			}
		std::cout << res << '\n';
	}
	return 0;
}
