#include <vector>
#include <climits>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <functional>

#define read std::cin
using i32 = int;
using i64 = long long;
using vi32 = std::vector<i32>;
using PII = std::pair<i32, i32>;
const int N = 1e5 + 10;

i32 n, m, K;
i32 a[N];

void work(void)
{
	read >> n >> m >> K;
	for (int i = 1; i <= K; ++i) {
		read >> a[i];
	}
	vi32 tmp;
	for (int i = 1; i <= K; ++i) {
		if (a[i] / n > 1) tmp.emplace_back(a[i] / n);
	}
	std::sort(tmp.begin(), tmp.end(), std::greater<i32>());
	i32 tot = m;
	bool sec = 0;
	for (int k = 0; k < tmp.size(); ++k) {
		i32 v = tmp[k];
		int del = std::min(tot, v);
		tot -= del;
		if (tot == 0) {
			if (del == 1) {
				if (k != 0 && tmp[0] > 2) sec = 1;
			}
			else {
				sec = 1;
			}
			break;
		}
	}
	tmp.clear();
	for (int i = 1; i <= K; ++i) {
		if (a[i] / m > 1) tmp.emplace_back(a[i] / m);
	}
	std::sort(tmp.begin(), tmp.end(), std::greater<i32>());
	tot = n;
	for (int k = 0; k < tmp.size(); ++k) {
		i32 v = tmp[k];
		i32 del = std::min(tot, v);
		tot -= del;
		if (tot == 0) {
			if (del == 1) {
				if (k != 0 && tmp[0] > 2) sec = 1;
			}
			else {
				sec = 1;
			}
			break;
		}
	}
	puts(sec ? "Yes" : "No");
}

int main(void)
{
	//Think twice, code once.
	std::ios::sync_with_stdio(false);
	i32 tt; read >> tt;
	while (tt--) {
		work();
	}
	return 0;
}
