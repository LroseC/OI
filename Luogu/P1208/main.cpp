#include <iostream>
#include <algorithm>

using namespace std;

typedef long long LL;
typedef pair<int, int> PII;

int n, m;
PII farm[100010];
LL ans = 0;

int main(void)
{
	cin >> n >> m;
	for (int i = 0; i < m; ++i) cin >> farm[i].first >> farm[i].second;
	sort(farm, farm + m);
	for (int i = 0; n; ++i) {
		int num = min(n, farm[i].second);
		ans += 1ll * num * farm[i].first;
		n -= num;
	}
	cout << ans << endl;
	return 0;
}