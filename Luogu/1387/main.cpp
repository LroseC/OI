#include <iostream>

using namespace std;

const int N = 110;

int n, m;
int f[N][N];
int s[N][N];

int main(void)
{
	ios::sync_with_stdio(0);
	cin >> n >> m;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j) {
			cin >> f[i][j];
			f[i][j] = !f[i][j];
		}
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j) {
			s[i][j] = s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1] + f[i][j];
		}
	for (int len = min(n, m); len; --len)
		for (int i = len; i <= n; ++i)
			for (int j = len; j <= m; ++j)
				if (!(s[i][j] - s[i - len][j] - s[i][j - len] + s[i - len][j - len])) {
					cout << len << endl;
					return 0;
				}
	return 0;
}