#include <cstdio>
#include <random>
#include <algorithm>
using namespace std;
random_device rd;
int a, b;
int main(void)
{
	srand(rd());
	int n = rand() % 10 + 1, m = rand() % 10 + 1;
	for (int i = 1; i <= n; ++i) putchar(rand() % 9 + '1');
	puts("");
	for (int i = 1; i <= m; ++i) putchar(rand() % 9 + '1');
	puts("");
	return 0;
}