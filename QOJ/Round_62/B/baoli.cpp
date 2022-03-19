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

int n, m, C;
int A[N], B[N];
int f[N][30];

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
	f[0][0] = 1;
	for (int i = 1; i <= n; ++i)
		for (int c = 0; c < C; ++c) {
			f[i][c] = f[i - 1][c] * B[i] + (c - 1 >= 0 ? f[i - 1][c - 1] * A[i] : 0);
			f[i][c] %= mod;
		}
	read >> m;
	for (int k = 1; k <= m; ++k) {
		int pos, a, b;
		read >> pos >> a >> b;
		a %= mod, b %= mod;
		A[pos] = a;
		B[pos] = b;
		for (int i = 1; i <= n; ++i)
			for (int c = 0; c < C; ++c) {
				f[i][c] = f[i - 1][c] * B[i] + (c - 1 >= 0 ? f[i - 1][c - 1] * A[i] : 0);
				f[i][c] %= mod;
			}
		int ans = 1;
		for (int i = 1; i <= n; ++i)
			ans = ans * (A[i] + B[i]) % mod;
		for (int c = 0; c < C; ++c)
			ans = Mod(ans - f[n][c] + mod);
		printf("%d\n", ans);
	}
	return 0;
}
