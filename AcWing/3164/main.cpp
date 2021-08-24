#include <cstdio>
#include <algorithm>

using namespace std;

typedef long long LL;
const int N = 1e5 + 10;

LL a[N];

int main(void)
{
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) scanf("%lld", &a[i]);
	int r, c;
	for (r = 0, c = 62; c >= 0; --c) {
		for (int i = r; i < n; ++i)
			if ((a[i] >> c) & 1) {
				swap(a[r], a[i]);
				break;
			}
		if (!((a[r] >> c) & 1)) continue;
		for (int i = 0; i < n; ++i)
			if (i != r && ((a[i] >> c) & 1))
				a[i] ^= a[r];
		++r;
	}
	LL res = 0;
	for (int i = 0; i < r; ++i) res ^= a[i];
	printf("%lld\n", res);
	return 0;
}