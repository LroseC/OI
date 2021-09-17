#include <cctype>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

inline int read(void)
{
	int res = 0, f = 1; char ch = getchar();
	while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
	while (isdigit(ch)) { res = res * 10 + ch - '0'; ch = getchar(); }
	return res * f;
}

const int N = 60;

int n, c;
int pos[N], P[N];
int f[N][N][2];

int main(void)
{
	n = read(), c = read();
	for (int i = 1; i <= n; ++i) pos[i] = read(), P[i] = P[i - 1] + read();
	memset(f, 0x3f, sizeof f);
	f[c][c][0] = f[c][c][1] = 0;
	for (int len = 2; len <= n; ++len) {
		for (int l = 1, r = l + len - 1; r <= n; ++l, ++r) {
			f[l][r][0] = min(f[l][r][0], f[l + 1][r][0] + (pos[l + 1] - pos[l]) * (P[n] - P[r] + P[l]));
			f[l][r][0] = min(f[l][r][0], f[l][r - 1][0] + (pos[r] - pos[l] + pos[r] - pos[l]) * (P[n] - P[r - 1] + P[l - 1]));
			f[l][r][0] = min(f[l][r][0], f[l + 1][r][1] + (pos[r] - pos[l]) * (P[n] - P[r] + P[l]));
			f[l][r][0] = min(f[l][r][0], f[l][r - 1][1] + (pos[r] - pos[r - 1] + pos[r] - pos[l]) * (P[n] - P[r - 1] + P[l - 1]));
			f[l][r][1] = min(f[l][r][1], f[l][r - 1][1] + (pos[r] - pos[r - 1]) * (P[n] - P[r - 1] + P[l - 1]));
			f[l][r][1] = min(f[l][r][1], f[l + 1][r][1] + (pos[r] - pos[l] + pos[r] - pos[l]) * (P[n] - P[r] + P[l]));
			f[l][r][1] = min(f[l][r][1], f[l][r - 1][0] + (pos[r] - pos[l]) * (P[n] - P[r - 1] + P[l - 1]));
			f[l][r][1] = min(f[l][r][1], f[l + 1][r][0] + (pos[l + 1] - pos[l] + pos[r] - pos[l]) * (P[n] - P[r] + P[l]));
		}
	}
	printf("%d\n", min(f[1][n][0], f[1][n][1]));
	return 0;
}