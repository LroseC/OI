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
template<typename T>
inline void write(T x, char end = '\n')
{
	static char buf[50]; int p = -1;
	if (x == 0) putchar('0');
	if (x < 0) { putchar('-'); x = -x; }
	while (x) { buf[++p] = x % 10; x /= 10; }
	while (~p) { putchar(buf[p] + '0'); --p; } putchar(end);
}

struct Query
{
	int key;
	int l1, r1;
	int l2, r2;
	Query(void) {}
	Query(int l1, int r1, int l2, int r2) : key(l1 - l2), l1(l1), r1(r1), l2(l2), r2(r2) {}
	bool operator<(const Query &b) const
	{
		return key < b.key;
	}
};
void Print(Query x)
{
	printf("key = %d, l1 = %d, r1 = %d, l2 = %d, r2 = %d\n", x.key, x.l1, x.r1, x.l2, x.r2);
}

int n, m, q;
char cnt[1 << 25];
char s1[N], s2[N];
short b1[N], b2[N];
Query query[N];

inline char GetCnt(int x)
{
	char res = 0;
	while (x) {
		x -= x & -x;
		++res;
	}
	return res;
}

int main(void)
{
	n = read(), m = read();
	for (int i = 1; i <= n; ++i) {
		do s1[i] = getchar();
		while (isspace(s1[i]));
		s1[i] -= '0';
	}
	for (int i = 1; i <= m; ++i) {
		do s2[i] = getchar();
		while (isspace(s2[i]));
		s2[i] -= '0';
	}
	q = read();
	for (int i = 1; i <= q; ++i) {
		int l1 = read(), r1 = read(), l2 = read(), r2 = read();
		int len = r1 - l1;
		int ans = 0;
		for (int i = 0; i <= len; ++i)
			if (s1[l1 + i] != s2[l2 + i]) ans ^= 1;
		write(ans);
	}
	return 0;
}
