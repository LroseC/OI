#include <cstdio>
#include <random>
#include <cstdint>

using i32 = int32_t;
using i64 = int64_t;

std::random_device srd;
std::mt19937 rd(srd());

inline i32 myrand(i32 l, i32 r)
{ return rd() % (r - l + 1) + l; }

i32 n = 5000, m = 5000;

int main(void)
{
	printf("%d %d\n", n, m);
	for (int i = 2; i <= n; ++i) {
		printf("%d %d %d\n", myrand(1, i - 1), i, myrand(1, 3e4));
	}
	for (int i = 1; i <= m; ++i) {
		printf("%d %d %d\n", myrand(1, n), myrand(1, n), i <= 2700 ? i : myrand(1, 3e4));
	}
	return 0;
}
