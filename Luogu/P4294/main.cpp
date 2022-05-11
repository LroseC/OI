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
		while (isdigit(ch)) { res = res * 10 + (ch - '0') * f; ch = getchar(); }
		return *this;
	}
} read;

using i64 = long long;
const int S = 1 << 10;
const int gox[] = {1, -1, 0, 0};
const int goy[] = {0, 0, 1, -1};

int n, m, K;
bool vis[110];
bool type[S][110];
int f[S][110], pre[S][110], isKey[110];
int tmpval[12][12], val[110], key[12];
std::vector<int> G[110];
char str[20][20];

void dijkstra(int id)
{
	std::memset(vis, 0, sizeof vis);
//	std::memset(vis + 1, 0, sizeof (int) * n * m);
	int *dis = f[id];
	for (int i = 1; i < n * m; ++i) {
		int u = 0;
		for (int j = 1; j <= n * m; ++j)
			if (!vis[j] && (!u || dis[j] < dis[u])) u = j;
		vis[u] = 1;
		for (int v : G[u])
			if (!vis[v] && dis[v] > dis[u] + val[v]) {
				type[id][v] = 1;
				pre[id][v] = u;
				dis[v] = dis[u] + val[v];
			}
	}
}
inline int getId(int x, int y)
{ return (x - 1) * m + y; }
inline std::pair<int, int> getXY(int id)
{
	int y = (id - 1) % m + 1;
	int x = (id - y) / m + 1;
	return std::make_pair(x, y);
}
inline int lowbit(int x) { return x & -x; }
void getPre(int s, int u)
{
	auto t = getXY(u);
	if (1 << isKey[u] == s) return;
	if (type[s][u] == 0) {
		int sp = pre[s][u];
		getPre(sp, u);
		getPre(s ^ sp, u);
	}
	else {
		auto t = getXY(u);
		if (str[t.first][t.second] != 'x')
			str[t.first][t.second] = 'o';
		getPre(s, pre[s][u]);
	}
}

int main(void)
{
	read >> n >> m;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j) {
			read >> tmpval[i][j];
			val[getId(i, j)] = tmpval[i][j];
		}
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			for (int k = 0; k < 4; ++k) {
				int x = i + gox[k];
				int y = j + goy[k];
				if (x < 1 || x > n || y < 1 || y > m) continue;
				int u = getId(i, j);
				int v = getId(x, y);
				G[u].emplace_back(v);
			}
	std::memset(f, 0x3f, sizeof f);
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			if (tmpval[i][j] == 0) {
				isKey[getId(i, j)] = K;
				key[K] = getId(i, j);
				f[1 << K][getId(i, j)] = 0;
				++K;
			}
	for (int s = 1; s < 1 << K; ++s) {
		for (int i = 1; i <= n * m; ++i)
			for (int sp = (s - 1) & s; sp; sp = (sp - 1) & s)
				if (f[sp][i] + f[s ^ sp][i] - val[i] < f[s][i]) {
					type[s][i] = 0;
					pre[s][i] = sp;
					f[s][i] = f[sp][i] + f[s ^ sp][i] - val[i];
				}
		dijkstra(s);
	}
	printf("%d\n", f[(1 << K) - 1][key[0]]);
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j) {
			if (tmpval[i][j] == 0)
				str[i][j] = 'x';
			else
				str[i][j] = '_';
		}
	getPre((1 << K) - 1, key[0]);
	for (int i = 1; i <= n; ++i)
		printf("%s\n", str[i] + 1);
	return 0;
}
