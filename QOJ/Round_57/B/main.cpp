#include <iostream>

using namespace std;

const int N = 100;
const int Mod = 1e9 + 7;

int n, m, k, A;
int D[N];
int l[N], r[N];
int bcnt = 0;
int ans = 0;

void dfs(int x, int renxing)
{
	if (x > n && bcnt >= k) {
		++ans;
		return;
	}
	if (x > n) return;
	for (int i = l[x]; i <= r[x]; ++i) {
		if (renxing * max(1, A - D[x]) >= i)
			++bcnt;
		dfs(x + 1, renxing);
		if (renxing * max(1, A - D[x]) >= i)
			--bcnt;
	}
}

int main(void)
{
	cin >> n >> m >> k >> A;
	for (int i = 1; i <= n; ++i) cin >> D[i] >> l[i] >> r[i];
	for (int i = 1; i <= m; ++i) {
		dfs(1, i);
	}
	cout << ans % Mod << endl;
	return 0;
}