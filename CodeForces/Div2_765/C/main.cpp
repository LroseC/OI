#include <cctype>
#include <cstdio>
#include <climits>
#include <cstring>
#include <algorithm>

using namespace std;

struct FSI
{
	template<typename T>
	FSI& operator>>(T &res)
	{
		res = 0; T f = 1; char ch = getchar();
		while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
		while (isdigit(ch)) { res = res * 10 + ch - '0'; ch = getchar(); }
		res = res * f;
		return *this;
	}
} IO;

const int N = 510;

int n, MaxDeleteCnt;
int pos[N], lim[N];
int f[2][N][N];

int main(void)
{
	IO >> n;
	IO >> pos[n + 1];
	IO >> MaxDeleteCnt;
	for (int i = 1; i <= n; ++i)
		IO >> pos[i];
	for (int i = 1; i <= n; ++i)
		IO >> lim[i];

	f[1][1][0] = 0;
	for (int i = 1; i <= n; ++i) {
		memset(f[i + 1 & 1], 0x3f, sizeof f[i + 1 & 1]);
		for (int j = 1; j <= i; ++j)
			for (int k = i - j; k <= i - 1; ++k) {
				f[i + 1 & 1][j][k + 1] = min(f[i + 1 & 1][j][k + 1], f[i & 1][j][k] + (pos[i + 1] - pos[i]) * lim[j]);
				f[i + 1 & 1][i + 1][k] = min(f[i + 1 & 1][i + 1][k], f[i & 1][j][k] + (pos[i + 1] - pos[i]) * lim[j]);
			}
	}
	int ans = INT_MAX;
	for (int i = 0; i <= MaxDeleteCnt; ++i)
		ans = min(ans, f[n + 1 & 1][n + 1][i]);
	printf("%d\n", ans);
	return 0;
}
