#include <vector>
#include <cctype>
#include <cstdio>
#include <climits>
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

using i32 = int;
using i64 = long long;
using vi32 = std::vector<i32>;
using PII = std::pair<i32, i32>;
const int N = 3e3 + 10, mod = 998244353;
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
};

i32 n;
i32 a[N];
ModInt f[2][N][N], presum[N][N];

int main(void)
{
	//Think twice, code once.
	read >> n;
	for (int i = 1; i <= n; ++i) {
		read >> a[i];
	}
	f[0][0][0] = 1;
	a[n + 1] = a[n] + 1;
	for (int i = 1; i <= n + 1; ++i) {
		for (int j = 0; j <= i; ++j) {
			presum[j][0] = f[i + 1 & 1][j][0];
			for (int k = 1; k <= a[i]; ++k)
				presum[j][k] = presum[j][k - 1] + f[i + 1 & 1][j][k];
		}
		for (int j = 0; j <= i; ++j) {
			for (int k = 0; k < a[i]; ++k)
				f[i & 1][j][k] = presum[j][k];
			if (j) f[i & 1][j][a[i]] = presum[j - 1][a[i]];
		}
	}
	for (int i = 0; i <= n; ++i)
		printf("%d ", f[n + 1 & 1][i][a[n]].val);
	return 0;
}
