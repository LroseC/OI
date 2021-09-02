#include <iostream>

using namespace std;

typedef long long LL;
const int N = 110;

int n;
LL a[N];

int main(void)
{
	cin >> n;
	for (int i = 1; i <= n; ++i) cin >> a[i];
	int r, c;
	for (c = 55, r = 1; c >= 0; --c) {
		for (int i = r; i <= n; ++i)
			if ((a[i] >> c) & 1) {
				swap(a[i], a[r]);
				break;
			}
		if (!((a[r] >> c) & 1)) continue;
		for (int i = 1; i <= n; ++i)
			if (((a[i] >> c) & 1) && (i != r)) {
				a[i] ^= a[r];
			}
		++r;
	}
	LL res = 0;
	for (int i = 1; i <= n; ++i) res ^= a[i];
	cout << res << endl;
	return 0;
}