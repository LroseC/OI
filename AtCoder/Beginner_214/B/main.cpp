#include <cstdio>

using namespace std;

int s, t;

int main(void)
{
	int cnt = 0;
	scanf("%d%d", &s, &t);
	for (int i = 0; i <= s; ++i)
		for (int j = s - i; j >= 0; --j)
			for (int k = s - i - j; k >= 0; --k)
				if (i * j * k <= t) ++cnt;
	printf("%d\n", cnt);
	return 0;
}