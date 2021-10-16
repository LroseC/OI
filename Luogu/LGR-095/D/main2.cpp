#include <queue>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <assert.h>

using namespace std;

const int N = 2010;
const int D = 110;

template<typename T = int>
inline T read(void)
{
	T res = 0, f = 1; char ch = getchar();
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

struct Node
{
	int x, y, dir;
	Node(int _x, int _y, int _d) : x(_x), y(_y), dir(_d) {}
};
inline void Print(Node x)
{
	printf("x = %d, y = %d, dir = %d\n", x.x, x.y, x.dir);
}

int n, m;
int a, b, c, d;
char G[N][N];
int VIS[N][N][4];
bool vis[D];
queue<Node> q[D];
priority_queue<int, vector<int>, greater<int> > heap;
int gox[] = {1, -1, 0, 0};
int goy[] = {0, 0, 1, -1};

inline int BFS(void)
{
	memset(vis, 0, sizeof vis);
	memset(VIS, 0, sizeof VIS);
	for (int i = 1; i < D; ++i)
		while (q[i].size()) q[i].pop();
	int last = 0;
	heap.emplace(0);
	while (heap.size()) {
		int dis = heap.top();
		int u = dis % D; heap.pop();
		vis[u] = 0;

		while (q[u].size()) {
			auto t = q[u].front(); q[u].pop();
			if (VIS[t.x][t.y][t.dir]) continue;
			VIS[t.x][t.y][t.dir] = 1;
			int xx, yy, dd;
			if (G[t.x][t.y] == 'E') return dis;
			switch(G[t.x][t.y]) {
				case '#':
					break;
				case '|':
					if (t.dir < 2) {
						xx = t.x + gox[t.dir];
						yy = t.y + goy[t.dir];
						if (xx <= 0 || xx > n || yy <= 0 || yy > m) break;
						q[(u + a) % D].emplace(Node(xx, yy, t.dir));
						if (!vis[(u + a) % D]) {
							vis[(u + a) % D] = 1;
							heap.emplace((dis + a));
						}
					}
					else {
						for (dd = 0; dd < 2; ++dd) {
							xx = t.x + gox[dd];
							yy = t.y + goy[dd];
							if (xx <= 0 || xx > n || yy <= 0 || yy > m) break;
							q[(u + a) % D].emplace(Node(xx, yy, dd));
							if (!vis[(u + a) % D]) {
								vis[(u + a) % D] = 1;
								heap.emplace((dis + a));
							}
						}
					}
					break;
				case '-':
					if (t.dir >= 2) {
						xx = t.x + gox[t.dir];
						yy = t.y + goy[t.dir];
						if (xx <= 0 || xx > n || yy <= 0 || yy > m) break;
						q[(u + a) % D].emplace(Node(xx, yy, t.dir));
						if (!vis[(u + a) % D]) {
							vis[(u + a) % D] = 1;
							heap.emplace((dis + a));
						}
					}
					else {
						for (dd = 2; dd < 3; ++dd) {
							xx = t.x + gox[dd];
							yy = t.y + goy[dd];
							if (xx <= 0 || xx > n || yy <= 0 || yy > m) break;
							q[(u + a) % D].emplace(Node(xx, yy, dd));
							if (!vis[(u + a) % D]) {
								vis[(u + a) % D] = 1;
								heap.emplace((dis + a));
							}
						}
					}
					break;
				case '/':
					if (t.dir == 0) dd = 3;
					if (t.dir == 1) dd = 2;
					if (t.dir == 2) dd = 1;
					if (t.dir == 3) dd = 0;
					xx = t.x + gox[dd];
					yy = t.y + goy[dd];
					if (xx <= 0 || xx > n || yy <= 0 || yy > m) break;
					q[(u + b) % D].emplace(Node(xx, yy, dd));
					if (!vis[(u + b) % D]) {
						vis[(u + b) % D] = 1;
						heap.emplace((dis + b));
					}
					break;
				case '\\':
					if (t.dir == 0) dd = 2;
					if (t.dir == 1) dd = 3;
					if (t.dir == 2) dd = 0;
					if (t.dir == 3) dd = 1;
					xx = t.x + gox[dd];
					yy = t.y + goy[dd];
					if (xx <= 0 || xx > n || yy <= 0 || yy > m) break;
					q[(u + b) % D].emplace(Node(xx, yy, dd));
					if (!vis[(u + b) % D]) {
						vis[(u + b) % D] = 1;
						heap.emplace((dis + b));
					}
					break;
				case '.':
					for (dd = 0; dd < 4; ++dd) {
						xx = t.x + gox[dd];
						yy = t.y + goy[dd];
						if (xx <= 0 || xx > n || yy <= 0 || yy > m) continue;
						q[(u + c) % D].emplace(Node(xx, yy, dd));
						if (!vis[(u + c) % D]) {
							vis[(u + c) % D] = 1;
							heap.emplace(dis + c);
						}
					}
					break;
				case '<':
					if (t.dir < 2) {
						dd = 3;
						xx = t.x + gox[dd];
						yy = t.y + goy[dd];
						if (xx <= 0 || xx > n || yy <= 0 || yy > m) break;
						q[(u + d) % D].emplace(Node(xx, yy, dd));
						if (!vis[(u + d) % D]) {
							vis[(u + d) % D] = 1;
							heap.emplace(dis + d);
						}
					}
					if (t.dir == 3) {
						dd = 3;
						xx = t.x;
						yy = t.y - 2;
						if (xx <= 0 || xx > n || yy <= 0 || yy > m) break;
						q[u].emplace(Node(xx, yy, dd));
					}
					break;
				case '>':
					if (t.dir < 2) {
						dd = 2;
						xx = t.x + gox[dd];
						yy = t.y + goy[dd];
						if (xx <= 0 || xx > n || yy <= 0 || yy > m) break;
						q[(u + d) % D].emplace(Node(xx, yy, dd));
						if (!vis[(u + d) % D]) {
							vis[(u + d) % D] = 1;
							heap.emplace(dis + d);
						}
					}
					if (t.dir == 2) {
						dd = 2;
						xx = t.x;
						yy = t.y + 2;
						if (xx <= 0 || xx > n || yy <= 0 || yy > m) break;
						q[u].emplace(Node(xx, yy, dd));
					}
					break;
				case '^':
					if (t.dir >= 2) {
						dd = 1;
						xx = t.x + gox[dd];
						yy = t.y + goy[dd];
						if (xx <= 0 || xx > n || yy <= 0 || yy > m) break;
						q[(u + d) % D].emplace(Node(xx, yy, dd));
						if (!vis[(u + d) % D]) {
							vis[(u + d) % D] = 1;
							heap.emplace(dis + d);
						}
					}
					if (t.dir == 1) {
						dd = 1;
						xx = t.x - 2;
						yy = t.y;
						if (xx <= 0 || xx > n || yy <= 0 || yy > m) break;
						q[u].emplace(Node(xx, yy, dd));
					}
					break;
				case 'v':
					if (t.dir >= 2) {
						dd = 0;
						xx = t.x + gox[dd];
						yy = t.y + goy[dd];
						if (xx <= 0 || xx > n || yy <= 0 || yy > m) break;
						q[(u + d) % D].emplace(Node(xx, yy, dd));
						if (!vis[(u + d) % D]) {
							vis[(u + d) % D] = 1;
							heap.emplace(dis + d);
						}
					}
					if (t.dir == 0) {
						dd = 0;
						xx = t.x + 2;
						yy = t.y;
						if (xx <= 0 || xx > n || yy <= 0 || yy > m) break;
						q[u].emplace(Node(xx, yy, dd));
					}
					break;
			}
		}
	}
	return -1;
}

int main(void)
{
	n = read(), m = read();
	a = read(), b = read(), c = read(), d = read();
	assert(a <= 100 && b <= 100 && c <= 100 && d <= 100);
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j) {
			do G[i][j] = getchar();
			while (isspace(G[i][j]));
		}
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			if (G[i][j] == 'S') {
				for (int k = 0; k < 4; ++k) {
					int xx = i + gox[k];
					int yy = j + goy[k];
					if (xx >= 1 && xx <= n && yy >= 1 && yy <= m && G[xx][yy] != '#') {
						q[0].emplace(Node(xx, yy, k));
					}
				}
			}
	write(BFS());
	return 0;
}