#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 310;
typedef long long LL;

int n;
vector<int> h;

inline LL sq(int x)
{
	return 1ll * x * x;
}

int main(void)
{
	ios::sync_with_stdio(false);
	cin >> n;
	for (int i = 0; i < n; ++i) {
		int x; cin >> x;
		h.emplace_back(x);
	}
	h.emplace_back(0);
	sort(h.begin(), h.end());
	LL res = 0;
	int i = 0, j = h.size() - 1;
	while (i < j) {
		res += sq(h[j] - h[i++]);
		if (i < j)
			res += sq(h[j--] - h[i]);
	}
	cout << res << endl;
	return 0;
}