#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

using LL = long long;
const int mod = 1e9 + 7;

struct Matrix
{
	int r, c;
	int num[60][60];

	Matrix(void) { memset(num, 0, sizeof num); }
	Matrix(int _r, int _c) : r(_r), c(_c)
	{ memset(num, 0, sizeof num); }
	Matrix(int _r, int _c, int _v)
	{
		r = _r, c = _c;
		for (int i = 0; i < r; ++i)
			for (int j = 0; j < c; ++j)
				num[i][j] = i == j ? _v : 0;
	}
	int* operator[](int x) { return num[x]; }
	friend Matrix operator*(Matrix &a, Matrix &b)
	{
		Matrix res(a.r, b.c);
		for (int i = 0; i < a.r; ++i)
			for (int k = 0; k < a.c; ++k)
				for (int j = 0; j < b.c; ++j)
					res[i][j] = (res[i][j] + 1ll * a[i][k] * b[k][j]) % mod;
		return res;
	}
};

LL n;
int m, k;

Matrix qpow(Matrix base, LL k)
{
	Matrix res(base.r, base.c, 1);
	while (k) {
		if (k & 1) res = res * base;
		k >>= 1;
		base = base * base;
	}
	return res;
}

int getid(char x)
{
	if (islower(x))
		return x - 'a';
	return x - 'A' + 26;
}

int main(void)
{
	cin >> n >> m >> k;
	Matrix base(m, m);
	for (int i = 0; i < m; ++i)
		for (int j = 0; j < m; ++j)
			base[i][j] = 1;
	for (int i = 0; i < k; ++i) {
		static char str[10];
		scanf("%s", str);
		base[getid(str[0])][getid(str[1])] = 0;
	}
	Matrix res(1, m);
	for (int i = 0; i < m; ++i)
		res[0][i] = 1;
	base = qpow(base, n - 1);
	res = res * base;
	int ans = 0;
	for (int i = 0; i < m; ++i)
		ans = (ans + res[0][i]) % mod;
	printf("%d\n", ans);
	return 0;
}
