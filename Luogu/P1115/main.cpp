#include <bits/stdc++.h>
using namespace std;
int sum[(int)2e5 + 10];
int main(void)
{
	int n, ans = INT_MIN, minx = 0; scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &sum[i]); sum[i] += sum[i - 1];
		ans = max(ans, sum[i] - minx);
		minx = min(minx, sum[i]);
	}
	printf("%d\n", ans); return 0;
}