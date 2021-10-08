#include <cctype>
#include <cstdio>

using namespace std;

const int N = 2e5 + 10;

inline int read(void)
{
	int res = 0, f = 1; char ch = getchar();
	while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
	while (isdigit(ch)) { res = res * 10 + ch - '0'; ch = getchar(); }
	return res * f;
}

int n, m, q;
int s1[N], s2[N];

int main(void)
{
	n = read(), m = read();
	for (int i = 1; i <= n; ++i) {
		do s1[i] = getchar();
		while (isspace(s1[i]));
		s1[i] -= '0'; s1[i] += s1[i - 1];
	}
	for (int i = 1; i <= m; ++i) {
		do s2[i] = getchar();
		while (isspace(s2[i]));
		s2[i] -= '0'; s2[i] += s2[i - 1];
	}
	q = read();
	while (q--) {
		int l1 = read(), r1 = read(), l2 = read(), r2 = read();
		putchar(((s1[r1] - s1[l1 - 1] & 1) + (s2[r2] - s2[l2 - 1] & 1) & 1) + '0');
		putchar('\n');
	}
}