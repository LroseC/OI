#include <queue>
#include <cctype>
#include <cstdio>
#include <cstring>

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
const int mod = 1e9 + 7, S =  110, N = 60;
inline int Mod(int x) { return x >= mod ? x - mod : x; }

struct ModInt
{
	int val;

	ModInt(void) {}
	ModInt(int x) { val = x; }
	ModInt operator+(const ModInt &other) const
	{ return val + other.val; }
	ModInt operator-(const ModInt &other) const
	{ return val + mod - other.val; }
	ModInt operator*(const ModInt &other) const
	{ return 1ll * val * other.val % mod; }
};
struct Matrix
{
	int r, c;
	std::vector< std::vector<ModInt> > val;

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
	Matrix(int _r, int _c, int v)
	{
		r = _r, c = _c;
		val.resize(r);
		for (int i = 0; i < r; ++i) {
			val[i].resize(c);
			for (int j = 0; j < c; ++j)
				val[i][j] = (i == j ? v : 0);
		}
	}
	std::vector<ModInt>& operator[](int x)
	{ return val[x]; }
	const std::vector<ModInt>& operator[](int x) const
	{ return val[x]; }
	Matrix operator*(const Matrix &other) const
	{
		Matrix res(r, other.c);
		for (int i = 0; i < r; ++i)
			for (int k = 0; k < c; ++k) {
				ModInt t = val[i][k];
				if (!t.val) continue;
				for (int j = 0; j < other.c; ++j)
					res[i][j] = res[i][j] + t * other[k][j];
			}
		return res;
	}
};

inline Matrix qpow(Matrix base, int k)
{
	Matrix res(base.r, base.c, 1);
	while (k) {
		if (k & 1) res = res * base;
		k >>= 1;
		base = base * base;
	}
	return res;
}

int n, m, L, idx;
int len[N];
bool end[S], flag[S][N];
int ch[S][26], fail[S], to[S][N];
char basis[N][S], tmp[S];
ModInt f[S][S];

void insert(char str[])
{
	int u = 0;
	for (int i = 0; str[i]; ++i) {
		int t = str[i] - 'a';
		if (!ch[u][t])
			ch[u][t] = ++idx;
		u = ch[u][t];
	}
	end[u] = 1;
}
void build(void)
{
	std::queue<int> q;
	for (int i = 0; i < 26; ++i)
		if (ch[0][i]) q.emplace(ch[0][i]);
	while (q.size()) {
		int u = q.front(); q.pop();
		for (int i = 0; i < 26; ++i) {
			if (!ch[u][i])
				ch[u][i] = ch[fail[u]][i];
			else {
				fail[ch[u][i]] = ch[fail[u]][i];
				q.emplace(ch[u][i]);
			}
		}
	}
}
void init(void)
{
	for (int u = 0; u <= idx; ++u) {
		if (end[u]) continue;
		for (int i = 1; i <= n; ++i) {
			flag[u][i] = 1;
			int t = u;
			for (int j = 1; basis[i][j]; ++j) {
				t = ch[t][basis[i][j] - 'a'];
				if (end[t]) flag[u][i] = 0;
			}
			to[u][i] = t;
		}
	}
}
Matrix initMatrix(void)
{
	Matrix base(idx + 1, idx + 1);
	for (int u = 0; u <= idx; ++u) {
		if (end[u]) continue;
		for (int i = 1; i <= n; ++i) {
			int t = ch[u][basis[i][1] - 'a'];
			if (!end[t]) base[u][t] = base[u][t] + 1;
		}
	}
	return base;
}
void Matrixmain(void)
{
	Matrix base = initMatrix();
	Matrix res(1, idx + 1);
	res[0][0] = 1;
	res = res * qpow(base, L);
	ModInt ans = 0;
	for (int i = 0; i <= idx; ++i)
		ans = ans + res[0][i];
	printf("%d\n", ans.val);
}

int main(void)
{
	read >> n >> m >> L;
	bool checkMatrix = 1;
	for (int i = 1; i <= n; ++i) {
		scanf("%s", basis[i] + 1);
		len[i] = std::strlen(basis[i] + 1);
		if (len[i] != 1) checkMatrix = 0;
	}
	for (int i = 1; i <= m; ++i) {
		scanf("%s", tmp + 1);
		insert(tmp + 1);
	}
	build();
	if (checkMatrix) {
		Matrixmain();
		return 0;
	}
	init();
	f[0][0] = 1;
	for (int l = 0; l <= L; ++l)
		for (int u = 0; u <= idx; ++u)
			if (f[l][u].val)
				for (int i = 1; i <= n; ++i)
					if (flag[u][i])
						f[l + len[i]][to[u][i]] = f[l + len[i]][to[u][i]] + f[l][u];
	ModInt res = 0;
	for (int u = 0; u <= idx; ++u)
		res = res + f[L][u];
	printf("%d\n", res.val);
	return 0;
}
