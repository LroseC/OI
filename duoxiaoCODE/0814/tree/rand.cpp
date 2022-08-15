#include <cstdio>
#include <random>

std::random_device srd;
std::mt19937 rd(srd());
inline int myrand(int l, int r)
{ return rd() % (r - l + 1) + l; }

int n = 100000;

int main(void)
{
	printf("%d %d\n", n, std::min(int(2e5), n * (n - 1) / 4));
	for (int i = 2; i <= n; ++i) {
		printf("%d %d %d\n", myrand(i - 1, i - 1), i, myrand(1, 1e9));
	}
	return 0;
}
