#include <cctype>
#include <cstdio>

using namespace std;

struct FSI
{
	template<typename T>
	FSI& operator>>(T &res) {
		res = 0; T f = 1; char ch = getchar();
		while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
		while (isdigit(ch)) { res = res * 10 + ch - '0'; ch = getchar(); }
		res = res * f; return *this;
	}
} io;

const int N = 3e5 + 10;

int n, m;
int a[N], b[N];

int main(void)
{
	io >> n;
	for (int i = 1; i <= n; ++i) io >> a[i];
	io >> m;
	while (m--) {
		static int op, l, r, x;
		io >> op;
		if (op == 1) {
			io >> l >> r >> x;
			for (int i = l; i <= r; ++i) b[i] = a[i];
			for (int i = l, j = 0; i <= r; ++i, ++j)
				a[x + j] = b[i];
		}
		if (op == 2) {
			io >> l >> r;
			for (int i = l; i <= r; ++i) a[i] = a[i] / 2;
		}
		if (op == 3) {
			io >> l >> r;
			long long res = 0;
			for (int i = l; i <= r; ++i) res += a[i];
			printf("%lld\n", res);
		}
	}
	return 0;
}