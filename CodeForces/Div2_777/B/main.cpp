#include <vector>
#include <climits>
#include <iostream>
#include <algorithm>

#define read std::cin
using i64 = long long;
using vint = std::vector<int>;
using PII = std::pair<int, int>;
const int N = 105;
const int gox[] = {+1, -1,  0,  0};
const int goy[] = { 0,  0, +1, -1};

int n, m;
bool vis[N][N];
char grid[N][N];

void DFS(int x, int y, std::vector<PII> &t)
{
	if (x < 1 || y < 1 || x > n || y > m) return;
	if (grid[x][y] != 1 || vis[x][y] != 0) return;
	vis[x][y] = 1;
	t.emplace_back(x, y);
	for (int k = 0; k < 4; ++k) {
		int xx = x + gox[k];
		int yy = y + goy[k];
		DFS(xx, yy, t);
	}
}

int main(void)
{
	//Think twice, code once.
#ifndef DEBUG
	std::ios::sync_with_stdio(false);
#endif
	int tt; read >> tt;
	while (tt--) {
		read >> n >> m;
		for (int i = 1; i <= n; ++i) {
			read >> grid[i] + 1;
			for (int j = 1; j <= m; ++j) {
				vis[i][j] = 0;
				grid[i][j] -= '0';
			}
		}
		bool flag = 1;
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= m; ++j)
				if (grid[i][j] && !vis[i][j]) {
					std::vector<PII> point;
					DFS(i, j, point);
					std::sort(point.begin(), point.end());
					PII l = point.front(), r = point.back();
					int tot = (r.first - l.first + 1) * (r.second - l.second + 1);
					if (tot != point.size()) {
						flag = 0;
						break;
					}
					for (auto v : point) {
						if (v.first < l.first || v.second < l.second)
							flag = 0;
						if (v.first > r.first || v.second > r.second)
							flag = 0;
					}
				}
		std::cout << (flag ? "Yes" : "No") << '\n';
	}
	return 0;
}
