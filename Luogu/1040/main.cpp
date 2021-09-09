#include <cctype>
#include <cstdio>
#include <algorithm>

using namespace std;

inline int read(void)
{
	int res = 0, f = 1; char ch;
	while (!isdigit(ch = getchar())) if (ch == '-') f = -1;
	do res = res * 10 + ch - '0'; while (isdigit(ch = getchar()));
	return res * f;
}

const int N = 50;
typedef long long LL;

int n;
LL v[N];
LL f[N][N];
int root[N][N];

void Print(int l, int r)
{
	if (l > r) return;
	if (l == r) {
		printf("%d ", l);
		return;
	}
	printf("%d ", root[l][r]);
	Print(l, root[l][r] - 1);
	Print(root[l][r] + 1, r);
}

int main(void)
{
	n = read();
	for (int i = 1; i <= n; ++i) f[i][i] = read();
	for (int len = 2; len <= n; ++len) {
		for (int l = 1, r = l + len - 1; r <= n; ++l, ++r) {
			LL tmp;
			tmp = f[l][l] + f[l + 1][r];
			if (tmp > f[l][r]) {
				f[l][r] = tmp;
				root[l][r] = l;
			}
			tmp = f[l][r - 1] + f[r][r];
			if (tmp > f[l][r]) {
				f[l][r] = tmp;
				root[l][r] = r;
			}
			for (int k = l + 1; k <= r - 1; ++k) {
				tmp = f[l][k - 1] * f[k + 1][r] + f[k][k];
				if (tmp > f[l][r]) {
					f[l][r] = tmp;
					root[l][r] = k;
				}
			}
		}
	}
	printf("%lld\n", f[1][n]);
	Print(1, n); puts("");
	return 0;
}