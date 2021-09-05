#include <vector>
#include <cstdio>
#include <iostream>

using namespace std;

const int N = 3e6 + 10;

int n;
int ans;
int f[N];
vector<int> to[N];

int main(void)
{
	ios::sync_with_stdio(0);
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		int x, y; cin >> x >> y;
		to[x].emplace_back(y);
	}
	for (int x = 0; x < N; ++x) {
		f[x] = max(f[x], f[x - 1]);
		for (auto y : to[x]) {
			f[y + 1] = max(f[y + 1], f[x] + y - x + 1);
			ans = max(ans, f[y + 1]);
		}
	}
	cout << ans << endl;
	return 0;
}