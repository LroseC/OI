#include <cctype>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

// #define DEBUG
const int mod = 1000003;

inline int read(void)
{
	int res = 0, f = 1; char ch;
	while (!isdigit(ch = getchar())) if (ch == '-') f = -1;
	do res = res * 10 + ch - '0'; while (isdigit(ch = getchar()));
	return res * f;
}
inline int lowbit(int x) { return x & -x; }

int n, k;
char str[20][100];
int match[60][30];
int f[60][1 << 15];

void Print(int x)
{
	for (int i = 0; i < n; ++i)
		if (x >> i & 1) putchar('1');
		else putchar('0');
}
inline int get_cnt(int x)
{
	int res = 0;
	while (x) { x -= lowbit(x); ++res; }
	return res;
}

int main(void)
{
	int T = read();
	while (T--) {
		memset(f, 0, sizeof f);
		memset(match, 0, sizeof match);

		n = read(), k = read();
		for (int i = 0; i < n; ++i)
			scanf("%s", str[i] + 1);
		int L = strlen(str[0] + 1);
		for (int i = 1; i <= L; ++i)
			for (int j = 0; j < 26; ++j)
				for (int k = 0; k < n; ++k) {
					if (str[k][i] == '?' || str[k][i] == 'a' + j)
						match[i][j] |= 1 << k;
				}

		#ifdef DEBUG
		for (int i = 1; i <= L; ++i)
			for (int j = 0; j < 26; ++j)
				printf("match[%d][%d] = ", i, j), Print(match[i][j]), putchar('\n');
		#endif
		
		f[0][(1 << n) - 1] = 1;
		for (int i = 0; i < L; ++i)
			for (int state = 0; state < 1 << n; ++state)
				for (int j = 0; j < 26; ++j) {
					if (i == 0) {
					}
					f[i + 1][state & match[i + 1][j]] = (f[i + 1][state & match[i + 1][j]] + f[i][state]) % mod;
				}
		
		#ifdef DEBUG
		for (int state = 0; state < 1 << n; ++state)
			printf("f[1]["), Print(state), printf("] = %d\n", f[1][state]);
		puts("");
		#endif

		int ans = 0;
		for (int state = 0; state < 1 << n; ++state)
			if (get_cnt(state) == k)
				ans = (ans + f[L][state]) % mod;
		printf("%d\n", ans);
	}
	return 0;
}