#include <vector>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long LL;
const int N = 1e5;

int n;
LL f[N];
int len[N];
LL suml[N];
LL sumr[N];
vector<int> a;
vector<int> stk;
vector<int> to[N];

int main(void)
{
	scanf("%d", &n);
	a.resize(n + 2);
	for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
	a[n + 1] = 0x3f3f3f3f;
	for (int i = 1; i <= n; ++i) a[i] -= i;
	for (int i = 1; i <= n + 1; ++i) {
		auto it = upper_bound(stk.begin(), stk.end(), a[i]);
		len[i] = it - stk.begin() + 1;
		to[len[i]].emplace_back(i);
		if (it == stk.end()) stk.emplace_back(a[i]);
		else *it = a[i];
	}
	printf("%d\n", (int)(n - stk.size() + 1));
	memset(f, 0x3f, sizeof f);
	f[0] = 0; a[0] = 0xcfcfcfcf;
	to[0].emplace_back(0);
	for (int r = 1; r <= n + 1; ++r) {
		for (auto l : to[len[r] - 1]) {
			if (l > r) break;
			if (a[l] > a[r]) continue;
			suml[l] = 0;
			for (int i = l + 1; i < r; ++i) {
				suml[i] = suml[i - 1] + abs(a[i] - a[l]);
			}
			sumr[r] = 0;
			for (int i = r - 1; i > l; --i) {
				sumr[i] = sumr[i + 1] + abs(a[i] - a[r]);
			}
			for (int i = l; i < r; ++i) f[r] = min(f[r], l == -1 ? 0 : f[l] + suml[i] + sumr[i + 1]);
		}
	}
	printf("%lld\n", f[n + 1]);
	return 0;
}