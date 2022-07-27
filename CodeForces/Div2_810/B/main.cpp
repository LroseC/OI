#include <vector>
#include <climits>
#include <cstring>
#include <iostream>
#include <algorithm>

#define read std::cin
using i32 = int;
using i64 = long long;
using vi32 = std::vector<i32>;
using PII = std::pair<i32, i32>;
const int N = 1e5 + 10;

int n, m;
i32 val[N], cnt[N];

void work(void)
{
	read >> n >> m;
	for (int i = 1; i <= n; ++i) {
		read >> val[i];
	}
	std::fill(cnt + 1, cnt + 1 + n, 0);
	std::vector<PII> e;
	for (int i = 1; i <= m; ++i) {
		i32 u, v;
		read >> u >> v;
		e.emplace_back(u, v);
		cnt[u] += 1;
		cnt[v] += 1;
	}
	if (m % 2 == 0) {
		puts("0");
		return;
	}
	i32 res = INT_MAX;
	for (int i = 1; i <= n; ++i) {
		if (cnt[i] & 1) res = std::min(res, val[i]);
	}
	for (int i = 0; i < m; ++i) {
		if (cnt[e[i].first] % 2 == 0 && cnt[e[i].second] % 2 == 0)
			res = std::min(res, val[e[i].first] + val[e[i].second]);
	}
	printf("%d\n", res);
}

int main(void)
{
	//Think twice, code once.
	std::ios::sync_with_stdio(false);
	i32 tt; read >> tt;
	while (tt--) {
		work();
	}
	return 0;
}
