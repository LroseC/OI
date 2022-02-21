#include <vector>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
using LL = long long;
const char endl = '\n';

struct FastStreamInputOutput
{
	using FSIO = FastStreamInputOutput;
	template<typename T>
	FSIO& operator>>(T &res)
	{
		res = 0; T f = 1; char ch = getchar();
		while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
		while (isdigit(ch)) { res = res * 10 + ch - '0'; ch = getchar(); }
		res *= f; return *this;
	}
	FSIO& operator<<(char x)
	{
		putchar(x);
		return *this;
	}
	FSIO& operator<<(const char x[])
	{
		for (int i = 0; x[i]; ++i) putchar(x[i]);
		return *this;
	}
	template<typename T>
	FSIO& operator<<(const T &res)
	{
		static char buf[50]; int p = -1; T x = res;
		if (x == 0) putchar('0');
		if (x < 0) { putchar('-'); x = -x; }
		while (x) { buf[++p] = x % 10; x /= 10; }
		while (~p) { putchar(buf[p] + '0'); --p; }
		return *this;
	}
} IO;

const int N = 1e5 + 10;

int n, m;
int w[N], val[N];
int L[N], R[N], idx;
int ans[N], rt[N];
vector<int> nums;
vector<int> G[N];
void dfs(int u, int fa)
{
	L[u] = ++idx;
	val[idx] = w[u];
	for (int v : G[u])
		if (v != fa) dfs(v, u);
	R[u] = idx;
}

struct node
{
	int l, r, sum;
} tr[N << 7];
int cnt;

void maintain(int u)
{
	tr[u].sum = tr[tr[u].l].sum + tr[tr[u].r].sum;
}
int insert(int val, int u, int l = 0, int r = nums.size())
{
	tr[++cnt] = tr[u];
	u = cnt;
	if (l == r) {
		++tr[u].sum;
		return u;
	}
	int mid = l + r >> 1;
	if (val <= mid)
		tr[u].l = insert(val, tr[u].l, l, mid);
	else
		tr[u].r = insert(val, tr[u].r, mid + 1, r);
	maintain(u);
	return u;
}
int query(int u1, int u2, int k, int l = 0, int r = nums.size())
{
	if (l == r)
		return l;
	int mid = l + r >> 1;
	int tmp = tr[tr[u2].r].sum - tr[tr[u1].r].sum;
	if (k <= tmp)
		return query(tr[u1].r, tr[u2].r, k, mid + 1, r);
	else
		return query(tr[u1].l, tr[u2].l, k - tmp, l, mid);
}

int main(void)
{
	// CHECK YOUR ARRAY TO MAKE SRUE YOUR CODE WON'T RE
	IO >> n >> m;
	for (int i = 1; i <= n; ++i) {
		IO >> w[i];
		nums.emplace_back(w[i]);
	}
	sort(nums.begin(), nums.end());
	nums.erase(unique(nums.begin(), nums.end()), nums.end());
	for (int i = 1; i <= n; ++i)
		w[i] = lower_bound(nums.begin(), nums.end(), w[i]) - nums.begin();
	for (int i = 1; i < n; ++i) {
		int u, v;
		IO >> u >> v;
		G[u].emplace_back(v);
		G[v].emplace_back(u);
	}
	dfs(1, -1);

	for (int i = 1; i <= n; ++i)
		rt[i] = insert(val[i], rt[i - 1]);
	for (int i = 1; i <= m; ++i) {
		int u, k; IO >> u >> k;
		printf("%d\n", nums[query(rt[L[u] - 1], rt[R[u]], k)]);
	}
	return 0;
}
