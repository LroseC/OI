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
const int N = 510, mod = 998244353;
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
};

int n;
int p[N];
ModInt f[N][N][2];

int main(void)
{
	int n;
	read >> n;
	for (int i = 1; i <= n; ++i) {
		read >> p[i];
	}
	for (int i = 1; i <= n; ++i) {
		f[i][i][0] = 1;
	}
	for (int len = 1; len <= n; ++len) {
		for (int l = 1, r = l + len - 1; r <= n; ++l, ++r) {
			if (l != r)
				f[l][r][0] = f[l + 1][r][1];
			for (int mid = l; mid < r; ++mid) {
				if (p[l] < p[mid + 1]) {
					f[l][r][1] = f[l][r][1] + f[l][mid][0] * f[mid + 1][r][1];
				}
			}
			f[l][r][1] = f[l][r][1] + f[l][r][0];
		}
	}
	printf("%d\n", f[1][n][0].val);
	return 0;
}
