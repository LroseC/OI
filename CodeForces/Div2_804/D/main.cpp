#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>

using i64 = long long;
using vint = std::vector<int>;
using PII = std::pair<int, int>;

inline void work(void)
{
	int n; std::cin >> n;
	vint a(n), del(n);
	vint pre(n), nex(n);
	for (int i = 0; i < n; ++i)
		std::cin >> a[i];
	int ans = 0;
	std::queue<PII> q0, q1;
	for (int res = 0; res < n; ++res) {
		std::cerr << "res = " << a[res] << '\n';
		std::fill(del.begin(), del.end(), 0);
		for (int i = 0; i < n; ++i) {
			pre[i] = i - 1;
			nex[i] = i + 1;
		}
		for (int i = 1; i < n; ++i)
			if (a[i - 1] != a[i]) {
				if (a[i - 1] == a[res] || a[i] == a[res])
					q1.emplace(i - 1, i);
				else
					q0.emplace(i - 1, i);
			}
		int cnt = n;
		while (q0.size() + q1.size()) {
			PII u;
			if (q0.size()) {
				u = q0.front(); q0.pop();
			}
			else {
				u = q1.front(); q1.pop();
			}

			if (!del[u.first] && !del[u.second]) {
				std::cerr << u.first << ',' << u.second << '\n';
				cnt -= 2;
				int pr = pre[u.first];
				int nx = nex[u.second];
				del[u.first] = del[u.second] = 1;
				if (pr != -1)
					nex[pr] = nx;
				if (nx != n)
					pre[nx] = pr;
				if (pr != -1 && nx != n && a[pr] != a[nx]) {
					if (a[pr] == a[res] || a[nx] == a[res])
						q1.emplace(pr, nx);
					else
						q0.emplace(pr, nx);
				}
			}
		}
		ans = std::max(ans, cnt);
	}
	std::cout << ans << '\n';
}

int main(void)
{
	//Think twice, code once.
	std::ios::sync_with_stdio(false);
	int tt; std::cin >> tt;
	while (tt--) {
		work();
	}
	return 0;
}
