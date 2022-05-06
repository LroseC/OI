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
		while (isdigit(ch)) { res = res * 10 + (ch - '0') * f; ch = getchar(); }
		return *this;
	}
} read;

using i64 = long long;
const int mod = 1e9 + 7;
inline int getId(int x, int y) { return x * 5 + y; }
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
	void operator+=(const ModInt &other)
	{ val = Mod(val + other.val); }
};

struct Matrix
{
	int r, c;
	std::vector< std::vector<ModInt> > val;

	std::vector<ModInt>& operator[](int x)
	{ return val[x]; }
	const std::vector<ModInt>& operator[](int x) const
	{ return val[x]; }
	Matrix(void) {}
	Matrix(int _r, int _c)
	{
		r = _r, c = _c;
		val.resize(r);
		for (int i = 0; i < r; ++i) {
			val[i].resize(c);
			for (int j = 0; j < c; ++j)
				val[i][j] = 0;
		}
	}
	Matrix(int _r, int _c, int _v)
	{
		r = _r, c = _c;
		val.resize(r);
		for (int i = 0; i < r; ++i) {
			val[i].resize(c);
			for (int j = 0; j < c; ++j)
				val[i][j] = i == j ? _v : 0;
		}
	}
};
Matrix operator*(const Matrix &a, const Matrix &b)
{
	Matrix res(a.r, b.c);
	for (int i = 0; i < a.r; ++i)
		for (int k = 0; k < a.c; ++k) {
			auto t = a[i][k];
			if (!t.val) continue;
			for (int j = 0; j < b.c; ++j)
				res[i][j] = res[i][j] + t * b[k][j];
		}
	return res;
}

Matrix base[100];

Matrix calc(int k)
{
	Matrix res(1, 20);
	res[0][getId(3, 0)] = 1;
	for (int i = 0; k; ++i, k >>= 1) {
		if (!base[i].r)
			base[i] = base[i - 1] * base[i - 1];
		if (k & 1) res = res * base[i];
	}
	return res;
}

int main(void)
{
	int T; read >> T;
	Matrix tmp(20, 20);
	for (int j = 0; j < 5; ++j) {
		int tj = j;
		if (j == 1 || j == 2) tj = 3;
		tmp[getId(0, j)][getId(3, tj)] += 1;
		tmp[getId(1, j)][getId(2, tj)] += 1;
		tmp[getId(2, j)][getId(1, tj)] += 1;
		tmp[getId(3, j)][getId(3, tj)] += 1;
		tmp[getId(3, j)][getId(0, tj)] += 1;
	}
	tmp[getId(1, 0)][getId(3, 2)] += 1;
	tmp[getId(1, 3)][getId(3, 4)] += 1;
	tmp[getId(2, 0)][getId(3, 1)] += 1;
	tmp[getId(2, 3)][getId(3, 4)] += 1;
	tmp[getId(3, 0)][getId(1, 2)] += 1;
	tmp[getId(3, 0)][getId(2, 1)] += 1;
	tmp[getId(3, 1)][getId(1, 4)] += 1;
	tmp[getId(3, 2)][getId(2, 4)] += 1;
	tmp[getId(3, 3)][getId(1, 4)] += 1;
	tmp[getId(3, 3)][getId(2, 4)] += 1;
	base[0] = tmp;
	while (T--) {
		int n; read >> n;
		auto m = calc(n);
		printf("%d\n", m[0][getId(3, 4)].val);
	}
	return 0;
}
