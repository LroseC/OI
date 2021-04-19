#include <cstdio>

using namespace std;

#define reg register
#define ll long long
const int N = 1e4 + 10;

int ans;
int l, m;
int a[N];

int main()
{
	scanf("%d%d", &l, &m);
	int x, y;
	for (int i = 0; i < m; ++i) {
		scanf("%d%d", &x, &y);
		--a[x], ++a[y + 1];
	}
	for (int i = 0; i <= l; ++i) {
		if (i) a[i] += a[i - 1];
		if (a[i] < 0) continue;
		++ans;
	}
	printf("%d\n", ans);
	return 0;
}
