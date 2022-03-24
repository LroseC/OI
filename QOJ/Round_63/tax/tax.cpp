#include <cctype>
#include <cstdio>

struct FSI
{
	template<typename T>
	FSI& operator>>(T &res)
	{
		res = 0; T f = 1; char ch = getchar();
		while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
		while (isdigit(ch)) { res = res * 10 + ch - '0'; ch = getchar(); }
		res = res * f; return *this;
	}
} read;

using i64 = long long;
const int mod = 998244353;
inline int Mod(int x) { return x >= mod ? x - mod : x; }

i64 A, B, C, L, R;

inline int getInv(int base)
{
	int k = mod - 2;
	int res = 1;
	while (k) {
		if (k & 1) res = 1ll * res * base % mod;
		k >>= 1;
		base = 1ll * base * base % mod;
	}
	return res;
}
int S1(i64 x)
{
	int a = x % mod;
	int b = (x + 1) % mod;
	int c = (2 * x + 1) % mod;
	return 1ll * a * b % mod * c % mod * getInv(6) % mod;
}
int S2(i64 x)
{
	int a = x % mod;
	int b = (x + 1) % mod;
	return 1ll * a * b % mod * getInv(2) % mod;
}
int S3(i64 x) { return x % mod; }
int calc(i64 R)
{
	if (R == 0) return 0;
	int res = 0;
	for (i64 i = 1, j; i <= R; i = j + 1) {
		j = R / (R / i);
		int tmp = (1ll * A * S1(R / i) % mod + 1ll * B * S2(R / i) % mod+ 1ll * C * S3(R / i) % mod) % mod;
		res = (res + 1ll * tmp * ((j - i + 1) % mod)) % mod;
	}
	return res;
}

int main(void)
{
//	freopen("tax.in", "r", stdin);
//	freopen("tax.out", "w", stdout);
	read >> A >> B >> C >> L >> R;
	printf("%d\n", Mod(calc(R) - calc(L - 1) + mod));
	return 0;
}
