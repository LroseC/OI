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

const int N = 110;

int n;
char pur[N];
int f[N][N];

int main(void)
{
	scanf("%s", pur + 1);
	n = strlen(pur + 1);
	memset(f, 0x3f, sizeof f);
	for (int len = 1; len <= n; ++len) {
		for (int l = 1, r; l + len - 1 <= n; ++l) {
			if (len == 1) {
				f[l][l] = 1;
				continue;
			}
			r = l + len - 1;
			if (pur[l] == pur[r]) f[l][r] = min(f[l + 1][r], f[l][r - 1]);
			else
				for (int k = l; k < r; ++k)
					f[l][r] = min(f[l][r], f[l][k] + f[k + 1][r]);
		}
	}
	printf("%d\n", f[1][n]);
	return 0;
}