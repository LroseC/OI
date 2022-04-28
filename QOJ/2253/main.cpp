#include <cmath>
#include <vector>
#include <iostream>

using i64 = long long;

struct Matrix
{
	int r, c;
	long double val[256][256];

	long double* operator[](int x)
	{ return val[x]; }
	const long double* operator[](int x) const
	{ return val[x]; }

	Matrix(void) { r = c = 0; }
	Matrix(int _r, int _c)
	{
		r = _r, c = _c;
		for (int i = 0; i < r; ++i)
			for (int j = 0; j < c; ++j)
				val[i][j] = 0;
	}
	Matrix(int _r, int _c, int _v)
	{
		r = _r, c = _c;
		for (int i = 0; i < r; ++i)
			for (int j = 0; j < c; ++j)
				val[i][j] = (i == j) ? _v : 0;
	}
};
Matrix operator*(const Matrix &a, const Matrix &b)
{
	Matrix res(a.r, b.c);
	for (int i = 0; i < a.r; ++i)
		for (int k = 0; k < a.c; ++k) {
			long double tmp = a[i][k];
			if (fabs(tmp) < 5e-10) continue;
			for (int j = 0; j < b.c; ++j)
				res[i][j] += tmp * b[k][j];
		}
	return res;
}

Matrix qpow(Matrix base, int k)
{
	Matrix res(base.r, base.c, 1);
	while (k) {
		if (k & 1) res = res * base;
		k >>= 1;
		base = base * base;
	}
	return res;
}

int n, m, d;
long double p[16][16];
int type[16];

inline int getId(int x, int y) { return x * n + y; }

int main(void)
{
	std::cin >> n >> m;
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			std::cin >> p[i][j];
	std::cin >> d;
	for (int i = 0; i < n; ++i)
		std::cin >> type[i];
	Matrix base(n * n, n * n);
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			if (type[i] == type[j])
				for (int u = 0; u < n; ++u)
					for (int v = 0; v < n; ++v)
						if (type[u] == type[v])
							base[getId(i, j)][getId(u, v)] = p[i][u] * p[j][v];
	Matrix res(1, n);
	res[0][0] = 1;
	res = res * qpow(base, m - 1);
	long double ans = 0;
	for (int i = 0; i < n * n; ++i)
		ans += res[0][i];
	printf("%.12Lf\n", ans);
	return 0;
}
