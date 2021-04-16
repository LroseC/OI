#include <queue>
#include <cstdio>
#include <iostream>

using namespace std;

#define reg register
#define ll long long
#define max(a, b) (a > b ? a : b)
const int N = 110;

struct PII
{
	int x, y, step;
	PII(int x, int y, int step) : x(x), y(y), step(step) {}
};

int r, c;
int x, y;
char f[N][N];
int gox[] = {0, 0, 1, -1, 1, 1, -1, -1};
int goy[] = {1, -1, 0, 0, 1, -1, 1, -1};

queue<PII> q;
int BFS(int, int);

int main()
{
	scanf("%d%d%d%d", &c, &r, &x, &y);
	for (int i = 0; i < r; ++i)
		for (int j = 0; j < c; ++j) cin >> f[i][j];


	cout << BFS(r - y, x - 1) << endl;

	return 0;
}
int BFS(int x, int y)
{
	int res = 0;
	f[x][y] = 'M';
	q.push(PII(x, y, 0));
	while (q.size()) {
		PII now = q.front();
		q.pop();
		res = max(res, now.step);
		for (int i = 0; i < 8; ++i) {
			int xx = now.x + gox[i], yy =now.y + goy[i];
			if (xx < 0 ||  yy < 0 || xx >= r || yy >= c || f[xx][yy] == '*' || f[xx][yy] == 'M') continue;
			f[xx][yy] = 'M';
			q.push(PII(xx, yy, now.step + 1));
		}
	}
	return res;
}
