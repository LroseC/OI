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
} io;

using LL = long long;
const int N = 1e3 + 10;

struct node
{
	int x, p;
	bool operator<(const node &other) const
	{
		return x < other.x;
	}
};

int n;
node q[N];
LL x[N], v[N];
LL f[N][N];

LL calc(void)
{
	memset(f, 0, sizeof f);
	LL ans = 0;
	for (int i = 1; i <= n; ++i) {
		f[i][0] = v[i];
		ans = max(ans, f[i][0]);
	}
	for (int j = 1; j < n; ++j)
		for (int i = j + 1, k = j - 1; i <= n; ++i) {
			f[i][j] = max(f[i - 1][j] - v[i - 1], v[i - 1]);
			while (k > 0 && x[i] - x[j] >= x[j] - x[k]) {
				f[i][j] = max(f[i][j], f[j][k]);
				--k;
			}
			f[i][j] += v[i];
			ans = max(ans, f[i][j]);
		}
	// fputs("b\n", stderr);
	// for (int j = 1; j < n; ++j)
	// 	for (int i = j + 1; i <= n; ++i)
	// 		fprintf(stderr, "f[%d][%d] = %lld\n", i, j, f[i][j]);
	// fputs("e\n", stderr);
	return ans;
}

int main(void)
{
	io >> n;
	for (int i = 1; i <= n; ++i) io >> q[i].x >> q[i].p;
	sort(q + 1, q + 1 + n);
	for (int i = 1; i <= n; ++i) {
		x[i] = q[i].x;
		v[i] = q[i].p;
	}
	// fputs("b\n", stderr);
	// for (int i = 1; i <= n; ++i) fprintf(stderr, "%lld %lld\n", x[i], v[i]);
	// fputs("e\n", stderr);
	LL ans = 0;
	ans = max(ans, calc());
	reverse(x + 1, x + 1 + n);
	reverse(v + 1, v + 1 + n);
	for (int i = 1; i <= n; ++i) x[i] = -x[i] + 1e6 + 10;
	ans = max(ans, calc());
	printf("%lld\n", ans);
	return 0;
}