#include <vector>
#include <iostream>
#include <algorithm>

using i64 = long long;
using vint = std::vector<int>;
using PII = std::pair<int, int>;
const int N = 4e4 + 10, mod = 1e9 + 7;
inline int Mod(int x) { return x >= mod ? x - mod : x; }

int f[N];

inline int rev(int x)
{
	int res = 0;
	while (x) {
		res = res * 10 + x % 10;
		x /= 10;
	}
	return res;
}

int main(void)
{
	//Think twice, code once.
	std::ios::sync_with_stdio(false);
	f[0] = 1;
	for (int i = 1; i < N; ++i)
		if (rev(i) == i) {
			for (int j = i; j < N; ++j)
				f[j] = Mod(f[j] + f[j - i]);
		}
	int tt; std::cin >> tt;
	while (tt--) {
		int n; std::cin >> n;
		std::cout << f[n] << '\n';
	}
	return 0;
}
