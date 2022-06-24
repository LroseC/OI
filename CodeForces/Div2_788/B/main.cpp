#include <set>
#include <queue>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using i64 = long long;
using PII = std::pair<int, int>;

int find(int x, std::vector<int> &fa)
{ return x == fa[x] ? x : fa[x] = find(fa[x], fa); }

int main(void)
{
	std::ios::sync_with_stdio(false);
	int tt; std::cin >> tt;
	while (tt--) {
		int n; std::cin >> n;
		std::set<char> S;
		std::vector<int> pre(n), del(n);
		std::queue<int> q, t;
		std::string s;
		std::cin >> s;
		int K; std::cin >> K;
		for (int i = 0; i < K; ++i) {
			char c; std::cin >> c;
			S.insert(c);
		}
		for (int i = 0; i < n; ++i) {
			pre[i] = i - 1;
			if (S.count(s[i])) {
				q.emplace(i);
			}
		}
		int tot = n, res = 0;
		for (int i = n - 1; i >= 0; --i) {
			if (!S.count(s[i])) --tot;
			else break;
		}
		while (tot != 1 && q.size()) {
			++res;
			while (q.size()) {
				int u = q.front(); q.pop();
				if (del[u]) continue;
				if (pre[u] != -1) {
					--tot;
					del[pre[u]] = 1;
					pre[u] = pre[pre[u]];
					t.emplace(u);
				}
			}
			std::swap(q, t);
		}
		std::cout << res << '\n';
	}
	return 0;
}
