#include <cstdio>

using namespace std;

#define reg register
#define ll long long

int n, m;

int main()
{
	freopen("test01.in", "w", stdout);
	printf("%d %d\n", 50, 50);
	for (int i = 0; i < 50; ++i) {
		for (int j = 0; j < 50; ++j) putchar('1');
		putchar('\n');
	}
	puts("0");
	return 0;
}
