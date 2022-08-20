#include <cstdio>
#include <random>

using i32 = int32_t;
using i64 = int64_t;
std::random_device srd;
std::mt19937 rd(srd());
std::mt19937_64 rdl(srd());

inline int myrand(i32 l, i32 r)
{ return rd() % (r - l + 1) + l; }
inline i64 myrandl(i64 l, i64 r)
{ return rdl() % (r - l + 1) + l; }

i32 n = 100000;

int main(void)
{
	printf("%d\n", n);
	for (int i = 2; i <= n; ++i) {
		printf("%d %ld\n", myrand(i / 2, i / 2), myrandl(0, 30));
	}
	return 0;
}
