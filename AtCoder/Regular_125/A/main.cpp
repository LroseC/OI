#include <cstdio>

using namespace std;

const int N = 2e5 + 10;

int n, m;
int a[N], v[N];

int flaga, flagv;

int main(void)
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
	for (int i = 1; i <= m; ++i) scanf("%d", &v[i]);

	flaga = a[1];
	for (int i = 2; i <= n; ++i)
		if (a[i] != flaga) flaga = 2;
	flagv = v[1];
	for (int i = 2; i <= m; ++i)
		if (v[i] != flagv) flagv = 2;

	if ((flaga != flagv) && (flaga < 2)) {
		puts("-1");
		return 0;
	}

	int cnt = 0, res = m;

	for (int i = 2; i <= m; ++i)
		if (v[i] != v[i - 1]) ++cnt;

	if (v[1] != a[1]) ++cnt;
	if (!cnt) {
		printf("%d\n", m);
		return 0;
	}
	for (int i = 1; i < n; ++i) {
		if (a[1 + i] != a[1] || a[n - i + 1] != a[1])  {
			res += i + cnt - 1;
			break;
		}
	}
	printf("%d\n", res);
	return 0;
}