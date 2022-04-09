#include <cctype>
#include <cstdio>
#include <algorithm>

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

using i64 = long long;
const int N = 310, mod = 1e9 + 7;
inline int Mod(int x) { return x >= mod ? x - mod : x; }

int n, m, TYPE;
int a[N][N];

void add(int u, int v, int w)
{
	a[v][v] = Mod(a[v][v] + w);
	a[u][v] = Mod(a[u][v] + mod - w);
}

int main(void)
{
	read >> n >> m >> TYPE;
	for (int i = 1; i <= m; ++i) {
		int u, v, w;
		read >> u >> v >> w;
		if (TYPE == 0) {
			add(u, v, w);
			add(v, u, w);
		}
		else
			add(u, v, w);
	}
	int res = 1;
	for (int i = 2; i <= n; ++i) {
		for (int j = i + 1; j <= n; ++j) {
			while (a[j][i]) {
				res *= -1;
				int tmp = a[i][i] / a[j][i];
				for (int k = 1; k <= n; ++k) {
					std::swap(a[i][k], a[j][k]);
					a[j][k] = Mod(a[j][k] - 1ll * tmp * a[i][k] % mod + mod);
				}
			}
		}
	}
	for (int i = 2; i <= n; ++i)
		res = 1ll * res * a[i][i] % mod;
	printf("%d\n", Mod(res + mod));
	return 0;
}
