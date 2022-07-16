#include <set>
#include <vector>
#include <climits>
#include <iostream>
#include <algorithm>

#define read std::cin
using i64 = long long;
using vint = std::vector<int>;
using PII = std::pair<int, int>;
const int M = 5e6 + 10;

int v[M], prime[M], idx;

void getPrime(void)
{
	for (int i = 2; i < M; ++i) {
		if (!v[i]) {
			v[i] = i;
			prime[idx++] = i;
		}
		for (int j = 0; j < idx && i * prime[j] < M; ++j) {
			v[i * prime[j]] = prime[j];
			if (v[i] == prime[j]) break;
		}
	}
}

int main(void)
{
	//Think twice, code once.
	std::ios::sync_with_stdio(false);
	getPrime();
	int tt; read >> tt;
	while (tt--) {
		int n, m; read >> n >> m;
		vint a(n);
		std::vector<vint> pos(m + 2);
		std::vector<vint> S(n), S2(n);
		int maxx = 0, minx = m;
		bool flag = 0;
		for (int i = 0; i < n; ++i) {
			read >> a[i];
			if (a[i] == 1) flag = 1;
			for (int x = a[i]; x != 1; x /= v[x]) {
				S[i].emplace(v[x]);
				pos[v[x] + 1].emplace_back(i);
				maxx = std::max(maxx, v[x]);
				minx = std::min(minx, v[x]);
			}
		}
		if (flag) {
			std::cout << maxx - 1 << '\n';
			continue;
		}
		int res = INT_MAX;
		for (; minx <= m; ++minx) {
			bool fail = 0;
			for (auto p : pos[minx]) {
				while (S[p].size() > 1 && *S[p].begin() < minx) {
					auto it = S[p].begin();
					auto jt = std::next(it);
					int v = (*it) * (*jt);
					S[p].erase(it);
					S[p].erase(jt);
					maxx = std::max(maxx, v);
					pos[v + 1].emplace_back(p);
					S[p].insert(v);
				}
				if (*S[p].begin() < minx) fail = 1;
			}
			if (fail) break;
			res = std::min(res, maxx - minx);
		}
		std::cout << res << '\n';
	}
	return 0;
}
