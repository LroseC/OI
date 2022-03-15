#include <cctype>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

struct FSI
{
	template<typename T>
	FSI& operator>>(T &res)
	{
		res = 0; T f = 1; char ch = getchar();
		while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
		while (isdigit(ch)) { res = res * 10 + ch - '0'; ch = getchar(); }
		res = res * f; return *this;
	}
} read;

const int N = 1e5 + 10;

int n;
int c[256];
int a[N], x[N], b1[N], b2[N];

int main(void)
{
	read >> n;
	for (int i = 1; i <= n; ++i) {
		read >> a[i];
		b1[i] = i;
	}
	for (int t = 0; t < 4; ++t) {
		for (int i = 1; i <= n; ++i)
			x[i] = a[i] >> (t * 8) & 255;

		memset(c, 0, sizeof c);
		for (int i = 1; i <= n; ++i) ++c[x[i]];
		for (int i = 1; i < 256; ++i) c[i] += c[i - 1];
		for (int i = n; i >= 1; --i) b2[c[x[b1[i]]]--] = b1[i], b1[i] = 0;
		swap(b1, b2);
	}
	for (int i = 1; i <= n; ++i)
		printf("%d ", a[b1[i]]);
	puts("");
	return 0;
}
