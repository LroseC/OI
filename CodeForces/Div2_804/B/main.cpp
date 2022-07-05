#include <vector>
#include <iostream>
#include <algorithm>

using i64 = long long;
using vint = std::vector<int>;
using PII = std::pair<int, int>;

vint get(int m)
{
	vint res(m);
	for (int i = 0, flg = 0; i < m; i += 2, flg ^= 1) {
		res[i] = flg;
		res[i + 1] = flg ^ 1;
	}
	return res;
}
void print(vint &x)
{
	for (auto v : x)
		std::cout << v << ' ';
	std::cout << '\n';
}
int main(void)
{
	//Think twice, code once.
	std::ios::sync_with_stdio(false);
	int tt; std::cin >> tt;
	while (tt--) {
		int n, m;
		std::cin >> n >> m;
		vint type[2];
		type[0] = get(m);
		type[1].resize(m);
		for (int i = 0; i < m; ++i)
			type[1][i] = type[0][i] ^ 1;
		for (int i = 0, flg = 0; i < n; i += 2, flg ^= 1) {
			print(type[flg]);
			print(type[flg ^ 1]);
		}
	}
	return 0;
}
