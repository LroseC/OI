#include <cstdio>

using namespace std;

#define reg register
#define ll long long
#define int long long
#define lowbit(x) ((x) & -(x))
const int N = 2e5 + 10;

int n, ans1, ans2;
int a[N];
int lma[N], lmi[N], rma[N], rmi[N];

struct BIT
{
	int tree[N];
	void Insert(int x)
	{
		while (x <= n) {
			tree[x] += 1ll;
			x += lowbit(x);
		}
	}
	int Sum(int x)
	{
		int res = 0;
		while (x) {
			res += tree[x];
			x -= lowbit(x);
		}
		return res;
	}
	void Print(void)
	{
		for (int i = 1; i <= 5; ++i) printf("%d%c", tree[i], i == 5 ? '\n' : ' ');
	}
}x1, x2, y1, y2;

signed main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) scanf("%lld", &a[i]);

	for (int i = 1; i <= n; ++i) {
		lma[i] = y1.Sum(n - a[i] + 1);
		lmi[i] = x1.Sum(a[i]);
		x1.Insert(a[i]);
		y1.Insert(n - a[i] + 1);
	}
	for (int i = n; i >= 1; --i) {
		rma[i] = y2.Sum(n - a[i] + 1);
		rmi[i] = x2.Sum(a[i]);
		x2.Insert(a[i]);
		y2.Insert(n - a[i] + 1);
	}
	for (int i = 1; i <= n; ++i) {
		ans1 += lmi[i] * rmi[i];
		ans2 += lma[i] * rma[i];
	}
	// for (int i = 1; i <= n; ++i) printf("%d%c", lmi[i], i == n ? '\n' : ' ');
	// for (int i = 1; i <= n; ++i) printf("%d%c", rmi[i], i == n ? '\n' : ' ');
	// for (int i = 1; i <= n; ++i) printf("%d%c", lma[i], i == n ? '\n' : ' ');
	// for (int i = 1; i <= n; ++i) printf("%d%c", rma[i], i == n ? '\n' : ' ');
	printf("%lld %lld\n", ans2, ans1);
	return 0;
}
