#include <cctype>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

inline int read(void)
{
	int res = 0, f = 1; char ch;
	while (!isdigit(ch = getchar())) if (ch == '-') f = -1;
	do res = res * 10 + ch - '0'; while (isdigit(ch = getchar()));
	return res * f;
}

const int N = 1e5 + 10;

int n;
int a[N];

int main(void)
{
	int T;
	T = read();
	while (T--) {
		n = read();
		for (int i = 1; i <= n; ++i) {
			do a[i] = getchar();
			while (a[i] != '0' && a[i] != '1');
			if (a[i] + 1 != a[i - 1]) {
				a[i] += 1;
				putchar('1');
			}
			else putchar('0');
		}
		putchar('\n');
	}
	return 0;
}