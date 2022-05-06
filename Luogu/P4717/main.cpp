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
const int N = 1 << 17, mod = 998244353;
inline int Mod(int x) { return x >= mod ? x - mod : x; }

struct ModInt
{
	int val;

	ModInt(void) {}
	ModInt(int x) { val = x; }
	ModInt operator+(const ModInt &other) const
	{ return Mod(val + other.val); }
	ModInt operator-(const ModInt &other) const
	{ return Mod(val + mod - other.val); }
	ModInt operator*(const ModInt &other) const
	{ return 1ll * val * other.val % mod; }
};
ModInt qpow(ModInt base, int k)
{
	ModInt res = 1;
	while (k) {
		if (k & 1) res = res * base;
		k >>= 1;
		base = base * base;
	}
	return res;
}
ModInt getInv(ModInt x) { return qpow(x, mod - 2); }

int n, m;
ModInt a[N], b[N], c[N];

void OR(ModInt f[], ModInt x)
{
	for (int l = 2, k = 1; l <= n; l <<= 1, k <<= 1)
		for (int i = 0; i < n; i += l)
			for (int j = 0; j < k; ++j)
				f[i + j + k] = f[i + j + k] + f[i + j] * x;
}
void AND(ModInt f[], ModInt x)
{
	for (int l = 2, k = 1; l <= n; l <<= 1, k <<= 1)
		for (int i = 0; i < n; i += l)
			for (int j = 0; j < k; ++j)
				f[i + j] = f[i + j] + f[i + j + k] * x;
}
void XOR(ModInt f[], ModInt x)
{
	for (int l = 2, k = 1; l <= n; l <<= 1, k <<= 1)
		for (int i = 0; i < n; i += l)
			for (int j = 0; j < k; ++j) {
				f[i + j] = f[i + j] + f[i + j + k];
				f[i + j + k] = f[i + j] - f[i + j + k] - f[i + j + k];
				f[i + j] = f[i + j] * x;
				f[i + j + k] = f[i + j + k] * x;
			}
}

int main(void)
{
	read >> m;
	n = 1 << m;
	for (int i = 0; i < n; ++i)
		read >> a[i].val;
	for (int i = 0; i < n; ++i)
		read >> b[i].val;

	OR(a, 1);
	OR(b, 1);
	for (int i = 0; i < n; ++i)
		c[i] = a[i] * b[i];
	OR(a, mod - 1);
	OR(b, mod - 1);
	OR(c, mod - 1);
	for (int i = 0; i < n; ++i)
		printf("%d ", c[i].val);
	puts("");

	AND(a, 1);
	AND(b, 1);
	for (int i = 0; i < n; ++i)
		c[i] = a[i] * b[i];
	AND(a, mod - 1);
	AND(b, mod - 1);
	AND(c, mod - 1);
	for (int i = 0; i < n; ++i)
		printf("%d ", c[i].val);
	puts("");

	XOR(a, 1);
	XOR(b, 1);
	for (int i = 0; i < n; ++i)
		c[i] = a[i] * b[i];
	XOR(a, getInv(2));
	XOR(b, getInv(2));
	XOR(c, getInv(2));
	for (int i = 0; i < n; ++i)
		printf("%d ", c[i].val);
	puts("");
	return 0;
}
