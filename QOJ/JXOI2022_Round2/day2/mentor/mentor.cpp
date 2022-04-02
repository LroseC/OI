#include <vector>
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
		while (isdigit(ch)) { res = res * 10 + ch - '0'; ch = getchar(); }
		res = res * f; return *this;
	}
} read;

const int N = 410;

int n, m, T, C;
bool vis[N];
int lim[N], s[N], ans[N], ans2[N];
std::vector<int> G[N][N], match[N];

bool dfs(int id, int u, int &res)
{
	vis[u] = 1;
	for (int v : G[u][id]) {
		if (match[v].size() < lim[v - n]) {
			match[v].emplace_back(u);
			vis[u] = 0;
			return 1;
		}
		else {
			for (int i = 0; i < match[v].size(); ++i) {
				int vv = match[v][i];
				if (vv == u || vis[vv]) continue;
				res = std::max(res, vv);
				if (dfs(ans[vv], vv, res)) {
					match[v][i] = u;
					vis[u] = 0;
					return 1;
				}
			}
		}
	}
	vis[u] = 0;
	return 0;
}

void work(void)
{
	read >> n >> m;
	for (int i = 1; i <= m; ++i)
		read >> lim[i];
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j) {
			int aij; read >> aij;
			if (aij == 0) continue;
			G[i][aij].emplace_back(j + n);
		}
	for (int i = 1; i <= n; ++i)
		read >> s[i];
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j) {
			if (dfs(j, i, j <= s[i] ? ans2[i] : ans2[0])) {
				ans[i] = j;
				if (ans[i] <= s[i]) ans2[i] = i;
				break;
			}
		}
	for (int i = 1; i <= n; ++i)
		printf("%d ", ans[i] == 0 ? m + 1 : ans[i]);
	puts("");
	for (int i = 1; i <= n; ++i)
		printf("%d ", i - ans2[i]);
	puts("");
}
void clear(void)
{
	std::memset(ans, 0, sizeof ans);
	std::memset(ans2, 0, sizeof ans2);
	for (int i = 0; i < N; ++i)
		match[i].clear();
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < N; ++j)
			G[i][j].clear();
}
int main(void)
{
//	freopen("menter.in", "r", stdin);
//	freopen("menter.out", "w", stdout);
	read >> T >> C;
	while (T--) {
		work();
		clear();
	}
	return 0;
}
