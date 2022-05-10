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

using i64 = long long;
const int mod = 998244353, N = 75;
inline int Mod(int x) { return x >= mod ? x - mod : x; }

struct ModInt
{
	int val;
	inline ModInt(void) {}
	inline ModInt(int x) { val = x; }
	inline ModInt operator+(const ModInt &other) const
	{ return Mod(val + other.val); }
	inline ModInt operator-(const ModInt &other) const
	{ return Mod(val + mod - other.val); }
	inline ModInt operator*(const ModInt &other) const
	{ return 1ll * val * other.val % mod; }
	inline void operator+=(const ModInt &other)
	{ val = Mod(val + other.val); }
};

int n, V, totSum;
int a[N], v[N], cnt[1010], vis[1010];
ModInt f[70 * 2 + 10][56000 * 2 + 10];
ModInt fac[N], inv[N];

inline ModInt C(int m, int n)
{ return fac[m] * inv[n] * inv[m - n]; }
inline ModInt calc(int val)
{
	for (int i = 1; i <= n; ++i)
		v[i] = a[i] - val;
	for (int i = -n; i <= n; ++i)
		for (int j = -totSum; j <= totSum; ++j)
			f[i + 70][j + 56000] = 0;
	// f[x][y] 表示 中位数差值为 x, 平均数差值为 y 时的方案数
	// x: -70 -> +70, y: -56000->+56000
	f[0 + 70][0 + 56000] = 1;
	for (int k = 1; k <= n; ++k) {
		if (v[k] < 0) {
			for (int i = -n; i <= n; ++i)
				for (int j = totSum; j >= -totSum; --j)
					if (f[i + 70][j + 56000].val)
						f[i - 1 + 70][j + v[k] + 56000] += f[i + 70][j + 56000];
		}
		if (v[k] > 0) {
			for (int i = n; i >= -n; --i)
				for (int j = -totSum; j <= totSum; ++j)
					if (f[i + 70][j + 56000].val)
						f[i + 1 + 70][j + v[k] + 56000] += f[i + 70][j + 56000];
		}
	}
	ModInt res = 0, ans = 0;
	for (int i = -totSum; i < 0; ++i)
		res += f[0 + 70][i + 56000];
	for (int i = 1; i <= cnt[val]; i += 2)
		ans += res * C(cnt[val], i);
	return ans;
}
inline ModInt qpow(ModInt base, int k)
{
	ModInt res = 1;
	while (k) {
		if (k & 1) res = res * base;
		k >>= 1;
		base = base * base;
	}
	return res;
}
inline ModInt getInv(ModInt x) { return qpow(x, mod - 2); }

int main(void)
{
	fac[0] = 1;
	for (int i = 1; i < N; ++i)
		fac[i] = fac[i - 1] * i;
	inv[N - 1] = getInv(fac[N - 1]);
	for (int i = N - 2; i >= 0; --i)
		inv[i] = inv[i + 1] * (i + 1);
	read >> n >> V;
	for (int i = 1; i <= n; ++i) {
		read >> a[i];
		++cnt[a[i]];
		totSum += a[i];
	}
	std::sort(a + 1, a + 1 + n);
	ModInt res = 0;
	for (int i = 1; i <= n; ++i)
		if (!vis[a[i]]) {
			vis[a[i]] = 1;
			res += calc(a[i]);
		}
	printf("%d\n", res.val);
	return 0;
}
