#include <vector>
#include <climits>
#include <iostream>
#include <algorithm>

#define read std::cin
using i64 = long long;
using vint = std::vector<int>;
using PII = std::pair<int, int>;
const int N = 1e5 + 10;

int n, m;
char str[N];

void work(void)
{
	read >> n >> m;
	read >> str + 1;
	int res = 0;
	for (int i = 1; i <= n; ++i) {
		str[i] -= '0';
		if (str[i] == 1) res += 11;
	}

	int first = -1, last = 0;
	for (int i = 1; i <= n; ++i)
		if (str[i] == 1) {
			if (first == -1) first = i;
			last = std::max(last, i);
		}
	if (first == -1) {
		puts("0");
	}
	else if (first == last) {
		if (n - last <= m) {
			printf("%d\n", res - 10);
		}
		else if (first - 1 <= m) {
			printf("%d\n", res - 1);
		}
		else {
			printf("%d\n", res);
		}
	}
	else {
		if (first - 1 + n - last <= m) {
			printf("%d\n", res - 11);
		}
		else if (n - last <= m) {
			printf("%d\n", res - 10);
		}
		else if (first - 1 <= m) {
			printf("%d\n", res - 1);
		}
		else {
			printf("%d\n", res);
		}
	}
}

int main(void)
{
	//Think twice, code once.
#ifndef DEBUG
	std::ios::sync_with_stdio(false);
#endif
	int tt; read >> tt;
	while (tt--) {
		work();
	}
	return 0;
}
