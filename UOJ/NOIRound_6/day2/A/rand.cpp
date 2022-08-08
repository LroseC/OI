#include <random>
#include <cstdio>

using i32 = int;
using i64 = long long;

i32 n = 36;
i64 mod = (1ll << n) - 1;

std::random_device srd;
std::mt19937 rd(srd());

int main(void)
{
	printf("%d %lld\n", n, mod);
	for (int i = 1; i <= n; ++i) {
		i64 x = rd();
		x <<= 33;
		x += rd();
		printf("%lld ", (x % mod + mod) % mod);
	}
	puts("");
	return 0;
}
