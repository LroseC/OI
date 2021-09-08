#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int n;
int f[110][110];
char str[10010];

bool check(char s[], int n, int len)
{
	for (int i = len; i < n; ++i)
		if (s[i] != s[i % len]) return 0;
	return 1;
}

int main(void)
{
	scanf("%s", str + 1);
	n = strlen(str + 1);
	for (int len = 1; len <= n; ++len)
		for (int l = 1, r; l + len - 1 <= n; ++l) {
			r = l + len - 1;
			f[l][r] = get(l, r);
			for (int k = l; k < r; ++k) f[l][r] = min(f[l][r], f[l][k] + f[k + 1][r]);
		}
	printf("%d\n", f[1][n]);
	return 0;
}