#include <iostream>

using namespace std;

const int N = 5e4 + 10;

int n;
int a[N];
int s[N], last[10];
int ans;

int main(void)
{
	cin >> n;
	for (int i = 1; i <= n; ++i) cin >> a[i];
	for (int i = 1; i <= n; ++i) {
		s[i] = (s[i - 1] + a[i]) % 7;
		if (last[s[i]] != 0 || s[i] == 0) ans = max(ans, i - last[s[i]]);
		else last[s[i]] = i;
	}
	cout << ans << endl;
	return 0;
}