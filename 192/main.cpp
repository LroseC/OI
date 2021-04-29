#include <queue>
#include <cstdio>
#include <climits>
#include <cstring>
#include <iostream>

using namespace std;

#define ll long long

struct PII
{
	int x, y, z;
};

char ttt;
int opt, x, y;
int f[7][7][3];
int dis[7][7];
int gox[3][4] = {{-2, 0, 1, 0}, {-1, 0, 1, 0}, {-1, 0, 2, 0}};
int goy[3][4] = {{0, -2, 0, 1}, {0, -1, 0, 2}, {0, -1, 0, 1}};
int goz[3][4] = {{2, 1, 2, 1}, {1, 0, 1, 0}, {0, 2, 0, 2}};
queue<PII> q, EMPTY;

void pre_work(void);
bool check(int, int, int);
int bfs(void);
inline int s(int a)
{
	return a > 0ll ? a : -a;
}

signed main()
{
	while (cin >> ttt >> x >> y) {
		switch(ttt) {
			case 'U':
				opt = 0;
				break;
			case 'H':
				opt = 1;
				break;
			case 'V':
				opt = 2;
				break;
		}
		int ans = bfs();
		printf("%d\n", ans);
	}

	return 0;
}
void pre_work(void)
{
	dis[3][3] = ((s(x) / 3ll + s(y) / 3ll) * 2ll);
	dis[3][6] = ((s(x) / 3ll + s(y + 3ll) / 3ll) * 2ll);
	dis[3][0] = ((s(x) / 3ll + s(y - 3ll) / 3ll) * 2ll);
	dis[6][3] = ((s(x + 3ll) / 3ll + s(y) / 3ll) * 2ll);
	dis[0][3] = ((s(x - 3ll) / 3ll + s(y) / 3ll) * 2ll);
	dis[0][0] = ((s(x - 3ll) / 3ll + s(y - 3ll) / 3ll) * 2ll);
	dis[6][6] = ((s(x + 3ll) / 3ll + s(y + 3ll) / 3ll) * 2ll);
	dis[0][6] = ((s(x - 3ll) / 3ll + s(y + 3ll) / 3ll) * 2ll);
	dis[6][0] = ((s(x + 3ll) / 3ll + s(y - 3ll) / 3ll) * 2ll);
}
bool check(int x, int y, int z)
{
	switch(z) {
		case 0:
			return (x >= 0 && y >= 0 && x < 7 && y < 7);
		case 1:
			return (x >= 0 && y >= 0 && x < 6 && y < 7);
		case 2:
			return (x >= 0 && y >= 0 && x < 7 && y < 6);
	}
	return 0;
}
int bfs()
{
	q = EMPTY;
	memset(f, 0xff, sizeof f);
	q.push({x % 3 + 3, y % 3 + 3, opt});
	pre_work();
	f[q.front().x][q.front().y][q.front().z] = 0;
	int res = INT_MAX;
	while (q.size()) {
		PII t = q.front();
		q.pop();
		if (!(t.x % 3) && !(t.y % 3) && !t.z) res = min(res, abs(dis[t.x][t.y]) + f[t.x][t.y][t.z]);
		for (int i = 0; i < 4; ++i) {
			int xx = t.x + gox[t.z][i];
			int yy = t.y + goy[t.z][i];
			int zz = goz[t.z][i];
			if (check(xx, yy, zz) && !~f[xx][yy][zz]) {
				q.push({xx, yy, zz});
				f[xx][yy][zz] = f[t.x][t.y][t.z] + 1;
			}
		}
	}
	return res;
}
