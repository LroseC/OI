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
} IO;

const int N = 1e6 + 10;
const int mod = 1e9 + 7;

struct Operation
{
	int op, l, r;
};

int n, m;
int ans = 1;
int A[N], B[N];
Operation op[N];

int main(void)
{
	IO >> n >> m;
	for (int i = 1; i <= m; ++i) {
		IO >> op[i].op >> op[i].l >> op[i].r;
	}
	for (int i = 1; i <= n; ++i) IO >> B[i];
	if (m == 1) {
		int l = op[1].l, r = op[1].r;
		for (int i = l; i <= r; ++i) {
			int res = 0;
			while (!(B[i] >> res & 1))
				++res;
			ans = 1ll * ans * res % mod;
		}
		printf("%d\n", ans);
	}
	else puts("0");
	return 0;
}
