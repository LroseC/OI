#include <cstdio>
#include <algorithm>

using namespace std;

const int N = 3e5 + 10, mod = 998244353;
typedef pair<int, int> PII;

int n;
PII a[N];
PII tmp[N];
int p2[N];
int sum[N];
int sump2[N];
int ans = 0;

void msort(int l, int r)
{
	if (l == r) {
		sum[r] = p2[a[r].second - (l - 1) - 1];
		return;
	}
	int mid = l + r >> 1;
	msort(l, mid); msort(mid + 1, r);
	int i = l, j = mid + 1, t = l;
	while (i <= mid && j <= r) {
		if (a[i].first <= a[j].first) {
			ans = ((ans + 1ll * p2[mid - a[i].second] * sum[j] % mod) % mod);
			tmp[t++] = a[i++];
		}
		else tmp[t++] = a[j++];
	}
	while (i <= mid) tmp[t++] = a[i++];
	while (j <= r) tmp[t++] = a[j++];
	for (int i = l; i <= r; ++i) a[i] = tmp[i];
	sum[r] = p2[a[r].second - (l - 1) - 1];
	for (int i = r - 1; i >= l; --i) sum[i] = (sum[i + 1] + p2[a[i].second - (l - 1) - 1]) % mod;
}

int main(void)
{
	p2[0] = 1;
	for (int i = 1; i < N ; ++i) p2[i] = (p2[i - 1] << 1) % mod;
	sump2[0] = 1;
	for (int i = 1; i < N; ++i) sump2[i] = (sump2[i - 1] + p2[i]) % mod;
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) scanf("%d", &a[i].first);
	for (int i = 1; i <= n; ++i) a[i].second = i;
	msort(1, n);
	printf("%d\n", ans);
	return 0;
}