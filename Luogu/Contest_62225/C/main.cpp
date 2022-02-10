#include <cctype>
#include <cstdio>

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

int n, m;
int a[N], b[N];

int main(void)
{
	read >> n;
	for (int i = 1; i <= n; ++i)
		read >> a[i];
	read >> m;
	for (int i = 1; i <= m; ++i) {
		int l, r, pos;
		read >> l >> r >> pos;
		for (int k = l; k <= r; ++k)
			b[pos + k - l] += a[k];
	}
	for (int i = 1; i <= n; ++i)
		printf("%d\n", b[i]);
	return 0;
}
