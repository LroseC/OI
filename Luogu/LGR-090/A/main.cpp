#include <iostream>

using namespace std;

const int N = 1e5 + 10;

int n, m;
int a[N];


int main(void)
{
	ios::sync_with_stdio(0);
	int T;
	cin >> T;
	while (T--) {
		cin >> n >> m;
		if (m >= n - 1) {
			for (int i = 1; i <= n; ++i) cout << i << ' ';
			cout << '\n';
			continue;
		}
		else if (m < n / 2) {
			for (int i = 0; i < m; ++i) a[i] = i + 1;
			for (int j = n, i = m; i < n; ++i, --j) a[i] = j;
			for (int i = 0; i < m; ++i) swap(a[i], a[i + m]);
			for (int i = 0; i < n; ++i) cout << a[i] << ' ';
			cout << '\n';
			continue;
		}
		else {
			m = (n - m);
			int k = n % m;
			for (int cnt = 0, i = k, j = n - 1; cnt < m; ++cnt, i = (i + 1) % m, --j)
				a[i] = j;
			for (int i = m; i < n; ++i) a[i] = i - m;
			for (int i = 0; i < n; ++i) cout << a[i] + 1 << ' ';
			cout << '\n';
		}
	}
	return 0;
}