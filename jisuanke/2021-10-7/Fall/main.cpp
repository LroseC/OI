#include <cctype>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long LL;
const int N = 1e5 + 10, M = 6;

inline LL read(void)
{
	LL res = 0, f = 1; char ch = getchar();
	while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
	while (isdigit(ch)) { res = res * 10 + ch - '0'; ch = getchar(); }
	return res * f;
}

inline LL sq(LL x) { return x * x; }

struct Matrix
{
	int r, c;
	LL val[M * M][M * M];
	Matrix(int _r = 0, int _c = 0)
	{
		r = _r, c = _c;
		memset(val, 0, sizeof val);
	}
	Matrix(int _r, int _c, int _v)
	{
		r = _r, c = _c;
		for (int i = 0; i < r; ++i)
			for (int j = 0; j < c; ++j)
				val[i][j] = (i == j ? _v : 0);
	}
	Matrix operator*(const Matrix &b) const
	{
		Matrix res(r, b.c);
		for (int i = 0; i < r; ++i)
			for (int j = 0; j < b.c; ++j)
				for (int k = 0; k < c; ++k)
					res.val[i][j] = max(res.val[i][j], val[i][k] + b.val[k][j]);
		return res;
	}
};

int n, m; LL k;
int G[N][M];
int f[N][M][M];

inline int getid(int x, int y) { return (x - 1) * m + (y - 1); }
inline Matrix qpow(Matrix base, LL k)
{
	Matrix res(base.r, base.c);
	while (k) {
		if (k & 1) res = res * base;
		k >>= 1;
		base = base * base;
	}
	return res;
}

int main(void)
{
	freopen("Falling.in", "r", stdin);
	freopen("Falling.out", "w", stdout);
	n = read(), m = read(); k = read();
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			G[i][j] = read();
	
	Matrix base(sq(m), sq(m));
	for (int a = 1; a <= m; ++a)
		for (int b = 1; b <= m; ++b) {
			if (a == b) continue;
			f[1][a][b] = (G[1][a] == 1) + (G[1][b] == 2);
			for (int i = 2; i <= n; ++i)
				for (int x = 1; x <= m; ++x)
					for (int y = 1; y <= m; ++y) {
						if (x == y) continue;
						f[i][x][y] = 0;
						for (int dx = -1; dx <= 1; ++dx)
							for (int dy = -1; dy <= 1; ++dy) {
								int p = x + dx, q = y + dy;
								if (p == q) continue;
								if (p < 1 || p > m) continue;
								if (q < 1 || q > m) continue;
								f[i][x][y] = max(f[i][x][y], f[i - 1][p][q]);
							}
						f[i][x][y] += (G[i][x] == 1) + (G[i][y] == 2);
					}
			int t = getid(a, b);
			for (int x = 1; x <= m; ++x)
				for (int y = 1; y <= m; ++y)
					base.val[t][getid(x, y)] = f[n][x][y];
			f[1][a][b] = 0;
		}
	Matrix ans = qpow(base, k);
	LL res = 0;
	for (int i = 0; i < ans.r; ++i)
		for (int j = 0; j < ans.c; ++j)
			res = max(res, ans.val[i][j]);
	printf("%lld\n", res);
	return 0;
}