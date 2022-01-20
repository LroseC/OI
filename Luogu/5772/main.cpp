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

int n, k;
char str[N];

void printin2(int x)
{
	for (int i = 0; i < n; ++i)
		printf("%d", x >> i & 1);
}
void printin2p(int x)
{
	for (int i = 0; i <= n; ++i)
		printf("%d", x >> i & 1);
}
Matrix qpow(Matrix base, int k)
{
	Matrix res(base.r, base.c, 1);
	while (k) {
		if (k >> 1 & 1) res = res * base;
		k >>= 1;
		base = base * base;
	}
	return res;
}
int Getcnt(int x)
{
	int res = 0;
	while (x) {
		++res;
		x -= lowbit(x);
	}
	return res;
}

int get(int pos, int state, int array)
{
	/*
	   get 函数返回处理到第 pos 位, 当前状态为 state, 如果数组为 array 时转移到的状态
	   如果无法转移 (不合法) 返回 -1
	   get 函数的复杂度为 O(n)
   */
	if (Getcnt(array) & 1) return -1;
	int tostate = 0;
	array = array << 1 | (str[pos] - '0');
	for (int i = 0; i < n; ++i) {
		int ai = array >> i & 1, ai1 = array >> i + 1 & 1;
		if ((state >> i & 1) && ai < ai1)
			return -1;
		tostate |= ((state >> i & 1) && ai == ai1) << i;
	}
	return tostate;
}

int main(void)
{
	IO >> n >> k;
	scanf("%s", str + 1);
	int len = strlen(str + 1);
	Matrix base(1 << n, 1 << n, 1);

	Matrix res(1, 1 << n);
	for (int i = 0; i < n; ++i)
		res[0][(1 << n) - 1 ^ (1 << i)] = 1;

	for (int pos = 1; pos <= len; ++pos) {
		Matrix tmpMa(1 << n, 1 << n);
		for (int state = 0; state < 1 << n; ++state)
			for (int array = 0; array < 1 << n; ++array) {
				int tmp = get(pos, state, array);
				if (tmp == -1) continue;

				//state -> tmp
				++tmpMa[state][tmp];
			}
		base = base * tmpMa;
		if (pos != 1) res = res * tmpMa;
	}
	base = qpow(base, k - 1);
	res = res * base;
	printf("%d\n", res[0][0]);
	return 0;
}
/*
   f[i][state] 表示考虑前 i 位, 状态为 state 时的方案数
   把 f[i] 整个数组视作维数为 2^n 的一个向量
   这时可以构造一个转移矩阵 M, 令 f[i] = f[i - 1] * M;
   然后把一个循环节的转移矩阵乘在一起, 最终的转移矩阵就是这个乘积矩阵的幂
   快速幂解决即可.
*/
