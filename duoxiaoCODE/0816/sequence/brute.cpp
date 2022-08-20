#include <cctype>
#include <cstdio>
#include <cstring>
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

i32 n, K, res;
i32 str[9];
bool vis[9];
i32 ans[10][10];

bool check(void)
{
	for (int i = 0; i < K; ++i) {
		bool sec = 1;
		for (int j = 0; j < i; ++j) {
			std::memset(vis, 0, sizeof vis);
			if (vis[str[j]]) {
				sec = 0;
				break;
			}
			vis[str[j]] = 1;
		}
		for (int l = i; l < n; l += K) {
			std::memset(vis, 0, sizeof vis);
			for (int j = 0; j < K && j + l < n; ++j) {
				if (vis[str[j + l]]) {
					sec = 0;
					break;
				}
				vis[str[j + l]] = 1;
			}
		}
		if (sec) return 1;
	}
	return 0;
}
void dfs(i32 id)
{
	if (id == n) {
		res += check();
		return;
	}
	for (int i = 1; i <= K; ++i) {
		str[id] = i;
		dfs(id + 1);
	}
}

int main(void)
{
#ifndef DEBUG
	freopen("sequence.in", "r", stdin);
	freopen("sequence.out", "w", stdout);
#endif
	//Think twice, code once.
	for (n = 1; n <= 8; ++n)
		for (K = 1; K <= 8; ++K) {
			res = 0;
			dfs(0);
			printf("ans[%d][%d] = %d;\n", n, K, res);
		}
	return 0;
}
