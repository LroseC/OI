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

const int N = 210;
typedef pair<int, int> PII;

int n;
int a[N], b[N];
int f[N][N];

int main(void)
{
	n = read();
	int nn = n << 1;
	for (int i = 1; i <= n; ++i) a[i] = read();
	memcpy(a + 1 + n, a + 1, 4 * n);
	for (int i = 1; i <= nn; ++i) b[i] = a[i + 1];
	for (int len = 2; len <= n; ++len)
		for (int l = 1, r; l + len - 1 <= nn; ++l) {
			r = l + len - 1;
			for (int k = l; k < r; ++k) {
				f[l][r] = max(f[l][r], f[l][k] + f[k + 1][r] + a[l] * b[k] * b[r]);
			}
		}
	int ans = 0;
	for (int i = 1; i <= n; ++i) ans = max(ans, f[i][i + n - 1]);
	printf("%d\n", ans);
	return 0;
}