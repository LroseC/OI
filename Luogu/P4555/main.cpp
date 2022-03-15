#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 1e5 + 10;

int n;
char str[N], s[N << 1];
int d[N << 1], id[N << 1];
int Left[N], Right[N];

void init(void)
{
	int t = strlen(str + 1);
	s[++n] = '$', s[++n] = '#';
	for (int i = 1; i <= t; ++i) {
		s[++n] = str[i];
		id[n] = i;
		s[++n] = '#';
	}
	s[++n] = '^';
}
void manacher(void)
{
	int mid = 0, mr = 0;
	for (int i = 1; i <= n; ++i) {
		d[i] = i >= mr ? 1 : min(d[mid * 2 - i], mr - i);
		while (s[i - d[i]] == s[i + d[i]])
			++d[i];
		if (i + d[i] > mr) {
			mid = i;
			mr = i + d[i];
		}
	}
//	for (int i = 1; i <= n; ++i) printf(" %c ", s[i]);
//	puts("");
//	for (int i = 1; i <= n; ++i) printf("%2d ", d[i]);
//	puts("");
//	for (int i = 1; i <= n; ++i) printf("%2d ", id[i]);
//	puts("");
}

int main(void)
{
	scanf("%s", str + 1);
	init();
	manacher();
	for (int i = 1; i <= n; ++i) {
		int l = i - d[i] + 1, r = i + d[i] - 1;
		if (s[l] == '#') ++l, --r;
		Right[id[l]] = max(Right[id[l]], d[i] - 1);
		Left[id[r]] = max(Left[id[r]], d[i] - 1);
	}
	n = strlen(str + 1);
	for (int i = 2; i <= n; ++i) Right[i] = max(Right[i], Right[i - 1] - 2);
	for (int i = n; i >= 2; --i) Left[i - 1] = max(Left[i - 1], Left[i] - 2);
	int ans = 0;
	for (int i = 1; i < n; ++i)
		ans = max(ans, Left[i] + Right[i + 1]);
	printf("%d\n", ans);
	return 0;
}
