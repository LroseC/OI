#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 510;

int n;
vector<int> val[N];

int main(void)
{
	cin >> n;
	int ans = 0;
	for (int i = 0; i < n - 1; ++i)
		for (int j = 1; j < n - i; ++j) {
			int x; cin >> x;
			val[i].emplace_back(x);
			val[j + i].emplace_back(x);
		}
	for (int i = 0; i < n; ++i) {
		sort(val[i].begin(), val[i].end(), greater<int>());
		ans = max(ans, val[i][1]);
	}
	cout << 1 << '\n' << ans << endl;
	return 0;
}