#include <random>
#include <cstdio>

using i32 = int32_t;
using i64 = int64_t;

std::random_device srd;
std::mt19937 rd(srd());
inline i32 myrand(i32 l, i32 r)
{ return rd() % (r - l + 1) + l; }

i32 n = 20;
bool vis[1000];

i32 getRd(i32 l, i32 r)
{
	i32 tmp;
	do tmp = myrand(l, r);
	while (vis[tmp]);
	vis[tmp] = 1;
	return tmp;
}

int main(void)
{
	printf("%d %d\n", n, std::max(1, myrand(n / 6, n / 2)));
	for (int i = 1; i <= n; ++i) {
		printf("%d %d %d\n", getRd(1, 100), getRd(1, 100), myrand(0, 1));
	}
	return 0;
}
