#include <cstdio>
#include <random>
#include <algorithm>

inline int myrand(int l, int r)
{ return rand() % (r - l + 1) + l; }

int main(void)
{
	int n = 10, q = 10;
	printf("%d %d\n", n, q);
	for (int t = 1; t <= q; ++t) {
		int op = myrand(1, 3);
		printf("%d ", op);
		if (op == 1) {
			int l = myrand(1, n);
			int r = myrand(1, n);
			if (l > r) std::swap(l, r);
			printf("%d %d %d\n", l, r, myrand(1, 4));
		}
		else if (op == 2) {
			int l = myrand(1, n);
			int r = myrand(1, n);
			if (l > r) std::swap(l, r);
			printf("%d %d\n", l, r);
		}
		else {
			int s = myrand(1, n);
			int q = myrand(1, 2);
			printf("%d %d\n", s, q);
		}
	}
	return 0;
}
