#include <queue>
#include <vector>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 1010;
const int INF = 0x3f3f3f3f;

#define x first
#define y second
typedef long long LL;
typedef pair<int, int> PII;

int n, m;
int G[N][N];
int d1[N][N];
int d2[N][N];
PII S, T;
vector<PII> ones;
int gox[] = {-1, 0, 1, 0};
int goy[] = {0, 1, 0, -1};

void BFS(int x, int y, int d[N][N])
{
	queue<PII> q;
	q.emplace(PII({x, y}));
	d[x][y] = 0;
	while (q.size()) {
		auto t = q.front(); q.pop();
		for (int i = 0; i < 4; ++i) {
			int xx = t.x + gox[i];
			int yy = t.y + goy[i];
			if (xx < 1 || yy < 1 || xx > n || yy > m) continue;
			if (d[xx][yy] != INF || G[xx][yy] == 1) continue;
			d[xx][yy] = d[t.x][t.y] + 1;
			q.push(PII({xx, yy}));
		}
	}
}

int main(void)
{
	scanf("%d%d", &m, &n);
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j) {
			scanf("%d", &G[i][j]);
			if (G[i][j] == 4) ones.emplace_back(PII({i, j}));
			if (G[i][j] == 2) S.x = i, S.y = j;
			if (G[i][j] == 3) T.x = i, T.y = j;
		}
	memset(d1, INF, sizeof d1);
	memset(d2, INF, sizeof d2);
	BFS(S.x, S.y, d1);
	BFS(T.x, T.y, d2);
	int ans = INF;
	for (auto t : ones) ans = min(ans, d1[t.x][t.y] + d2[t.x][t.y]);
	printf("%d\n", ans);
	return 0;
}