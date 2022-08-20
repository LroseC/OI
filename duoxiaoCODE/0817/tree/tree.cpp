#include <set>
#include <vector>
#include <cctype>
#include <cstdio>
#include <cstdint>
#include <algorithm>

struct FSI
{
	template<typename T>
	FSI& operator>>(T &res)
	{
		res = 0; T f = 1; char ch = getchar();
		while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
		while (isdigit(ch)) { res = res * 10 + (ch - '0') * f; ch = getchar(); }
		return *this;
	}
} read;

using i32 = int32_t;
using i64 = int64_t;
using PII = std::pair<i32, i32>;
const int N = 1e6 + 10;

i32 n;
char str[N];
i32 w[N], sum[N];
std::vector<i32> G[N];

i32 dfs(i32 u, i32 fa, i32 state)
{
	i32 sz = 1;
	for (int v : G[u])
		if (v != fa && (state >> (v - 1) & 1)) sz += dfs(v, u, state);
	return sz;
}
bool check(i32 state)
{
	for (int j = 0; j < n; ++j)
		if (state >> j & 1) {
			return dfs(j + 1, j + 1, state) == __builtin_popcount(state);
		}
	return 1;
}
i32 getRes(i32 state)
{
	i32 res = 0;
	for (int j = 0; j < n; ++j) {
		if (state >> j & 1) {
			res += w[j + 1];
		}
		else {
			res -= w[j + 1];
		}
	}
	return std::abs(res);
}

int main(void)
{
#ifndef DEBUG
	freopen("tree.in", "r", stdin);
	freopen("tree.out", "w", stdout);
#endif
	//Think twice, code once.
	read >> n;
	for (int i = 1; i <= n; ++i) {
		read >> w[i];
	}
	bool flag = 1;
	for (int i = 2; i <= n; ++i) {
		i32 u;
		read >> u;
		if (u != i - 1) flag = 0;
		G[u].emplace_back(i);
		G[i].emplace_back(u);
	}
	if (n <= 20) {
		i32 res = 0x3f3f3f3f;
		i32 ans = 0;
		for (int i = 0; i < 1 << n; ++i) {
			if (check(i)) {
				i32 tmp = getRes(i);
				if (tmp < res) {
					res = tmp;
					ans = i;
				}
			}
		}
		for (int i = 0; i < n; ++i)
			putchar((ans >> i & 1) + '0');
		puts("");
		return 0;
	}
	if (flag) {
		i32 res = 0x3f3f3f3f;
		PII ans;
		std::set<PII> S;
		for (int i = 1; i <= n; ++i) {
			sum[i] = sum[i - 1] + w[i];
			auto it = S.lower_bound(std::make_pair(sum[i], i));
			if (it != S.end()) {
				i32 tmp = std::abs(it->first - sum[i]);
				if (tmp < res) {
					res = tmp;
					ans = std::make_pair(it->second, i) ;
				}
			}
			if (it != S.begin()) {
				--it;
				i32 tmp = std::abs(it->first - sum[i]);
				if (tmp < res) {
					res = tmp;
					ans = std::make_pair(it->second, i);
				}
			}
			S.insert(std::make_pair(sum[i], i));
		}
		for (int i = 1; i <= n; ++i) str[i] = '0';
		for (int i = ans.first; i <= ans.second; ++i) str[i] = '1';
		printf("%s\n", str + 1);
	}
	return 0;
}
