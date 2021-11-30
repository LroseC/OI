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
} io;

const int N = 1e6 + 10;

int n, K;
int h[N], f[N];
int q[N];

int main(void)
{
	io >> n;
	for (int i = 1; i <= n; ++i) io >> h[i];
	int Q; io >> Q;
	while (Q--) {
		int K; io >> K;
		q[0] = 1;
		int hh = 0, tt = 0;
		for (int i = 2; i <= n; ++i) {
			while (hh <= tt && i - q[hh] > K) ++hh;
			f[i] = f[q[hh]] + (h[i] >= h[q[hh]]);
			auto cmp = [](int a, int b)
			{
				if (f[a] != f[b]) return f[a] < f[b];
				return h[a] >= h[b];
			};
			while (hh <= tt && cmp(i, q[tt])) --tt;
			q[++tt] = i;
		}
		printf("%d\n", f[n]);
	}
	return 0;
}