#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>

using i64 = long long;
using vint = std::vector<int>;
using PII = std::pair<int, int>;

int main(void)
{
	//Think twice, code once.
	std::ios::sync_with_stdio(false);
	int tt; std::cin >> tt;
	while (tt--) {
		int n;
		std::cin >> n;
		vint a(n);
		std::priority_queue<i64> heap1, heap2;
		i64 sum = 0;
		for (int i = 0; i < n; ++i) {
			std::cin >> a[i];
			sum += a[i];
			heap1.emplace(a[i]);
		}
		heap2.emplace(sum);
		bool fail = 0;
		while (heap1.size() && heap2.size()) {
			while (heap2.top() > heap1.top()) {
				i64 u = heap2.top(); heap2.pop();
				heap2.emplace(u / 2);
				heap2.emplace(u - u / 2);
			}
			if (heap2.top() != heap1.top()) {
				fail = 1;
				break;
			}
			heap2.pop(); heap1.pop();
		}
		puts(fail ? "No" : "Yes");
	}
	return 0;
}
