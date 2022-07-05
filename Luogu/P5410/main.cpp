#include <cctype>
#include <cstdio>
#include <cstring>
#include <algorithm>

struct FSI
{
	template<typename T>
	FSI& operator>>(T &res)
	{
		res = 0; T f = 1; char ch = getchar();
		while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
		while (isdigit(ch)) { res = res * 10 + (ch - '0') * f; ch = getchar(); }
		return *this;
	}
} read;

using i64 = long long;
const int N = 2e7 + 10;

int n, m;
int z[N], p[N];
char a[N], b[N];

void Z(char *a, int n)
{
	std::fill(z, z + n, 0);
	z[0] = n;
	for (int l = 0, r = 0, i = 1; i < n; ++i) {
		if (i < r) z[i] = std::min(z[i - l], r - i);
		while (i + z[i] < n && a[i + z[i]] == a[z[i]]) ++z[i];
		if (i + z[i] > r) {
			l = i;
			r = i + z[i];
		}
	}
}
void exkmp(char *a, int n, char *b, int m)
{
	Z(b, m);
	std::fill(p, p + n, 0);
	for (int l = 0, r = 0, i = 0; i < n; ++i) {
		if (i < r) p[i] = std::min(z[i - l], r - i);
		while (i + p[i] < n && a[i + p[i]] == b[p[i]]) ++p[i];
		if (i + p[i] > r) {
			l = i;
			r = i + p[i];
		}
	}
}

int main(void)
{
	scanf("%s%s", a, b);
	n = strlen(a);
	m = strlen(b);
	exkmp(a, n, b, m);
	i64 res1 = 0;
	for (int i = 0; i < m; ++i) {
		res1 ^= 1ll * (i + 1) * (z[i] + 1);
	}
	printf("%lld\n", res1);
	i64 res2 = 0;
	for (int i = 0; i < n; ++i) {
		res2 ^= 1ll * (i + 1) * (p[i] + 1);
	}
	printf("%lld\n", res2);
	return 0;
}
