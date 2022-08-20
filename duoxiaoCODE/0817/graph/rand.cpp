#include <random>
#include <cstdio>

using i32 = int32_t;
using i64 = int64_t;

std::random_device srd;
std::mt19937 rd(srd());
inline i32 myrand(i32 l, i32 r)
{ return rd() % (r - l + 1) + l; }

i32 n = 1e5, m = 1e5;

int main(void)
{
	i32 T = 10;
	printf("%d\n", T);
	while (T--) {
		printf("%d\n", n);
		for (int i = 1; i <= n; ++i) {
			printf("%d ", myrand(1, n));
		}
		printf("%d\n", m);
		for (int i = 1; i <= m; ++i) {
			i32 op = rd() % 2;
			if (op == 0) {
				printf("1 %d %d\n", myrand(1, n), myrand(1, n));
			}
			else {
				printf("2 %d\n", myrand(1, n));
			}
		}
	}
	return 0;
}
