#include <iostream>

using namespace std;

typedef long long LL;

LL ans;
int l, r;

int main(void)
{
	cin >> l >> r;
	for (int i = l; i <= r; ++i) {
		int x = i;
		while (x) {
			ans += (x % 10 == 2);
			x /= 10;
		}
	}
	cout << ans << endl;
	return 0;
}