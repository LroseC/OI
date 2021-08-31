#include <iostream>
#include <algorithm>

using namespace std;

typedef long long LL;
const int N = 20010;

struct Node
{
	int a, b, d;
	bool operator<(const Node &y) const
	{
		if (d != y.d) return d < y.d;
		if (d < 0) return a < y.a;
		return b > y.b;
	}
};

int T;
int n;
Node node[N];

int main(void)
{
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> T;
	while (T--) {
		cin >> n;
		for (int i = 1; i <= n; ++i) {
			int a, b; cin >> a >> b;
			int d = (a - b) / abs(a - b);
			node[i] = {a, b, d};
		}
		sort(node + 1, node + 1 + n);
		LL res = 0, sum = 0;
		for (int i = 1; i <= n; ++i) {
			sum += node[i].a;
			res = max(res, sum) + node[i].b;
		}
		cout << res << '\n';
	}
	return 0;
}