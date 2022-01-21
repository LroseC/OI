#include <vector>
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

const int mod = 1e9 + 7;
inline int lowbit(int x) { return x & -x; }

struct Matrix
{
	int r, c;
	vector<vector<int>> num;
	Matrix(int _r, int _c) : r(_r), c(_c)
	{
		num.resize(r);
		for (int i = 0; i < r; ++i)
			num[i].resize(c);
	}
	Matrix(int _r, int _c, int _v) : r(_r), c(_c)
	{
		num.resize(r);
		for (int i = 0; i < r; ++i) {
			num[i].resize(c);
			if (i < c) num[i][i] = _v;
		}
	}

	friend void print(Matrix &x)
	{
		for (int i = 0; i < x.r; ++i, puts(""))
			for (int j = 0; j < x.c; ++j)
				printf("%d ", x[i][j]);
	}
	vector<int>& operator[](int x) { return num[x]; }
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

const int N = 60;

Matrix qpow(Matrix base, int k);
int get(int pos, int state, int array);

int n, k, len;
char str[60];
int f[60][1 << 8];
int bitcnt[1 << 8];

int main(void)
{
	IO >> n >> k;
	scanf("%s", str + 1);
	len = strlen(str + 1);
	for (int i = 1; i <= len; ++i)
		str[i] -= '0';
	for (int i = 1; i < 1 << 8; ++i)
		bitcnt[i] = bitcnt[i >> 1] + (i & 1);

	Matrix trans(1 << n, 1 << n);
	for (int st = 0; st < 1 << n; ++st) {
		memset(f, 0, sizeof f);
		f[0][st] = 1;
		for (int pos = 1; pos <= len; ++pos) {
			for (int state = 0; state < 1 << n; ++state) {
				if (!f[pos - 1][state]) continue;
				for (int array = 0; array < 1 << n; ++array) {
					int tmp = get(pos, state, array);
					if (tmp == -1) continue;
					f[pos][tmp] = (f[pos][tmp] + f[pos - 1][state]) % mod;
				}
			}
		}
		for (int i = 0; i < 1 << n; ++i)
			trans[st][i] = f[len][i];
	}
	trans = qpow(trans, k);
	Matrix res(1, 1 << n);
	res[0][(1 << n) - 1] = 1;
	res = res * trans;
	printf("%d\n", res[0][0]);
	return 0;
}

int get(int pos, int state, int array)
{
	if (bitcnt[array] & 1) return -1;
	int tostate = 0;
	array = (array << 1) | str[pos];
	for (int i = 0; i < n; ++i) {
		int ai = array >> i & 1, ai1 = array >> (i + 1) & 1;
		if (state >> i & 1) {
			if (ai < ai1) return -1;
			if (ai == ai1)
				tostate |= 1 << i;
		}
	}
	return tostate;
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
