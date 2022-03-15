#include <queue>
#include <cstring>
#include <iostream>

using namespace std;

#define x first
#define y second
const int N = 110;

struct PII
{
	int x, y, c, dis;
	PII (int x, int y, int c, int dis) : x(x), y(y), c(c), dis(dis) {}
	bool operator<(const PII &b) const
	{
		return dis > b.dis;
	}
};

int n, m;
int c[N][N];
int dis[N][N][3];
bool vis[N][N][3];
int gox[] = {1, -1, 0, 0};
int goy[] = {0, 0, 1, -1};

int BFS(void)
{
	priority_queue<PII> heap;
	heap.emplace(PII(1, 1, c[1][1], 0));
	while (heap.size()) {
		auto tmp = heap.top(); heap.pop();
		if (vis[tmp.x][tmp.y][tmp.c]) continue;
		vis[tmp.x][tmp.y][tmp.c] = 1;
		dis[tmp.x][tmp.y][tmp.c] = tmp.dis;
		if (tmp.x == n && tmp.y == n) return tmp.dis;
		if (c[tmp.x][tmp.y] == 0) {
			for (int i = 0; i < 4; ++i) {
				int xx = tmp.x + gox[i];
				int yy = tmp.y + goy[i];
				if (xx > n || !xx || yy > n || !yy || !c[xx][yy]) continue;
				heap.emplace(PII(xx, yy, c[xx][yy], tmp.dis + (c[xx][yy] != tmp.c)));
			}
		}
		else
			for (int i = 0; i < 4; ++i) {
				int xx = tmp.x + gox[i];
				int yy = tmp.y + goy[i];
				if (xx > n || !xx || yy > n || !yy) continue;
				if (!c[xx][yy]) {
					heap.emplace(PII(xx, yy, tmp.c, tmp.dis + 2));
					heap.emplace(PII(xx, yy, 3 - tmp.c, tmp.dis + 3));
				}
				else heap.emplace(PII(xx, yy, c[xx][yy], tmp.dis + (c[xx][yy] != tmp.c)));
			}
	}
	return -1;
}

int main(void)
{
	cin >> n >> m;
	memset(dis, 0x3f, sizeof dis);
	dis[1][1][c[1][1]] = 0;
	for (int i = 1; i <= m; ++i) {
		int x, y, cl;
		cin >> x >> y >> cl;
		c[x][y] = cl + 1;
	}
	// for (int i = 1; i <= n; ++i, cout << '\n')
		// for (int j = 1; j <= n; ++j) cout << c[i][j] << ' ';
	cout << BFS() << endl;
	// puts("...");
	// for (int i = 1; i <= n; ++i, cout << '\n')
		// for (int j = 1; j <= n; ++j)
			// printf("%10d,%10d ", dis[i][j][1], dis[i][j][2]);
	return 0;
}