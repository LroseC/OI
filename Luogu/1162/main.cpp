#include <queue>
#include <iostream>

using namespace std;

typedef pair<int, int> PII;
#define x first
#define y second

int n;
int f[50][50];
int gox[] = {1, -1, 0, 0};
int goy[] = {0, 0, 1, -1};
queue<PII> q;

void BFS(void)
{
	while (q.size()) {
		auto t = q.front(); q.pop();
		for (int i = 0; i < 4; ++i) {
			int xx = t.x + gox[i];
			int yy = t.y + goy[i];
			if (xx >= 1 && xx <= n && yy >= 1 && yy <= n && f[xx][yy] == 2) {
				f[xx][yy] = 0;
				q.push(PII(xx, yy));
			}
		}
	}
}

int main(void)
{
	cin >> n;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j) {
			int x; cin >> x;
			f[i][j] = x == 1 ? 1 : 2;
		}
	for (int i = 1; i <= n; ++i) {
		if (f[i][1] != 1) {
			f[i][1] = 0;
			q.emplace(PII(i, 1));
		}
		if (f[i][n] != 1) {
			f[i][n] = 0;
			q.emplace(PII(i, n));
		}
	}
	for (int i = 2; i < n; ++i) {
		if (f[1][i] != 1) {
			f[1][i] = 0;
			q.emplace(PII(1, i));
		}
		if (f[n][i] != 1) {
			f[n][i] = 0;
			q.emplace(PII(n, i));
		}
	}
	BFS();
	for (int i = 1; i <= n; ++i, cout << '\n')
		for (int j = 1; j <= n; ++j)
			cout << f[i][j] << ' ';
	return 0;
}