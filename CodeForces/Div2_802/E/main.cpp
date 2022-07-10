#include <set>
#include <vector>
#include <iostream>
#include <algorithm>

using i64 = long long;
using vint = std::vector<int>;
using PII = std::pair<int, int>;
const int gox[] = {0, 0, 1, -1, 0};
const int goy[] = {1, -1, 0, 0, 0};

int n, m;

bool check(int x, int y, std::vector<vint> &grid)
{
	if (grid[x][y] == 1) return 1;
	for (int k = 0; k < 4; ++k) {
		int xx = x + gox[k];
		int yy = y + goy[k];
		if (xx < 0 || xx >= n || yy < 0 || yy >= m) continue;
		if (grid[xx][yy] < grid[x][y]) return 1;
	}
	return 0;
}

int main(void)
{
	std::ios::sync_with_stdio(false);
	std::cin >> n >> m;
	int nm = n * m;
	std::vector<vint> grid(n);
	std::vector<PII> pos(nm + 1);
	for (int i = 0; i < n; ++i) {
		grid[i].resize(m);
		for (int j = 0; j < m; ++j) {
			std::cin >> grid[i][j];
			pos[grid[i][j]] = {i, j};
		}
	}
	vint bad;
	for (int i = 2; i <= nm; ++i) {
		int x = pos[i].first, y = pos[i].second;
		bool fail = 1;
		for (int k = 0; k < 4; ++k) {
			int xx = x + gox[k];
			int yy = y + goy[k];
			if (xx < 0 || xx >= n || yy < 0 || yy >= m) continue;
			if (grid[xx][yy] < i) fail = 0;
		}
		if (fail) bad.emplace_back(i);
	}
	if (bad.size() == 0) {
		std::cout << "0\n";
		return 0;
	}
	if (bad.size() > 8) {
		std::cout << "2\n";
		return 0;
	}
	std::set<std::pair<PII, PII>> res;
	std::vector<PII> b;
	for (int k = 0; k < 5; ++k) {
		int xx = pos[bad[0]].first + gox[k];
		int yy = pos[bad[0]].second + goy[k];
		if (xx < 0 || xx >= n || yy < 0 || yy >= m) continue;
		b.emplace_back(xx, yy);
	}
	for (auto p : b) {
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < m; ++j) {
				std::swap(grid[p.first][p.second], grid[i][j]);
				bool sec = 1;
				for (int k = 0; k < 5; ++k) {
					int xx = p.first + gox[k];
					int yy = p.second + goy[k];
					if (xx < 0 || xx >= n || yy < 0 || yy >= m) continue;
					if (!check(xx, yy, grid)) {
						sec = 0;
					}
				}
				for (int k = 0; k < 5; ++k) {
					int xx = i + gox[k];
					int yy = j + goy[k];
					if (xx < 0 || xx >= n || yy < 0 || yy >= m) continue;
					if (!check(xx, yy, grid)) sec = 0;
				}
				for (auto t : bad) {
					if (!check(pos[t].first, pos[t].second, grid)) sec = 0;
				}
				std::swap(grid[p.first][p.second], grid[i][j]);
				if (sec) {
					PII o = std::make_pair(i, j);
					res.insert(std::make_pair(std::min(p, o), std::max(p, o)));
				}
			}
	}
	if (res.size() == 0) std::cout << "2\n";
	else std::cout << "1 " << res.size() << '\n';
	return 0;
}
