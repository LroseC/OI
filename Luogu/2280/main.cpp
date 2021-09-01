#include <iostream>

using namespace std;

const int N = 5e3 + 10;

int n, m;
int f[N][N];

int main(void)
{
	ios::sync_with_stdio(0);
	cin >> n >> m;
	for (int i = 1; i <= n; ++i) {
		int x, y, v; cin >> x >> y >> v;
		++x, ++y;
		f[x][y] += v;
	}
	for (int i = 1; i < N; ++i)
		for (int j = 1; j < N; ++j) {
			f[i][j] += f[i - 1][j] + f[i][j - 1] - f[i - 1][j - 1];
		}
	int ans = 0;
	for (int i = m; i < N; ++i)
		for (int j = m; j < N; ++j) {
			ans = max(ans, f[i][j] - f[i - m][j] - f[i][j - m] + f[i - m][j - m]);
		}

	cout << ans << endl;
	return 0;
}