#include <vector>
#include <cctype>
#include <cstdio>

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

const int N = 3e5 + 10;
const int mod = 1e9 + 7;

int n, m;
vector<int> G[N];

namespace pts30
{
	int f[N], w[N];
	bool check(void) { return 1ll * n * m <= 1e8; }
	void dfs(int u, int fa, int dep, int lim)
	{
		w[u] += f[dep];
		w[u] = w[u] >= mod ? w[u] - mod : w[u];
		if (dep == lim) return;
		for (int v : G[u])
			if (v != fa) dfs(v, u, dep + 1, lim);
	}
	int main(void)
	{
		for (int i = 1; i <= m; ++i) {
			int opt; read >> opt;
			if (opt == 1) {
				int u, d;
				read >> u >> f[0] >> f[1] >> d;
				for (int i = 2; i <= d; ++i) {
					f[i] = f[i - 2] + f[i - 1];
					f[i] = f[i] >= mod ? f[i] - mod : f[i];
				}
				dfs(u, u, 0, d);
			}
			else {
				int x; read >> x;
				printf("%d\n", w[x]);
			}
		}
		return 0;
	}
}

int main(void)
{
	read >> n >> m;
	for (int i = 1; i < n; ++i) {
		int u, v; read >> u >> v;
		G[u].emplace_back(v);
		G[v].emplace_back(u);
	}
	pts30::main();
	return 0;
}
