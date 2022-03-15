#include <iostream>
#include <algorithm>

using namespace std;

typedef long long LL;
const int N = 1010;

int ans;
int n, c;
int w[N];
LL sum[N];

void dfs(int x, int tot)
{
	if (x > n) {
		ans = max(ans, tot);
		return;
	}
	if (tot + sum[n] - sum[x - 1] <= ans) return;
	if (tot + w[x] < c) dfs(x + 1, tot + w[x]);
	dfs(x + 1, tot);
}

int main(void)
{
	cin >> n >> c;
	for (int i = 1; i <= n; ++i) cin >> w[i];
	reverse(w + 1, w + 1 + n);
	for (int i = 1; i <= n; ++i) sum[i] = sum[i - 1] + w[i];
	dfs(1, 0);
	cout << ans << endl;
	return 0;
}