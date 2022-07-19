#include <vector>
#include <iostream>
#include <algorithm>

#define read std::cin
using i64 = long long;
using vint = std::vector<int>;
using PII = std::pair<int, int>;

int n, K;

int main(void)
{
	//Think twice, code once.
	std::ios::sync_with_stdio(false);
	read >> n >> K;
	vint x(n);
	for (int i = 0; i < n; ++i) {
		x[i] = i;
	}
	do {
		bool fail = 0;
		for (int i = 0; i < n; ++i)
			if (std::abs(x[i] - i) < K) {
				fail = 1;
				break;
			}
		if (!fail) break;
	} while (std::next_permutation(x.begin(), x.end()));
	for (int i = 0; i < n; ++i)
		printf("%d ", x[i] + 1);
	puts("");
	return 0;
}
