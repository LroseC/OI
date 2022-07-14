#include <vector>
#include <iostream>
#include <algorithm>

using i64 = long long;
using vint = std::vector<int>;
using PII = std::pair<int, int>;
const int N = 2e5 + 10;

vint G[N];

int main(void)
{
	//Think twice, code once.
	std::ios::sync_with_stdio(false);
	int tt; std::cin >> tt;
	while (tt--) {
		int n, x; std::cin >> n, x;
		for (int i = 1; i <= n; ++i) G[i].clear();
		for (int i = 1; i < n; ++i) {
			int u, v; std::cin >> u >> v;
			G[u].emplace_back(v);
			G[v].emplace_back(u);
		}
		int root = 1;
		for (int i = 1; i <= n; ++i)
			if (G[i].size() > G[root].size()) root = i;
		vint a(n);
		for (int i = 0; i < n; ++i) {
			std::cin >> a[i];
		}
		if (G[root].size() != n - 1) {
			puts("Alice");
			continue;
		}
		if (std::is_sorted(a.begin(), a.end())) {
			puts("Alice");
			continue;
		}
		vint b(n);
		for (int i = 0; i < n; ++i) b[i] = a[i];
		std::sort(b.begin(), b.end());
		bool fail = 0;
		for (int i = 0; i < n; ++i) {
			if (a[i] != b[i]) {
				++cnt;
				if (a[i] == root || b[i] == root) fail = 1;
			}
		}
		if (cnt > 2 || fail) puts("Bob");
		else puts("Alice");
	}
	return 0;
}
