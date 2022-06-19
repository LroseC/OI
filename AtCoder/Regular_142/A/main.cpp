#include <set>
#include <vector>
#include <iostream>
#include <algorithm>

using i64 = long long;
using PII = std::pair<int, int>;

i64 rev(i64 x)
{
	i64 res = 0;
	while (x) {
		res = res * 10 + x % 10;
		x /= 10;
	}
	return res;
}

int main(void)
{
	std::ios::sync_with_stdio(false);
	i64 n, K;
	std::cin >> n >> K;
	if (K % 10 == 0) {
		puts("0");
	}
	else if (rev(K) < K) {
		puts("0");
	}
	else {
		int res = 0;
		i64 t = K;
		std::set<i64> S;
		while (t <= n) {
			S.insert(t);
			t *= 10;
		}
		t = rev(K);
		while (t <= n) {
			S.insert(t);
			t *= 10;
		}
		std::cout << S.size() << '\n';
	}
	return 0;
}
