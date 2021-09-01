#include <iostream>

using namespace std;

const int N = 1010;

int n, m;
int f[N][N];

int main(void)
{
	cin >> n >> m;
	while (m--) {
		int x1, y1, x2, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		++f[x1][y1];
		--f[x2 + 1][y1];
		--f[x1][y2 + 1];
		++f[x2 + 1][y2 + 1];
	}
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j) {
			f[i][j] += f[i - 1][j] + f[i][j - 1] - f[i - 1][j - 1];
		}
	for (int i = 1; i <= n; ++i, cout << '\n')
		for (int j = 1; j <= n; ++j) {
			cout << f[i][j] << ' ';
		}
	return 0;
}