#include <vector>
#include <cstring>
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
	//Think twice, code once.
	std::ios::sync_with_stdio(false);
	i32 tt; read >> tt;
	while (tt--) {
		i32 n; read >> n;
		vi32 a(n);
		for (int i = 0; i < n; ++i) {
			read >> a[i];
		}
		i32 m; read >> m;
		i32 top = 0;
		for (int i = 0; i < m; ++i) {
			i32 b; read >> b;
			top += b;
			top %= n;
		}
		printf("%d\n", a[top]);
	}
	return 0;
}
