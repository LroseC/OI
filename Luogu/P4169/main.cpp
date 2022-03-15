#include <vector>
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

const int N = 3e5 + 10;

struct Query
{
	int x, y, t, v, id;
	Query(void) {}
	Query(int _x, int _y, int _t, int _v, int _id) : x(_x), y(_y), t(_t), v(_v), id(_id) {}
	struct cmpx
	{
		bool operator()(const Query &a, const Query &b)
		{
			if (a.x == b.x) {
				return a.v > b.v;
			}
			return a.x < b.x;
		}
	};
};

namespace BIT
{
	inline int lowbit(int x) { return x & -x; }
	int tr[N];
	int stk[N], top = 0;
	void addo(int x)
	{
		for (int i = x; i < N; i += lowbit(i))
			tr[i] = 0;
	}
	void add(int x, int val)
	{
		stk[++top] = x;
		for (int i = x; i < N; i += lowbit(i))
			tr[i] = max(tr[i], val);
	}
	int query(int x)
	{
		int res = 0;
		for (int i = x; i; i -= lowbit(i))
			res = max(res, tr[i]);
		return res;
	}
	void init(void)
	{
		while (top) {
			addo(stk[top]);
			--top;
		}
	}
}

int n, m;
int ans[N], idcnt;
vector<Query> q, t;

void CDQ(int l, int r)
{
	if (l == r) return;
	int mid = l + r >> 1;
	CDQ(l, mid); CDQ(mid + 1, r);
	BIT::init();
	int i = l, j = mid + 1, k = l;
	while (i <= mid && j <= r) {
		if (q[i].y <= q[j].y) {
			if (q[i].v) {
				BIT::add(q[i].t, q[i].x + q[i].y);
			}
			t[k++] = q[i++];
		}
		else {
			if (!q[j].v) {
				int tmp = BIT::query(q[j].t);
				if (tmp)
					ans[q[j].id] = min(ans[q[j].id], q[j].x + q[j].y - tmp);
			}
			t[k++] = q[j++];
		}
	}
	while (i <= mid) {
		t[k++] = q[i++];
	}
	while (j <= r) {
		int tmp = BIT::query(q[j].t);
		if (tmp)
			ans[q[j].id] = min(ans[q[j].id], q[j].x + q[j].y - tmp);
		t[k++] = q[j++];
	}
	for (int i = l; i <= r; ++i) q[i] = t[i];
}

// int x, y, t, v, id;

int main(void)
{
	io >> n >> m;
	for (int i = 1; i <= n; ++i) {
		int x, y; io >> x >> y;
		++x, ++y;
		q.emplace_back(x, y, 1, 1, 0);
	}
	for (int i = 1; i <= m; ++i) {
		int op, x, y; io >> op >> x >> y;
		++x, ++y;
		if (op == 1)
			q.emplace_back(x, y, i + 1, 1, 0);
		else {
			++idcnt;
			q.emplace_back(x, y, i + 1, 0, idcnt);
		}
	}
	memset(ans, 0x3f, sizeof ans);
	t.resize(q.size());
	for (int i = 0; i < 4; ++i) {
		for (int i = 0; i < q.size(); ++i) {
			int x = q[i].x, y = q[i].y;
			q[i].x = 1e6 + 5 - y;
			q[i].y = x;
		}
		sort(q.begin(), q.end(), Query::cmpx());
		CDQ(0, q.size() - 1);
	}
	for (int i = 1; i <= idcnt; ++i)
		printf("%d\n", ans[i]);
	return 0;
}