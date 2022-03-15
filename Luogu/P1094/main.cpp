#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int cnt;
int limit, n;
vector<int> val;

int main(void)
{
	ios::sync_with_stdio(false);
	cin >> limit >> n;
	for (int i = 0; i < n; ++i) {
		int x; cin >> x;
		val.emplace_back(x);
	}
	sort(val.begin(), val.end());
	// for (auto x : val) {
		// cout << x << ' ';
	// }
	// cout << endl;
	while (val.size() >= 2) {
		int v = *val.begin();
		val.erase(val.begin());
		auto it = upper_bound(val.begin(), val.end(), limit - v);
		if (it == val.begin()) {
			val.emplace_back(v);
			break;
		}
		// cout << v << ',' << *it << endl;
		--it;
		val.erase(it);
		++cnt;
	}
	cnt += val.size();
	cout << cnt << endl;
	return 0;
}