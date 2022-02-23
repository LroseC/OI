#include <vector>
#include <cctype>
#include <cstdio>
#include <algorithm>

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
} read;

const int N = 2510;

int K, n;
int S[N], P[N], fa[N];
double x[N], f[N][N];
vector<int> G[N];

int dfs(int u, int fa)
{
	int sz = 1;
	f[u][0] = 0;
	for (int i = 1; i <= n; ++i)
		f[u][i] = -1e9;
	for (int v : G[u])
		if (v != fa) {
			int tmp; sz += (tmp = dfs(v, u));
			for (int i = min(sz - 1, K); i >= 0; --i)
				for (int j = 0; j <= min(tmp, i); ++j)
					f[u][i] = max(f[u][i], f[u][i - j] + f[v][j]);
		}
	if (u != 0)
		for (int i = min(sz, K); i > 0; --i)
			f[u][i] = f[u][i - 1] + x[u];
	return sz;
}
bool check(double res)
{
	for (int i = 1; i <= n; ++i)
		x[i] = P[i] - res * S[i];
	dfs(0, 0);
	return f[0][K] >= 0;
}

int main(void)
{
	read >> K >> n;
	for (int i = 1; i <= n; ++i) {
		read >> S[i] >> P[i] >> fa[i];
		G[fa[i]].emplace_back(i);
	}
	double l = 0, r = 1e9;
	while (r - l >= 1e-5) {
		double mid = (l + r) / 2;
		if (check(mid)) l = mid;
		else r = mid;
	}
	printf("%.3lf\n", l);
	return 0;
}
