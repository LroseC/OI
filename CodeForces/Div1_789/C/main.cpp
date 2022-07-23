#include <vector>
#include <climits>
#include <iostream>
#include <algorithm>

#define read std::cin
using i32 = int;
using i64 = long long;
using vi32 = std::vector<i32>;
using PII = std::pair<i32, i32>;

i32 getSz(int u, vi32 &vis, vi32 &G)
{
	vis[u] = 1;
	if (!vis[G[u]])
		return getSz(G[u], vis, G) + 1;
	return 1;
}

int main(void)
{
	//Think twice, code once.
#ifndef DEBUG
	std::ios::sync_with_stdio(false);
#endif
	int tt; read >> tt;
	while (tt--) {
		i32 n; read >> n;
		vi32 p1(n), p2(n), vis(n), G(n);
		for (int i = 0; i < n; ++i) {
			read >> p1[i];
			p1[i] -= 1;
		}
		for (int i = 0; i < n; ++i) {
			read >> p2[i];
			p2[i] -= 1;
			G[p2[i]] = p1[i];
		}
		int l = 1, r = n;
		i64 res = 0;
		for (int i = 0; i < n; ++i) {
			if (vis[i]) continue;
			int sz = getSz(i, vis, G);
			while (sz >= 2) {
				res += (r - l) * 2;
				l += 1;
				r -= 1;
				sz -= 2;
			}
		}
		printf("%lld\n", res);
	}
	return 0;
}
