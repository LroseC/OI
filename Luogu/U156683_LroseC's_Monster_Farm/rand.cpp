#include <ctime>
#include <cstdio>
#include <cstdlib>

using namespace std;

int my_rand(int l, int r);

int n, m;

int main()
{
	srand(time(NULL));
	n = my_rand(1, 1000), m = my_rand(1, 1000);
	printf("%d %d\n", n, m);
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j)
			putchar(my_rand(0, 1000) > 20 ? 'B' : '.'), putchar(' ');
		putchar('\n');
	}
	return 0;
}
int my_rand(int l, int r)
{
	return rand() % (r - l + 1) + l;
}
