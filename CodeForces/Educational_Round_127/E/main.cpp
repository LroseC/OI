#include <vector>
#include <climits>
#include <cstring>
#include <iostream>
#include <algorithm>

#define read std::cin
using i32 = int;
using i64 = long long;
using u64 = unsigned long long;
using vi32 = std::vector<i32>;
using vi64 = std::vector<i64>;
using PII = std::pair<i32, i32>;
const int N = (1 << 18) + 10, mod = 998244353;
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
	void operator+=(const ModInt &other)
	{ val = Mod(val + other.val); }
	void operator-=(const ModInt &other)
	{ val = Mod(val + mod - other.val); }
	void operator*=(const ModInt &other)
	{ val = 1ll * val * other.val % mod; }
};

i32 n;
char str[N];
ModInt f[N];
u64 hash[N];

void calc(int u)
{
	if ((u << 1) >= n) {
		hash[u] = str[u];
		f[u] = 1;
		return;
	}
	calc(u << 1);
	calc(u << 1 | 1);
	f[u] = f[u << 1] * f[u << 1 | 1];
	if (hash[u << 1] != hash[u << 1 | 1])
		f[u] *= 2;
	hash[u] = str[u];
	u64 left = std::min(hash[u << 1], hash[u << 1 | 1]);
	u64 right = std::max(hash[u << 1], hash[u << 1 | 1]);
	hash[u] += left * 131;
	hash[u] += right * 1331;
	hash[u] ^= left * right;
}

int main(void)
{
	//Think twice, code once.
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	std::cout.tie(0);
	read >> n;
	n = 1 << n;
	read >> str + 1;
	calc(1);
	printf("%d\n", f[1].val);
	return 0;
}
