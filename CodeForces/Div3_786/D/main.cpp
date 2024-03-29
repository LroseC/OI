#include <vector>
#include <climits>
#include <iostream>
#include <algorithm>

#define read std::cin
using i32 = int;
using i64 = long long;
using vi32 = std::vector<i32>;
using PII = std::pair<i32, i32>;

int main(void)
{
	//Think twice, code once.;
	std::ios::sync_with_stdio(false);
	i32 tt; read >> tt;
	while (tt--) {
		i32 n; read >> n;
		vi32 a(n), b(n);
		for (int i = 0; i < n; ++i) {
			read >> a[i];
			b[i] = a[i];
		}
		std::sort(b.begin(), b.end());
		for (int i = n - 1; i >= 0; i -= 2) {
			if (i - 1 >= 0) {
				if (a[i - 1] > a[i])
					std::swap(a[i - 1], a[i]);
			}
		}
		bool sec = 1;
		for (int i = 0; i < n; ++i)
			if (a[i] != b[i]) sec = 0;
		puts(sec ? "Yes" : "No");
	}
	return 0;
}
