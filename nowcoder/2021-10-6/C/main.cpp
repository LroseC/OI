#include <vector>
#include <cctype>
#include <cstdio>

using namespace std;

const int N = 1e5 + 10;

inline int read(void)
{
	int res = 0, f = 1; char ch = getchar();
	while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
	while (isdigit(ch)) { res = res * 10 + ch - '0'; ch = getchar(); }
	return res * f;
}
template<typename T>
inline void write(T x, char end = '\n')
{
	static char buf[50]; int p = -1;
	if (x == 0) putchar('0');
	if (x < 0) { putchar('-'); x = -x; }
	while (x) { buf[++p] = x % 10; x /= 10; }
	while (~p) { putchar(buf[p] + '0'); --p; } putchar(end);
}

int dis[N];
vector<int> G[N];

int dfs(int u, int fa, int dep, int &res)
{
	dis[u] = dep;
	if (dis[u] > dis[res]) res = u;
	for (int v : G[u]) {
		if (v == fa) continue;
		dfs(v, u, dep + 1, res);
	}
	return dis[res];
}

int main(void)
{
	int T = read();
	while (T--) {
		int n = read();
		for (int i = 1; i <= n; ++i) G[i].clear();
		for (int i = 1; i < n; ++i) {
			int u = read(), v = read();
			G[u].emplace_back(v);
			G[v].emplace_back(u);
		}
		int tmp;
		dfs(1, -1, 0, tmp);
		write(dfs(tmp, -1, 0, tmp) + 1);
	}
	return 0;
}
