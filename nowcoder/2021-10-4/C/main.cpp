#include <cstdio>
#include <algorithm>

using namespace std;

const int mod = 998244353;
const long long BASE = 1e9;

typedef long long LL;

int T;
int dp[2];

int read(void)
{
	int res = 0; char ch = getchar();
	while (ch != '0' && ch != '1') ch = getchar();
	while (ch == '0' || ch == '1') { res = res << 1 | ch - '0'; ch = getchar(); }
	return res;
}
bool get(int i, LL c, LL &tmp)
{
	bool d = ((tmp & i * c) == i);
	if (tmp == i) tmp = tmp << 1 | 1;
	return d;
}

int main(void)
{
	scanf("%d", &T);
	while (T--) {
		int n; LL c;
		dp[0] = dp[1] = 0;
		n = read(); scanf("%lld", &c);
		int ans = 0;
		LL tmp = 1;
		for (int i = 1; i <= n; ++i) {
			dp[i & 1] = max(dp[i - 1 & 1], (get(i, c, tmp) ? i : 0));
			ans = (ans + dp[i & 1]) % mod;
		}
		printf("%d\n", ans);
	}
	return 0;
}
