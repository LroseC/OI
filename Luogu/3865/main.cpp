#include <cctype>
#include <cstdio>
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
} io;

const int N = 1e5 + 10, M = 20;

int n, m;
int lg2[N];
int st[N][M];

int main(void)
{
	io >> n >> m;
	lg2[1] = 0;
	for (int i = 2; i < N; ++i) lg2[i] = lg2[i >> 1] + 1;
	for (int i = 1; i <= n; ++i) io >> st[i][0];
	for (int k = 1; k < M; ++k)
		for (int i = 1; i <= n; ++i)
			if (i + (1 << k - 1) <= n)
				st[i][k] = max(st[i][k - 1], st[i + (1 << k - 1)][k - 1]);
	while (m--) {
		int l, r; io >> l >> r;
		int t = lg2[r - l + 1];
		printf("%d\n", max(st[l][t], st[r - (1 << t) + 1][t]));
	}
	return 0;
}