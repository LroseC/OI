#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using i64 = long long;
const int N = 210;

std::string s;
std::vector<int> G[N];

void dfs(int u, std::vector<int> &vis, std::vector<char> &t)
{
	if (vis[u]) {
		return;
	}
	vis[u] = 1;
	t.emplace_back(s[u]);
	for (int v : G[u]) {
		dfs(v, vis, t);
	}
}

int main(void)
{
	std::ios::sync_with_stdio(false);
	int tt; std::cin >> tt;
	while (tt--) {
		int n; std::cin >> n;
		std::cin >> s;
		std::vector<int> p(n), vis(n);
		for (int i = 0; i < n; ++i) {
			std::cin >> p[i];
			G[i].emplace_back(p[i] - 1);
		}
		i64 ans = 1;
		for (int i = 0; i < n; ++i) {
			std::vector<char> t;
			dfs(i, vis, t);
			if (!t.size()) continue;
			int l = t.size();
			t.resize(l << 1);
			for (int j = 0; j < l; ++j) {
				t[j + l] = t[j];
			}
			i64 res = l;
			for (int j = 1; j < l; ++j) {
				bool flag = 1;
				for (int k = 0; k < l; ++k)
					if (t[k] != t[j + k]) {
						flag = 0;
						break;
					}
				if (flag) {
					res = j;
					break;
				}
			}
			ans = ans / std::__gcd(ans, res) * res;
		}
		std::cout << ans << '\n';
		for (int i = 0; i < n; ++i) {
			G[i].clear();
		}
	}
	return 0;
}
