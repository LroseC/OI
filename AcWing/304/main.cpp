#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long double LD;
const int N = 1e5 + 10;

struct Node
{
	int l, r, j;
};

int T;
int n, l, p;
char str[N][31];
int s[N], from[N];
LD f[N];
Node q[N];

LD val(int j, int i)
{
	LD tmp = abs(s[i] - s[j] + i - j - l - 1), res = 1;
	for (int i = 0; i < p; ++i) res *= tmp;
	return res + f[j];
}

void Init(void)
{
	return;
}
void Print(int n)
{
	if (n == 0) return;
	Print(from[n]);
	for (int i = from[n] + 1; i <= n; ++i) printf("%s%c", str[i], i == n ? '\n' : ' ');
}

void Work(void)
{
	scanf("%d%d%d", &n, &l, &p);
	for (int i = 1; i <= n; ++i) scanf("%s", str[i]);
	for (int i = 1; i <= n; ++i) s[i] = s[i - 1] + strlen(str[i]);

	f[0] = 0;
	int hh = 0, tt = 0;
	q[0] = {1, n, 0};
	for (int i = 1; i <= n; ++i) {
		f[i] = val(q[hh].j, i); from[i] = q[hh].j;
		if (i == q[hh].r) ++hh;

		int pos = n + 1;
		while (hh <= tt && val(i, q[tt].l) <= val(q[tt].j, q[tt].l)) pos = q[tt--].l;
		if (hh <= tt && val(i, q[tt].r) <= val(q[tt].j, q[tt].r)) {
			int l = q[tt].l, r = q[tt].r, mid;
			while (l < r) {
				mid = l + r >> 1;
				if (val(i, mid) <= val(q[tt].j, mid)) r = mid;
				else l = mid + 1;
			}
			q[tt].r = l - 1;
			pos = l;
		}
		if (pos != n + 1) q[++tt] = {pos, n, i};
	}
	if (f[n] > 1e18) puts("Too hard to arrange");
	else {
		printf("%lld\n", (long long) f[n]);
		Print(n);
	}
	puts("--------------------");
}

int main(void)
{
	scanf("%d", &T);

	while (T--) {
		Init();
		Work();
	}

	return 0;
}