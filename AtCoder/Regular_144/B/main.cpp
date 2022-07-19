#include <vector>
#include <iostream>
#include <algorithm>

#define read std::cin
using i64 = long long;
using vint = std::vector<int>;
using PII = std::pair<int, int>;
const int N = 3e5 + 10;

int n, a, b;
int v[N];

bool check(int del)
{
	i64 res = 0;
	for (int i = 0; i < n; ++i) {
		if (v[i] < del) {
			int t = del - v[i];
			res -= t % a == 0 ? t / a : t / a + 1;
		}
		else {
			int t = v[i] - del;
			res += t / b;
		}
	}
	return res >= 0;
}

int main(void)
{
	//Think twice, code once.
	std::ios::sync_with_stdio(false);
	read >> n >> a >> b;
	for (int i = 0; i < n; ++i) {
		read >> v[i];
	}
	int l = 0, r = 1e9;
	check(5);
	while (l < r) {
		int mid = l + r + 1 >> 1;
		if (check(mid)) l = mid;
		else r = mid - 1;
	}
	std::cout << l << '\n';
	return 0;
}
