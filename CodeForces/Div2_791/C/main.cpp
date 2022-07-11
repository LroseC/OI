#include <set>
#include <vector>
#include <iostream>
#include <algorithm>

using i64 = long long;
using vint = std::vector<int>;
using PII = std::pair<int, int>;
inline int lowbit(int x) { return x & -x; }

int n, m;

void add(int x, int v, vint &tr)
{
	for (int i = x; i < tr.size(); i += lowbit(i))
		tr[i] += v;
}
int query(int x, vint &tr)
{
	int res = 0;
	for (int i = x; i; i -= lowbit(i))
		res += tr[i];
	return res;
}

int main(void)
{
	//Think twice, code once.
	std::ios::sync_with_stdio(false);
	std::cin >> n >> m;
	vint X(n + 1), Y(n + 1);
	vint trX(n + 1), trY(n + 1);
	for (int i = 1; i <= m; ++i) {
		int t; std::cin >> t;
		if (t == 1) {
			int x, y;
			std::cin >> x >> y;
			++X[x];
			if (X[x] == 1)
				add(x, 1, trX);
			++Y[y];
			if (Y[y] == 1)
				add(y, 1, trY);
		}
		else if (t == 2) {
			int x, y;
			std::cin >> x >> y;
			--X[x];
			if (X[x] == 0)
				add(x, -1, trX);
			--Y[y];
			if (Y[y] == 0)
				add(y, -1, trY);
		}
		else {
			int x1, x2, y1, y2;
			std::cin >> x1 >> y1 >> x2 >> y2;
			if (query(x2, trX) - query(x1 - 1, trX) == x2 - (x1 - 1)) {
				std::cout << "Yes\n";
			}
			else if (query(y2, trY) - query(y1 - 1, trY) == y2 - (y1 - 1)) {
				std::cout << "Yes\n";
			}
			else {
				std::cout << "No\n";
			}
		}
	}
	return 0;
}
