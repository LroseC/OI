#include <vector>
#include <cstdio>
#include <cctype>
#include <algorithm>

using namespace std;

template<typename Int> inline void read(Int &res)
{
	Int f = 1;
	res = 0; char ch = getchar();
	while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
	while (isdigit(ch)) { res = res * 10 + (ch ^ '0'); ch = getchar(); }
	res *= f;
}

template<typename Int> inline void write(Int x)
{
	static char buf[30]; int p = -1;
	if (!x) putchar('0');
	if (x < 0) { putchar('-'); x = -x; }
	while (x) { buf[++p] = x % 10 ^ '0'; x /= 10; }
	while (p >= 0) { putchar(buf[p]); --p; }
}

typedef long long LL;

int n; LL m;
LL nums[50];
vector<LL> a, b;

void dfs(int l, int r, LL sum, vector<LL> &a)
{
	if (sum > m) return;
	if (l > r) {
		a.emplace_back(sum);
		return;
	}
	dfs(l + 1, r, sum + nums[l], a);
	dfs(l + 1, r, sum, a);
}

int main(void)
{
	read(n); read(m);
	for (int i = 1; i <= n; ++i) read(nums[i]);
	int mid = n >> 1;
	dfs(1, mid, 0, a);
	dfs(mid + 1, n, 0, b);
	// for (auto x : a) write(x), putchar(' ');
	// puts("");
	// for (auto x : b) write(x), putchar(' ');
	// puts("");
	sort(b.begin(), b.end());
	LL ans = 0;
	for (auto x : a)
		ans += upper_bound(b.begin(), b.end(), m - x) - b.begin();
	write(ans); putchar('\n');
	return 0;
}