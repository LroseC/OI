#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 1e5 + 10;

int n, m;
int nex[N];
char str[N], s[N];
int f[N], g[N];

bool check(int pos)
{
	if (pos < m) return 0;
	pos -= m;
	for (int i = 1; i <= m; ++i) {
		if (str[pos + i] != '?' && str[pos + i] != s[i])
			return 0;
	}
	return 1;
}

int main(void)
{
	scanf("%s%s", str + 1, s + 1);
	n = strlen(str + 1);
	m = strlen(s + 1);

	for (int i = 2, j = 0; i <= m; ++i) {
		while (j && s[i] != s[j + 1])
			j = nex[j];
		if (s[i] == s[j + 1])
			++j;
		nex[i] = j;
	}

	nex[0] = -1;
	for (int i = 1; i <= n; ++i) {
		f[i] = f[i - 1];
		if (check(i)) {
			for (int j = nex[m]; ~j; j = nex[j])
				g[i] = max(g[i], g[i - (m - j)] + 1);
			g[i] = max(g[i], f[i - m] + 1);
			f[i] = max(f[i], g[i]);
		}
	}

	printf("%d\n", f[n]);
	return 0;
}
