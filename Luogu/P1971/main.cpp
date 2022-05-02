#include <cctype>
#include <cstdio>

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

int main(void)
{
	read >> n >> m;
	for (int i = 1; i <= n; ++i) {
		scanf("%s", G[i] + 1);
		for (int j = 1; j <= m; ++j)
			if (G[i][j] == '.') {
				vis[i][j] = 1;
				del.emplace_back(i, j);
			}
	}
	read >> K;
	K <<= 1;
	for (int i = 1, x, y; i <= K << 1; ++i) {
		read >> x >> y;
		vis[x][y] = 1;
		del.emplace_back(x, y);
	}
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			if (!vis[i][j])
				for (int k = 0; k < 4; ++k) {
					int xx = i + gox[k];
					int yy = i + goy[k];
					if (!vis[xx][yy] && G[i][j] != G[xx][yy])
						addFlow(getId(i, j), getId(xx, yy));
				}
	dinic::main();
	std::reverse(del.begin(), del.end());
	for (auto t : del) {
		vis[t.first][t.second] = 0;
		for (int k = 0; k < 4; ++k) {
			int xx = t.first + gox[k];
			int yy = t.second + goy[k];
			if (!vis[xx][yy] && G[t.first][t.second] != G[xx][yy])
				addFlow(getId(i, j), getId(xx, yy));
		}
		if (dinic::main())
	}
	return 0;
}
