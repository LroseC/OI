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

using i64 = long long;
const int N = 1010, M = 2e5 + 10;

struct Edge
{
	int u, v;
};

int n, m;
Edge e[M];
int f[M];
int g[N][N];

int main(void)
{
	read >> n >> m;
	for (int i = 1; i <= m; ++i) {
		int u, v;
		read >> u >> v;
		g[u][v] = i;
	}
	for (int k = n; k >= 1; --k) {
		for (int i = n; i >= k; --i)
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= n; ++j) {
				if (f[i][k] && f[k][j])
					f[i][j] = std::max(f[i][j], std::min(f[i][k], f[k][j]));
			}
	}
	return 0;
}
