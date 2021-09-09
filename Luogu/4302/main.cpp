#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int n;
int m[101];
long long f[110][110];
char str[1 << 10];
char buf[1 << 10];

bool check(char s[], int n, int len)
{
	for (int i = len; i < n; ++i)
		if (s[i] != s[i % len]) return 0;
	return 1;
}

int main(void)
{
	memset(f, 0x3f, sizeof f);
	scanf("%s", str + 1);
	n = strlen(str + 1);
	// n = fread(buf, 1, 1 << 10, stdin);
	// for (int i = 0; i < n; ++i)
	// 	if (buf[i] == '\n' || buf[i] == ' ') {
	// 		n = i - 1;
	// 		break;
	// 	}
	// 	else str[i + 1] = buf[i];
	// printf("n = %d, str = %s\n", n, str + 1);

	for (int i = 0; i < 10; ++i) m[i] = 1;
	for (int i = 10; i < 100; ++i) m[i] = 2;
	m[100] = 3;

	for (int i = 1; i <= n; ++i) f[i][i] = 1;
	for (int len = 2; len <= n; ++len)
		for (int l = 1, r = l + len - 1; r <= n; ++l, ++r) {
			f[l][r] = len;
			for (int k = l; k < r; ++k)
				f[l][r] = min(f[l][r], f[l][k] + f[k + 1][r]);
			for (int k = l; k <= r; ++k) {
				int le = k - l + 1;
				if (len % le) continue;
				if (check(str + l, len, le))
					f[l][r] = min(f[l][r], 2 + f[l][k] + m[len / le]);
			}
		}
	printf("%lld\n", f[1][n]);
	return 0;
}