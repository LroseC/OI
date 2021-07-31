#include <cstdio>
#include <climits>
#include <algorithm>

using namespace std;

const int N = 2e5 + 10;

int n, m;
int a[N], b[N];

int main(void)
{
	scanf("%d%d", &n, &m);
	int ans = INT_MAX;
	for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
	for (int j = 1; j <= m; ++j) scanf("%d", &b[j]);
	sort(a + 1, a + 1 + n);
	sort(b + 1, b + 1 + m);
	for (int i = 1; i <= n; ++i) {
		int k = lower_bound(b + 1, b + 1 + m, a[i]) - b;
		if (k - 1) ans = min(ans, abs(b[k - 1] - a[i]));
		if (k <= m) ans = min(ans, abs(b[k] - a[i]));
	}
	printf("%d\n", ans);
	return 0;
}
