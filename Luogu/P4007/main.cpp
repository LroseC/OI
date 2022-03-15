#include <cctype>
#include <cstdio>
#include <cstring>

using namespace std;

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
} IO;

using LL = long long;
const int mod = 998244353;

struct DIII
{
	int x, y, z;
	DIII(void) { x = y = z = 0; }
	DIII(int _x, int _y, int _z) : x(_x), y(_y), z(_z) {}
	bool operator<(const DIII &other)
	{
		if (x != other.x) return x < other.x;
		if (y != other.y) return y < other.y;
		return z < other.z;
	}
};
struct Matrix
{
	int r, c;
	int num[170][170];

	Matrix(void) { memset(num, 0, sizeof num); }
	Matrix(int _r, int _c) : r(_r), c(_c)
	{
		memset(num, 0, sizeof num);
	}
	Matrix(int _r, int _c, int _val) : r(_r), c(_c)
	{
		for (int i = 0; i < r; ++i)
			for (int j = 0; j < c; ++j)
				num[i][j] = i == j ? _val : 0;
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
} Base[70];
void print(Matrix x)
{
	for (int i = 0; i < x.r; ++i, puts(""))
		for (int j = 0; j < x.c; ++j)
			printf("%d ", x[i][j]);
}

LL n;
int T, m, Lim, cnt;
int inv[10];
int id[10][10][10];

inline int Getinv(int base)
{
	int k = mod - 2, res = 1;
	while (k) {
		if (k & 1) res = 1ll * res * base % mod;
		k >>= 1;
		base = 1ll * base * base % mod;
	}
	return res;
}

int init(void)
{
	for (int i = 0; i <= 9; ++i)
		inv[i] = Getinv(i);

	for (int i = 0; i <= Lim; ++i)
		for (int j = 0; j <= (m >= 2 ? Lim - i : 0); ++j)
			for (int k = 0; k <= (m == 3 ? Lim - i - j : 0); ++k)
				if (i + j + k <= Lim)
					id[i][j][k] = cnt++;
	cnt++;
	Base[0] = Matrix(cnt, cnt);
	for (int i = 0; i <= Lim; ++i)
		for (int j = 0; j <= (m >= 2 ? Lim - i : 0); ++j)
			for (int k = 0; k <= (m == 3 ? Lim - i - j : 0); ++k) {
				int now = id[i][j][k];
				int val = inv[i + j + k + 1], add = i + j + k < Lim;
				if (m == 1) {// f[i][j][k] => f[i - 1][j][k];
					if (i) Base[0][now][id[i - 1][j][k]] = 1ll * i * val % mod;
				}
				if (m == 2) {
					if (i) Base[0][now][id[i - 1][j][k]] = 1ll * i * val % mod;
					if (j) Base[0][now][id[i + 1][j - 1 + add][k]] = 1ll * j * val % mod;
				}
				if (m == 3) {
					if (i) Base[0][now][id[i - 1][j][k]] = 1ll * i * val % mod;
					if (j) Base[0][now][id[i + 1][j - 1][k + add]] = 1ll * j * val % mod;
					if (k) Base[0][now][id[i][j + 1][k - 1 + add]] = 1ll * k * val % mod;
				}
				//attack the boss
				Base[0][now][cnt - 1] = Base[0][now][now] = val;
			}
	Base[0][cnt - 1][cnt - 1] = 1;
	for (int i = 1; i <= 63; ++i)
		Base[i] = Base[i - 1] * Base[i - 1];
	return 0;
}

int calc(LL x)
{
	Matrix res(1, cnt);
	res[0][id[m == 1][m == 2][m == 3]] = 1;
	for (int i = 0; i <= 60; ++i)
		if (x >> i & 1)
			res = res * Base[i];
	return res[0][cnt - 1];
}

int main(void)
{
	IO >> T >> m >> Lim;
	init();
	while (T--) {
		IO >> n;
		printf("%d\n", calc(n));
	}
	return 0;
}
