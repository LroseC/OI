#include <queue>
#include <iostream>

using namespace std;

const int N = 60;
#define x first
#define y second
typedef pair<int, int> PII;

struct State
{
	int x, y, dir, tim;
};

int n, m;
int o_G[N][N];
int G[N][N];
bool vis[N][N][4];
PII S, T;
queue<State> q;
int gox[] = {-1, 0, 1, 0};
int goy[] = {0, 1, 0, -1};

inline int char2int(char ch)
{
	if (ch == 'N') return 0;
	if (ch == 'E') return 1;
	if (ch == 'S') return 2;
	if (ch == 'W') return 3;
}

inline int BFS(void)
{
	while (q.size()) {
		auto t = q.front(); q.pop();
		if (vis[t.x][t.y][t.dir]) continue;
		vis[t.x][t.y][t.dir] = 1;
		// printf("x = %d, y = %d, dir = %d, time = %d\n", t.x, t.y, t.dir, t.tim);
		if (t.x == T.x && t.y == T.y) return t.tim;
		for (int i = 1; i <= 3; ++i) {
			int xx = t.x + gox[t.dir] * i;
			int yy = t.y + goy[t.dir] * i;
			if (xx < 1 || yy < 1 || xx > n || yy > m) continue;
			if (G[xx][yy]) break;
			q.emplace(State({xx, yy, t.dir, t.tim + 1}));
		}
		q.emplace(State({t.x, t.y, (t.dir + 1) % 4, t.tim + 1}));
		q.emplace(State({t.x, t.y, (t.dir + 3) % 4, t.tim + 1}));
	}
	return -1;
}

int main(void)
{
	cin >> n >> m;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			cin >> o_G[i][j];

	--n, --m;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			for (int dx = 0; dx < 2; ++dx)
				for (int dy = 0; dy < 2; ++dy)
					if (o_G[i + dx][j + dy])
						G[i][j] = 1;
	
	cin >> S.x >> S.y >> T.x >> T.y;
	char ch; cin >> ch;
	q.emplace(State({S.x, S.y, char2int(ch)}));
	
	cout << BFS() << endl;
	return 0;
}