#include <set>
#include <cstdio>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 3e5 + 10;
inline int lowbit(int x) { return x & -x; }

int n, m;
set<int> S;
bool road[N];
int tr[N];
char a[N];
//小 trick: 可以用 set 存下所有 0 的位置, 这样就可以用 lower_bound 与 upper_bound 查找某一位置连续 1 的 lower_bound 与 upper_bound.

namespace SegmentTree
{
	struct node
	{
		int l, r, tag;
	} tr[(int)7e7];
	int idx;

	void add(int &u, int L, int R, int val, int l = 1, int r = n + 1)
	{
		if (!u) u = ++idx;
		if (L <= l && r <= R) {
			tr[u].tag += val;
			return;
		}
		int mid = l + r >> 1;
		if (L <= mid)
			add(tr[u].l, L, R, val, l, mid);
		if (R > mid)
			add(tr[u].r, L, R, val, mid + 1, r);
	}
	int query(int u, int pos, int l = 1, int r = n + 1)
	{
		if (!u) return 0;
		if (l == r) return tr[u].tag;
		int mid = l + r >> 1;
		if (pos <= mid) return query(tr[u].l, pos, l, mid) + tr[u].tag;
		else return query(tr[u].r, pos, mid + 1, r) + tr[u].tag;
	}
}


void add(int x, int y1, int y2, int val)
{
	for (int i = x; i <= n + 1; i += lowbit(i))
		SegmentTree::add(tr[i], y1, y2, val);
}
int query(int x, int y)
{
	int res = 0;
	for (int i = x; i; i -= lowbit(i))
		res += SegmentTree::query(tr[i], y);
	return res;
}

void addMatrix(int x1, int x2, int y1, int y2, int val)
{
	add(x1, y1, y2, val);
	add(x2 + 1, y1, y2, -val);
}

signed main(void)
{
	ios::sync_with_stdio(0);
	cin >> n >> m;
	for (int i = 0; i <= n + 1; ++i)
		S.insert(i);
	cin >> a + 1;
	for (int i = 1; i <= n; ++i)
		if (a[i] == '1') {
			S.erase(i);
			road[i] = 1;
		}
	for (int i = 1; i <= m; ++i) {
		static char op[10];
		cin >> op;
		if (op[0] == 't') {
			int pos; cin >> pos;
			road[pos] ^= 1;
			if (road[pos]) {
				S.erase(pos);
				auto it = S.lower_bound(pos);
				int right_bound = *it;
				--it;
				int left_bound = *it + 1;
				addMatrix(left_bound, pos, pos + 1, right_bound, -i);
			}
			else {
				auto it = S.lower_bound(pos);
				int right_bound = *it;
				--it;
				int left_bound = *it + 1;
				addMatrix(left_bound, pos, pos + 1, right_bound, i);
				S.insert(pos);
			}
		}
		else {
			int u, v;
			cin >> u >> v;
			auto it = S.lower_bound(u);
			int right_bound = *it;
			printf("%d\n", query(u, v) + (v <= right_bound) * i);
		}
	}
	return 0;
}
