#include <queue>
#include <cstdio>

using namespace std;

#define reg register
#define ll long long
const int N = 1010;

struct PII
{
	int x, y, light;
	PII(int x, int y, int light)
	{
		this->x = x, this->y = y, this->light = light;
	}
};


void BFS(void);

int n, m;
int f[N][N];
int gox[] = {0, 0, 1, -1};
int goy[] = {1, -1, 0, 0};
queue<PII> q;

int main()
{
	reg char ch;
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < m; ++j) {
			ch = getchar();
			while (ch == ' ' || ch == '\n') ch = getchar();
			if (ch == '.') {
				q.push(PII(i, j, 15));
				f[i][j] = 15;
			}
		}

	BFS();

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j)
			if (f[i][j] < 8) putchar('X');
			else putchar('O');
		putchar('\n');
	}

	return 0;
}
void BFS(void)
{
	while(q.size()) {
		PII now = q.front();
		q.pop();
		for (int i = 0; i < 4; ++i) {
			int x = now.x + gox[i], y = now.y + goy[i];
			if (x < 0 || y < 0 || x >= n || y >= m || f[x][y]) continue;
			f[x][y] = now.light - 1;
			q.push(PII(x, y, f[x][y]));
		}
	}
	return;
}
