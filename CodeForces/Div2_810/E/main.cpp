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
const int N = 2e5 + 10, mod = 998244353;
inline int Mod(int x) { return x >= mod ? x - mod : x; }

struct ModInt
{
	int val;
	ModInt(int x = 0) { val = x; }
	ModInt operator+(const ModInt &other) const
	{ return Mod(val + other.val); }
	ModInt operator-(const ModInt &other) const
	{ return Mod(val + mod - other.val); }
	ModInt operator*(const ModInt &other) const
	{ return 1ll * val * other.val % mod; }
};

i32 n;
char str[N];

int main(void)
{
	//Think twice, code once.
	std::ios::sync_with_stdio(false);
	read >> str + 1;
	n = strlen(str + 1);
	for (int i = 1; i <= n; ++i) {
		str[i] -= '0';
	}
	return 0;
}
/*
   g[i][s] 表示考虑到第 i 位, 考虑上界状态为 s, 满足 (a ^ b) > (a ^ c) + (b ^ c) 的方案数.
   f[i][s] 表示考虑到第 i 位, 考虑上界状态为 s, (a ^ b), (a ^ c) 和 (b ^ c) 满足三角形不等式的方案数.
*/
