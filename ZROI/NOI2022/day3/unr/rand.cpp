#include <random>
#include <cstdio>
#include <vector>
#include <algorithm>

std::random_device srd;

int main(void)
{
	srand(srd());
	int n = 10000;
	printf("%d\n", n);
	std::vector<int> a(n);
	for (int i = 0; i < n; ++i) {
		a[i] = rand();
	}
	std::sort(a.begin(), a.end());
	for (int i = 0; i < n; ++i) {
		printf("%d ", a[i]);
	}
	puts("");
	return 0;
}
