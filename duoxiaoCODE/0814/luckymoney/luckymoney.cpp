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
using u32 = uint32_t;
using u64 = uint64_t;
using vi32 = std::vector<i32>;
using PII = std::pair<i32, i32>;

i32 n, mod;
i32 grid[110][110];
inline int Mod(i32 x) { return x >= mod ? x - mod : x; }

int main(void)
{
#ifndef DEBUG
	freopen("luckymoney.in", "r", stdin);
	freopen("luckymoney.out", "w", stdout);
#endif
	//Think twice, code once.
	read >> n >> mod;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j) read >> grid[i][j];
	std::vector<i32> per(n);
	for (int i = 0; i < n; ++i) per[i] = i + 1;
	do {
		bool sec = 1;
		i32 tot = 0;
		for (int i = 0; i < n; ++i) {
			if (grid[i + 1][per[i]] == -1)
				sec = 0;
			tot = Mod(tot + grid[i + 1][per[i]]);
		}
		if (sec && tot == 0) {
			puts("Yes");
			return 0;
		}
	} while (std::next_permutation(per.begin(), per.end()));
	puts("No");
	return 0;
}
