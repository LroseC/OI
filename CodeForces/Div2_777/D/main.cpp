#include <vector>
#include <climits>
#include <iostream>
#include <algorithm>

#define read std::cin
using i64 = long long;
using vint = std::vector<int>;
using PII = std::pair<int, int>;

inline int factorCnt(int x)
{
	int res = 0;
	for (int i = 2; i * i <= x; ++i)
		if (x % i == 0) {
			while (x % i == 0) {
				++res;
				x /= i;
			}
		}
	if (x != 1) ++res;
	return res;
}
inline bool isPrime(int x)
{ return factorCnt(x) == 1; }

int main(void)
{
	//Think twice, code once.
	std::ios::sync_with_stdio(false);
	int tt; read >> tt;
	while (tt--) {
		int x, d;
		read >> x >> d;
		if (isPrime(d)) {
			int cnt = 0;
			while (x % d == 0) {
				++cnt;
				x /= d;
			}
			if (cnt == 1) puts("No");
			else puts(factorCnt(x) > 1 ? "Yes" : "No");
		}
		else {
			int cnt = 0;
			for (int t = x; t % d == 0; t /= d)
				++cnt;
			if (cnt == 1) puts("No");
			else {
				x /= d;
				x /= d;
				puts(factorCnt(x) > 1 ? "Yes" : "No");
			}
		}
	}
	return 0;
}
