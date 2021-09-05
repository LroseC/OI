#include <cstdio>
#include <iostream>

using namespace std;

const int Mod = 1e9 + 7;

int n, m, k;
char a[10010], b[10010];
long long f[2][210][210][2];

int main(void)
{
	cin >> n >> m >> k;
	cin >> a + 1 >> b + 1;
	f[0][0][0][0] = f[1][0][0][0] = 1;
	for (int i = 1, t = 1; i <= n; ++i, t ^= 1)
		for (int j = 1; j <= m; ++j)
			for (int p = 1; p <= k; ++p) {
				f[t][j][p][0] = f[t ^ 1][j][p][0] + f[t ^ 1][j][p][1];
				if (a[i] == b[j]) 
					f[t][j][p][1] = f[t ^ 1][j - 1][p][1] + f[t ^ 1][j - 1][p - 1][0] + f[t ^ 1][j - 1][p - 1][1];
				else f[t][j][p][1] = 0;
				f[t][j][p][0] %= Mod;
				f[t][j][p][1] %= Mod;
			}
	cout << (f[n & 1][m][k][1] + f[n & 1][m][k][0]) % Mod << endl;
	return 0;
}