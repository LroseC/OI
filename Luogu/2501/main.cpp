#include <vector>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long LL;
const int N = 3.5e4 + 10;

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
	a.resize(n);
	for (int i = 0; i < n; ++i) scanf("%d", &a[i]);
	for (int i = 0; i < n; ++i) a[i] -= i;
	for (int i = 0; i < n; ++i) {
		auto it = upper_bound(stk.begin(), stk.end(), a[i]);
		len[i] = it - stk.begin();
		to[len[i]].emplace_back(i);
		if (it == stk.end()) stk.emplace_back(a[i]);
		else *it = a[i];
	}
	printf("%d\n", n - stk.size());
	memset(f, 0x3f, sizeof f);
	to[0].emplace_back(0), f[0] = 0;
	for (int r = 0; r <= n; ++r) {
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
			for (int i = l; i < r; ++i) f[r] = min(f[r], f[l] + suml[i] + sumr[i + 1]);
		}
	}
	printf("%lld\n", f[n]);
	return 0;
}