#include <cctype>
#include <cstdio>
#include <algorithm>

using namespace std;

typedef long long LL;

inline LL read(void)
{
	LL res = 0, f = 1; char ch;
	while (!isdigit(ch = getchar())) if (ch == '-') f = -1;
	do res = res * 10 + ch - '0'; while (isdigit(ch = getchar()));
	return res * f;
}

const int N = 4e6 + 10;

int n;
LL a[N];
int l[N], r[N];

int main(void)
{
	n = read();
	for (int i = 1; i <= n; ++i) a[i] = read();
	l[1] = 1;
	for (int i = 2; i <= n; ++i) {
		l[i] = i;
		while (a[l[i] - 1] >= a[i] && !(a[l[i] - 1] % a[i])) l[i] = l[l[i] - 1];
	}
	r[n] = n;
	for (int i = n - 1; i; --i) {
		r[i] = i;
		while (a[r[i] + 1] >= a[i] && !(a[r[i] + 1] % a[i])) r[i] = r[r[i] + 1];
	}
	int ans = 0;
	for (int i = 1; i <= n; ++i) ans = max(ans, r[i] - l[i] + 1);
	printf("%d\n", ans);
	return 0;
}