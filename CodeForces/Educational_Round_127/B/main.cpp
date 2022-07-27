#include <vector>
#include <climits>
#include <cstring>
#include <iostream>
#include <algorithm>

#define read std::cin
using i32 = int;
using i64 = long long;
using vi32 = std::vector<i32>;
using vi64 = std::vector<i64>;
using PII = std::pair<i32, i32>;
const int N = 2e5 + 10;

int n;
int a[N];

void work(void)
{
	read >> n;
	for (int i = 1; i <= n; ++i) {
		read >> a[i];
	}
	bool sec = 0;
	for (int del = -1; del <= 1; ++del) {
		int last = a[1] + del;
		bool fail = 0;
		for (int i = 2; i <= n; ++i) {
			++last;
			if (-1 <= a[i] - last && a[i] - last <= 1) continue;
			else fail = 1;
		}
		if (!fail) {
			sec = 1;
			break;
		}
	}
	puts(sec ? "YES" : "NO");
}

int main(void)
{
	//Think twice, code once.
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	std::cout.tie(0);
	int tt; read >> tt;
	while (tt--) {
		work();
	}
	return 0;
}
