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
} IO;

const int N = 3010;

int n, m, cnt;
bool G[N][N];
bool vis[N];

int main(void)
{
	IO >> n >> m;
	for (int i = 1; i <= m; ++i) {
		int u, v; IO >> u >> v;
		G[u][v] = G[v][u] = 1;
	}
	for (int i = 1; i <= n; ++i) {
		if (vis[i]) continue;
		for (int j = i + 1; j <= n; ++j) {
			if (vis[j]) continue;
			if (!G[i][j] && cnt != n / 3) {
				++cnt;
				vis[i] = vis[j] = 1;
				break;
			}
		}
	}
	int tcnt = 0;
	for (int i = 1; i <= n; ++i)
		if (!vis[i] && tcnt != n / 3) {
			++tcnt;
			printf("%d ", i);
		}
	puts("");
	return 0;
}
