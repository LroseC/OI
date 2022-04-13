#include <vector>
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
const int N = 1010, M = 2e5 + 10;

struct Edge
{
	int u, v;
};

int n, m;
Edge e[M];
int f[N][N];
int res[M];

int main(void)
{
	read >> n >> m;
	for (int i = 1; i <= m; ++i) {
		int u, v;
		read >> u >> v;
		f[u][v] = i;
	}
	for (int k = n; k >= 1; --k) {
		for (int i = n; i > k; --i)
			if (f[i][k] && f[k][i]) ++res[std::min(f[i][k], f[k][i])];
		for (int i = 1; i <= n; ++i) {
			if (!f[i][k]) continue;
			int t = i > k ? k - 1 : n;
			for (int j = 1; j <= t; ++j) {
				if (f[k][j])
					f[i][j] = std::max(f[i][j], std::min(f[i][k], f[k][j]));
			}
		}
	}
	res[m + 1] = n;
	for (int i = m; i >= 1; --i)
		res[i] += res[i + 1];
	for (int i = 1; i <= m + 1; ++i)
		printf("%d ", res[i]);
	puts("");
	return 0;
}
