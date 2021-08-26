#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 2e7;

int n, k;
char str[N], s[N];
int p[N];

void Init(void)
{
	s[++k] = '$'; s[++k] = '#';
	for (int i = 1; i <= n; ++i) s[++k] = str[i], s[++k] = '#';
	s[++k] = '^';
	n = k;
}
void manacher(void)
{
	int mr = 0, mid = 0;
	for (int i = 1; i <= n; ++i) {
		if (i < mr) p[i] = min(p[2 * mid - i], mr - i);
		else p[i] = 1;
		while (s[i + p[i]] == s[i - p[i]]) ++p[i];
		if (i + p[i] > mr) mid = i, mr = i + p[i];
	}
}

int main(void)
{
	scanf("%s", str + 1);
	n = strlen(str + 1);
	Init();
	manacher();
	int ans = 0;
	for (int i = 1; i <= n; ++i) ans = max(ans, p[i]);
	printf("%d\n", ans - 1);
	return 0;
}