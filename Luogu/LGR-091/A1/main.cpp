#include <cctype>
#include <cstdio>

using namespace std;

inline int read(void)
{
	int res = 0, f = 1; char ch = getchar();
	while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
	while (isdigit(ch)) { res = res * 10 + ch - '0'; ch = getchar(); }
	return res * f;
}

int n, m;

int main(void)
{
	int t = read();
	int T = read();
	while (T--) {
		n = read(), m = read();
		if (n == 1 && m == 1) {
			puts("YES");
			printf("0\n");
		}
		else if (m == 1) {
			puts("NO");
		}
		else {
			puts("YES");
			for (int i = 1; i <= n; ++i)
				for (int j = 1 ;j <= m; ++j)
					printf("%d%c", j == 1 ? i : j == 2 ? n - i : 0, j == m ? '\n' : ' ');
		}
	}
	return 0;
}