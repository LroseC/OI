#include <vector>
#include <iostream>
#include <algorithm>

#define read std::cin
using i64 = long long;
using vint = std::vector<int>;
using PII = std::pair<int, int>;

int main(void)
{
	//Think twice, code once.
	std::ios::sync_with_stdio(false);
	int n; read >> n;
	std::cout << n * 2 << '\n';
	int buf[100010];
	int top = 0;
	while (n) {
		buf[++top] = std::min(4, n);
		n -= std::min(4, n);
	}
	while (top) std::cout << buf[top--];
	std::cout << '\n';
	return 0;
}
