#include <cctype>
#include <cstdio>
#include <algorithm>

using namespace std;

const int N = 250;

inline int read(void)
{
	int res = 0, f = 1; char ch = getchar();
	while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
	while (isdigit(ch)) { res = res * 10 + ch - '0'; ch = getchar(); }
	return res * f;
}

int n, ans;
int f[N][N];

int main(void)
{
	n = read();
	for (int i = 1; i <= n; ++i) f[i][i] = read();
	for (int len = 2; len <= n; ++len) {
		for (int l = 1, r; l + len - 1 <= n; ++l) {
			r = l + len - 1;
			for (int k = l; k < r; ++k) {
				if (f[l][k] == f[k + 1][r]) {
					f[l][r] = max(f[l][r], f[l][k] + 1);
					ans = max(ans, f[l][r]);
				}
			}
		}
	}
	printf("%d\n", ans);
	return 0;
}