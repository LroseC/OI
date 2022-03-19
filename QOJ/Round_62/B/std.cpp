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

const int N = 1e5 + 10, mod = 10007;
inline int Mod(int x) { return x >= mod ? x - mod : x; }

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

int n, m, C;
int A[N], B[N];
int f[N][30];
std::vector<int> tr[N << 2];

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

std::vector<int> merge(std::vector<int> a, std::vector<int> b)
{
	std::vector<int> res(C);
	for (int i = 0; i < C; ++i)
		for (int j = 0; j + i < C; ++j)
			res[i + j] = (res[i + j] + 1ll * a[i] * b[j]) % mod;
	return res;
}
void build(int u = 1, int l = 1, int r = n)
{
	tr[u].resize(C);
	if (l == r) {
		tr[u][0] = B[l];
		tr[u][1] = A[l];
		return;
	}
	int mid = l + r >> 1;
	build(u << 1, l, mid);
	build(u << 1 | 1, mid + 1, r);
	tr[u] = merge(tr[u << 1], tr[u << 1 | 1]);
}
void change(int pos, int u = 1, int l = 1, int r = n)
{
	if (l == r) {
		tr[u][0] = B[l];
		tr[u][1] = A[l];
		return;
	}
	int mid = l + r >> 1;
	if (pos <= mid)
		change(pos, u << 1, l, mid);
	else
		change(pos, u << 1 | 1, mid + 1, r);
	tr[u] = merge(tr[u << 1], tr[u << 1 | 1]);
}

int main(void)
{
	read >> n >> C;
	for (int i = 1; i <= n; ++i) {
		read >> A[i];
		A[i] %= mod;
	}
	for (int i = 1; i <= n; ++i) {
		read >> B[i];
		B[i] %= mod;
	}
	build();
	int ans = 1;
	for (int i = 1; i <= n; ++i)
		ans = 1ll * ans * (A[i] + B[i]) % mod;
	read >> m;
	for (int k = 1; k <= m; ++k) {
		int pos, a, b;
		read >> pos >> a >> b;
		a %= mod, b %= mod;
		ans = 1ll * ans * Getinv(A[pos] + B[pos]) % mod * (a + b) % mod;
		A[pos] = a;
		B[pos] = b;
		change(pos);
		int tans = ans;
		for (int c = 0; c < C; ++c)
			tans = Mod(tans - tr[1][c] + mod);
		printf("%d\n", tans);
	}
	return 0;
}
