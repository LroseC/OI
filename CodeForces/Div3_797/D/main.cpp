#include <vector>
#include <iostream>
#include <algorithm>

using i64 = long long;
const int N = 1e6 + 11;

char str[N];
int sum[N];

int main(void)
{
	std::ios::sync_with_stdio(false);
	int tt; std::cin >> tt;
	while (tt--) {
		int n, K;
		std::cin >> n >> K;
		std::cin >> str + 1;
		for (int i = 1; i <= n; ++i) {
			sum[i] = sum[i - 1] + (str[i] == 'W');
		}
		int res = 0x3f3f3f3f;
		for (int i = 1, j = K; j <= n; ++i, ++j) {
			res = std::min(res, sum[j] - sum[i - 1]);
		}
		std::cout << res << '\n';
	}
	return 0;
}
