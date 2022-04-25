#include <cctype>
#include <cstdio>

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

using i64 = long long;
const int mod = 998244353;

struct ModInt
{
	int val;

	ModInt(void) {}
	ModInt(int x) { val = x; }
	ModInt operator+(ModInt x) const
	{ return Mod(val + x.val); }
	ModInt operator-(ModInt x) const
	{ return Mod(val + mod - x.val); }
	ModInt operator*(ModInt x) const
	{ return 1ll * val * x.val % mod; }
};

bool v[2010];
int idx, prime[2010];

void initPrime(void)
{
	for (int i = 2; i <= 2000; ++i) {
		if (!v[i])
			prime[idx++] = i;
		for (int j = 1; j <= idx && i * prime[j] <= 2000; ++j) {
			v[i * prime[j]] = 1;
			if (i % prime[j] == 0) break;
		}
	}
	for (int i = 1; i <= 2000; ++i)
		for (int j = i; j <= 2000; j += i) {
			if (!cnt[j]) continue;
			for (int st = 0; st < 1 << 14; ++st) {
				bool flag = 1;
				for (int k = 0; k < 14; ++k)
					if ((st >> k & 1) && j % prime[k]) {
						flag = 0;
						break;
					}
				if (flag) f[i][st] = f[i][st] + cnt[j];
			}
		}
}

int main(void)
{
	initPrime();
	read >> n;
	for (int i = 1; i <= n; ++i) {
		read >> s[i];
		++cnt[s[i]];
	}
	read >> m;
	for (int i = 1, c; i <= m; ++i) {
		read >> c;
		for (int j = 1; j <= c; ++j)
			read >> p[j];
		std::sort(p + 1, p + 1 + c);
		int totState = 0;
		int res = qpow(2, n);
		for (int j = 1; j <= c; ++j) {
			if (p[j] > 43) {
				for (int st = 0; st < 1 << 14; ++st)
					res = res - qpow(2, n - f[p[j]][st]);
			}
			else
				totState |= 1 << id[p[j]];
		}
	}
	return 0;
}
/*
   显然，答案 = 总方案数 - 不合法方案数
   不合法方案数: 不含任意一个质数的方案数.
   考虑容斥求不合法方案数: 不含一个质数方案数 - 不含两个质数方案数 + 不含三个质数方案数...
   如何求不含一个质数的方案数？2^(tot - 含两个质数的数个数)
   把那个容斥式子直接拆了: sum (-1)^(质数个数) * 2^(tot - 含某几个质数的数的个数)
   可以状压枚举含的是哪几个质数.
   考虑根号分治经典做法: 对于一个数 a /in (1, 2000)，其大于 sqrt(2000) 的质因数必然最多只有一个。
*/
