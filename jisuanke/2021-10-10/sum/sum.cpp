#include <cctype>
#include <cstdio>
#include <cstring>

using namespace std;

typedef unsigned long long ULL;
const int mod = 20050103;

inline ULL read(void)
{
	ULL res = 0, f = 1; char ch = getchar();
	while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
	while (isdigit(ch)) { res = res * 10 + ch - '0'; ch = getchar(); }
	return res * f;
}
template<typename T>
inline void write(T x, char end = '\n')
{
	static char buf[50]; int p = -1;
	if (x == 0) putchar('0');
	if (x < 0) { putchar('-'); x = -x; }
	while (x) { buf[++p] = x % 10; x /= 10; }
	while (~p) { putchar(buf[p] + '0'); --p; } putchar(end);
}

struct Matrix
{
	int r, c;
	int val[120][120];

	Matrix(int _r = 0, int _c = 0)
	{
		r = _r; c = _c;
		memset(val, 0, sizeof val);
	}
	Matrix(int _r, int _c, int _v)
	{
		r = _r; c = _c;
		for (int i = 0; i < r; ++i)
			for (int j = 0; j < c; ++j)
				val[i][j] = i == j ? _v : 0;
	}

	Matrix operator*(const Matrix &b) const
	{
		Matrix res(b.r, c);
		for (int i = 0; i < b.r; ++i)
			for (int k = 0; k < r; ++k) {
				int t = b.val[i][k];
				for (int j = 0; j < c; ++j)
					res.val[i][j] = (res.val[i][j] + 1ll * val[k][j] * t % mod) % mod;
			}
		return res;
	}
} ori, base;

int K, C;
int a[1010], b[1010];

inline void Print(Matrix x)
{
	for (int i = 0; i < x.r; ++i, puts(""))
		for (int j = 0; j < x.c; ++j)
			printf("%3d ", x.val[i][j]);
}
inline Matrix qpow(Matrix base, ULL k)
{
	Matrix res(base.r, base.c, 1);
	while (k) {
		if (k & 1) res = res * base;
		k >>= 1;
		base = base * base;
	}
	return res;
}

inline int query(ULL x)
{
	if (x <= K) {
		int res = 0;
		for (int i = 1; i <= x; ++i) res = (res + a[i]) % mod;
		return res;
	}
	if (K == 0) {
		x %= mod;
		return 1ll * C * x % mod;
	}
	Matrix res = ori * qpow(base, x - K);
	return res.val[K + 1][0];
}
inline void BuildMatrix(void)
{
	ori.r = K + 2, ori.c = 1;
	ori.val[0][0] = 1;
	for (int i = 1; i <= K; ++i) {
		ori.val[i][0] = a[i] % mod;
		ori.val[K + 1][0] = (ori.val[K + 1][0] + a[i]) % mod;
	}
	base.r = base.c = K + 2;
	base.val[0][0] = 1;
	for (int i = 1; i < K; ++i)
		base.val[i][i + 1] = 1;
	base.val[K][0] = C;
	for (int i = K, j = 1; i >= 1; --i, ++j)
		base.val[K][i] = b[j];
	base.val[K + 1][0] = C;
	for (int i = K, j = 1; i >= 1; --i, ++j)
		base.val[K + 1][i] = b[j];
	base.val[K + 1][K + 1] = 1;
}
int main(void)
{
	freopen("sum.in", "r", stdin);
	freopen("sum.out", "w", stdout);
	K = read(), C = read() % mod;
	for (int i = 1; i <= K; ++i) a[i] = read() % mod;
	for (int i = 1; i <= K; ++i) b[i] = read() % mod;
	BuildMatrix();
	ULL l = read(), r = read();
	write(((query(r) - query(l - 1)) % mod + mod) % mod);
	return 0;
}