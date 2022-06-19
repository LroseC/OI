#include <map>
#include <vector>
#include <iostream>
#include <algorithm>

using i64 = long long;

int main(void)
{
	std::ios::sync_with_stdio(false);
	int tt; std::cin >> tt;
	while (tt--) {
		int n, m;
		std::cin >> n >> m;
		std::map<int, int> M;
		std::vector<int> a(n);

		M[-1] = 2e9, M[n] = -2e9;
		for (int i = 0, pre = 2e9; i < n; ++i) {
			std::cin >> a[i];
			if (a[i] < pre) {
				pre = a[i];
				M[i] = a[i];
			}
		}
		while (m--) {
			int k, d;
			std::cin >> k >> d;
			k = k - 1;
			a[k] -= d;
			if (M.count(k)) {
				M[k] = a[k];
				auto it = M.upper_bound(k);
				while (it->second >= a[k]) {
					it = M.erase(it);
				}
			}
			else {
				auto it = std::prev(M.upper_bound(k));
				if (a[k] < it->second) {
					M[k] = a[k];
					it = M.upper_bound(k);
					while (it->second >= a[k]) {
						it = M.erase(it);
					}
				}
			}
			std::cout << M.size() - 2 << ' ';
		}
		std::cout << '\n';
	}
	return 0;
}
