#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 1.1e7 + 10;

int n;
int d[N << 1];
char str[N], s[N << 1];

void manacher(void)
{
	int mid = 0, mr = 0;
	for (int i = 1; i <= n; ++i) {
		d[i] = i >= mr ? 1 : min(d[2 * mid - i], mr - i);
		while (s[i + d[i]] == s[i - d[i]]) ++d[i];
		if (i + d[i] > mr) mr = i + d[i], mid = i;
	}
}

int main(void)
{
	scanf("%s", str + 1);
	int t = strlen(str + 1);
	s[++n] = '$';
	s[++n] = '#';
	for (int i = 1; i <= t; ++i) {
		s[++n] = str[i];
		s[++n] = '#';
	}
	s[++n] = '^';
	manacher();
	int ans = 0;
	for (int i = 1; i <= n; ++i)
		ans = max(ans, d[i]);
	printf("%d\n", ans - 1);
	return 0;
}
