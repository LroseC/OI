#include <cstdio>

using namespace std;

int main(void)
{
	int l = 1, r = 1e9;
	while (l <= r) {
		int mid = l + r >> 1;
		printf("%d\n", mid);
		fflush(stdout);
		int op; scanf("%d", &op);
		if (op == 0) {
			printf("%d\n", mid);
			return 0;
		}
		if (op == 1)
			r = mid - 1;
		if (op == -1)
			l = mid + 1;
	}
	return 0;
}
