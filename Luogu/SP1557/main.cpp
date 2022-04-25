#include <map>
#include <vector>
#include <cctype>
#include <cstdio>
#include <climits>
#include <cstring>
#include <algorithm>

struct FSI
{
	template<typename T>
	FSI& operator>>(T &res)
	{
		res = 0; T f = 1; char ch = getchar();
		while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
		while (isdigit(ch)) { res = res * 10 + (ch - '0') * f; ch = getchar(); }
		return *this;
	}
} read;

using i64 = long long;
using PII = std::pair<int, int>;
const int N = 1e5 + 10;

int n, m;
int val[N];
std::vector<PII> q[N];
std::map<int, int> last;
i64 tag[N << 2], tr[N << 2], maxLast[N << 2], maxTag[N << 2];
i64 ans[N];

void addNode(int u, int val, int maxval)
{
	maxTag[u] = std::max(maxTag[u], tag[u] + maxval);
	maxLast[u] = std::max(maxLast[u], tr[u] + maxval);
	tag[u] += val;
	tr[u] += val;
}
void addMax(int u, int val)
{
	maxTag[u] += val;
	maxLast[u] += val;
}
void spread(int u)
{
	if (tag[u]) {
		addNode(u << 1, tag[u], maxTag[u]);
		addNode(u << 1 | 1, tag[u], maxTag[u]);
		tag[u] = 0;
		maxTag[u] = 0;
	}
}
void maintain(int u)
{
	tr[u] = std::max(tr[u << 1], tr[u << 1 | 1]);
	maxLast[u] = std::max(maxLast[u << 1], maxLast[u << 1 | 1]);
}
void add(int L, int R, int val, int u = 1, int l = 1, int r = n)
{
	if (L <= l && r <= R) {
		addNode(u, val, val);
		return;
	}
	spread(u);
	int mid = l + r >> 1;
	if (L <= mid) add(L, R, val, u << 1, l, mid);
	if (R > mid) add(L, R, val, u << 1 | 1, mid + 1, r);
	maintain(u);
}
i64 query(int L, int R, int u = 1, int l = 1, int r = n)
{
	if (L <= l && r <= R)
		return maxLast[u];
	spread(u);
	int mid = l + r >> 1;
	i64 res = LLONG_MIN;
	if (L <= mid)
		res = std::max(res, query(L, R, u << 1, l, mid));
	if (R > mid)
		res = std::max(res, query(L, R, u << 1 | 1, mid + 1, r));
	return res;
}

int main(void)
{
	read >> n;
	for (int i = 1; i <= n; ++i)
		read >> val[i];
	read >> m;
	for (int i = 1, l, r; i <= m; ++i) {
		read >> l >> r;
		q[r].emplace_back(std::make_pair(i, l));
	}
	for (int i = 1; i <= n; ++i) {
		add(last[val[i]] + 1, i, val[i]);
		last[val[i]] = i;
		for (auto t : q[i])
			ans[t.first] = query(t.second, i);
	}
	for (int i = 1; i <= m; ++i)
		printf("%lld\n", ans[i]);
	return 0;
}
