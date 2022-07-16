#include <vector>
#include <climits>
#include <iostream>
#include <algorithm>

#define read std::cin
using i64 = long long;
using vint = std::vector<int>;
using PII = std::pair<int, int>;

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
	for (int i = 0; i < 10; ++i)
		printf("%d ", prime[i]);
	puts("");
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
		std::vector<vint> pos(m + 1);
		std::vector<std::set<int>> S(n);
		int maxx = 0;
		for (int i = 0; i < n; ++i) {
			read >> a[i];
			for (int x = a[i]; x != 1; x /= v[x]) {
				S[i].emplace(v[x]);
				pos[v[x]].emplace_back(i);
				maxx = std::max(maxx, v[x]);
			}
		}
		int res = INT_MAX;
		for (int minx = 0; minx <= m; ++minx) {
			bool fail = 0;
			for (auto p : pos[minx]) {
				while (S[p].size() > 1 && S[p].front() < minx) {
					auto it = S.begin();
					auto jt = std::next(it);
					maxx = std::max(maxx, (*it) * (*jt));
					pos[(*it) * (*jt)].emplace_back(p);
					S.insert((*it) * (*jt));
					S.erase(it);
					S.erase(jt);
				}
				if (S[p].front() < minx) fail = 1;
			}
			if (fail) break;
			res = std::min(maxx - minx);
		}
	}
	return 0;
}
