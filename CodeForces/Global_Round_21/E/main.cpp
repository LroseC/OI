#include <vector>
#include <iostream>
#include <algorithm>

using i64 = long long;
using vint = std::vector<int>;
using PII = std::pair<int, int>;
const int N = 2e5 + 10, mod = 1e9 + 7;
inline int Mod(int x) { return x >= mod ? x - mod : x; }
int sum[N];

int main(void)
{
	//Think twice, code once.
	std::ios::sync_with_stdio(false);
	int n; std::cin >> n;
	vint a(n + 1);
	for (int i = 0; i <= n; ++i) {
		std::cin >> a[i];
	}
	i64 res = 0;
	for (int i = 0; i <= n; ++i) {
		sum[0] = 1;
		for (int j = 1; j < a[i]; ++j) {
			sum[j] += sum[j - 1];
		}
		for (int j = 0; j < a[i]; ++j) {
			res += sum[j];
		}
	}
	std::cout << res << '\n';
	return 0;
}
