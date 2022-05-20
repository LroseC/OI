#include <vector>
#include <cctype>
#include <cstdio>
#include <algorithm>

struct FSI
{
	template<typename T>
	FSI& operator>>(T &res)
	{
		res = 0; T f = 1; char ch = getchar();
		while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
		while (isdigit(ch)) { res = res * 10 + (ch - '0') * f; ch = getchar(); }
		return *this;
	}
} read;

using i64 = long long;

int n, m;
std::vector< std::vector<int> > grid;

void swap(int a, int b)
{
	for (int i = 0; i < n; ++i)
		std::swap(grid[i][a], grid[i][b]);
}
bool check(void)
{
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < m - 1; ++j)
			if (grid[i][j] > grid[i][j + 1]) return 0;
	return 1;
}
void print(void)
{
	for (int i = 0; i < n; ++i, puts(""))
		for (int j = 0; j < m; ++j)
			printf("%d ", grid[i][j]);
}

void solve(void)
{
	read >> n >> m;
	grid.resize(n);
	for (int i = 0; i < n; ++i) {
		grid[i].resize(m);
		for (int j = 0; j < m; ++j)
			read >> grid[i][j];
	}
	if (check()) {
		printf("1 1\n");
		return;
	}
	int last = 0;
	for (int i = 0; i < n; ++i)
	for (int j = 0; j < m - 1; ++j) {
		if (grid[i][j] != grid[i][last])
			last = j;
		if (grid[i][j] > grid[i][j + 1]) {
			swap(j + 1, last);
			if (check()) {
				printf("%d %d\n", last + 1, j + 1 + 1);
				return;
			}
			else swap(j + 1, last);
			int cnt = 0, tmp = 0;
			for (int k = j + 1; k < m; ++k) {
				if (grid[i][k] < grid[i][j + 1]) {
					++cnt;
					tmp = k;
				}
			}
			if (cnt > 1) {
				puts("-1");
				return;
			}
			if (cnt == 1) {
				swap(j, tmp);
				if (check())
					printf("%d %d\n", j + 1, tmp + 1);
				else
					puts("-1");
				return;
			}
			else {
				tmp = j + 1;
				while (tmp + 1 < m && grid[i][tmp + 1] == grid[i][j + 1])
					++tmp;
				swap(j, tmp);
				if (check())
					printf("%d %d\n", j + 1, tmp + 1);
				else
					puts("-1");
				return;
			}
			puts("-1");
			return;
		}
	}
}

int main(void)
{
	int T; read >> T;
	while (T--) {
		solve();
	}
	return 0;
}
