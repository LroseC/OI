#include <iostream>

using namespace std;

const int N = 1010, Mod = 1e9 + 7;

int f[N][N];

int main(void)
{
	int n, m;
	cin >> n >> m;
	f[0][0] = 1;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			f[i][j] = (f[i - 1][j - 1] + 1ll * j * f[i - 1][j]) % Mod;
	cout << f[n][m] << endl;
	return 0;
}