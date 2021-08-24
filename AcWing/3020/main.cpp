#include <iostream>

using namespace std;

const int MOD = 1e9 + 7;
const int N = 50010, M = 210;

int f[N][M], c[M][M];

int main(void)
{
	ios::sync_with_stdio(0);
	f[0][0] = 1;
	for (int i = 1; i < N; ++i)
		for (int j = 1; j < M; ++j)
			f[i][j] = (f[i - 1][j - 1] + 1ll * (i - 1) * f[i - 1][j]) % MOD;
	for (int i = 0; i < M; ++i)
		for (int j = 0; j <= i; ++j)
			if (!j) c[i][j] = 1;
			else c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]) % MOD;
	
	int T;
	cin >> T;
	while (T--) {
		int n, a, b;
		cin >> n >> a >> b;
		cout << (1ll * f[n - 1][a + b - 2] * c[a + b - 2][a - 1] % MOD) << endl;
	}
	return 0;
}