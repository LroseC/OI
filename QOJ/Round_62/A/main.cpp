#include <vector>
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

const int mod = 1e9 + 7;

struct Matrix
{
	int r, c;
	std::vector< std::vector<int> > val;

	Matrix(void) { r = c = 0; }
	Matrix(int _r, int _c)
	{
		r = _r, c = _c;
		val.resize(r);
		for (int i = 0; i < r; ++i)
			val[i].resize(c);
	}
	Matrix(int _r, int _c, int _v)
	{
		r = _r, c = _c;
		val.resize(r);
		for (int i = 0; i < r; ++i) {
			val[i].resize(c);
			for (int j = 0; j < c; ++j)
				val[i][j] = (i == j ? _v : 0);
		}
	}
	friend Matrix operator*(const Matrix &a, const Matrix &b)
	{
		Matrix res(a.r, b.c);
		for (int i = 0; i < a.r; ++i)
			for (int k = 0; k < a.c; ++k) {
				int tmp = a.val[i][k];
				for (int j = 0; j < b.c; ++j)
					res.val[i][j] = (res.val[i][j] + 1ll * tmp * b.val[k][j]) % mod;
			}
		return res;
	}
};

using i64 = long long;
const int N = 5010;

i64 n;
int K;
int fac[N], inv[N];

int qpow(int base, int k)
{
	int res = 1;
	while (k) {
		if (k & 1) res = 1ll * res * base % mod;
		k >>= 1;
		base = 1ll * base * base % mod;
	}
	return res;
}
int Getinv(int x) { return qpow(x, mod - 2); }
Matrix qpow(Matrix base, i64 k)
{
	Matrix res(base.r, base.c, 1);
	while (k) {
		if (k & 1) res = res * base;
		k >>= 1;
		base = base * base;
	}
	return res;
}
int C(int n, int m) { return 1ll * fac[n] * inv[m] % mod * inv[n - m] % mod; }

int main(void)
{
	read >> n >> K;
	fac[0] = 1;
	for (int i = 1; i < N; ++i) fac[i] = 1ll * fac[i - 1] * i % mod;
	inv[N - 1] = Getinv(fac[N - 1]);
	for (int i = N - 2; i >= 0; --i) inv[i] = 1ll * inv[i + 1] * (i + 1) % mod;

	Matrix base(K + 3, K + 3);
	for (int j = 0; j <= K; ++j)
		for (int i = 0; i <= j; ++i)
			base.val[i][j] = C(j, i);
	base.val[K + 1][K + 1] = 2;
	base.val[K + 1][K + 2] = 1;
	base.val[K][K + 1] = base.val[K][K + 2] = 1;

	base = qpow(base, n);

	Matrix res(1, K + 3);
	for (int i = 0; i <= K; ++i) res.val[0][i] = 1;
	res.val[0][K + 1] = res.val[0][K + 2] = 0;
	res = res * base;

	printf("%d\n", res.val[0][K + 2]);
	return 0;
}
