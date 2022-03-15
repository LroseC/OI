#include <vector>
#include <cstdio>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 2e4 + 10;

struct node
{
	int l, r;
	int sum, lsum, rsum;
	node(void) { l = r = sum = lsum = rsum = 0; }
};

int n, m, idx;
int A[N], root[N];
vector<int> nums;
vector<int> Map[N];
node tr[N << 5];

node merge(const node &a, const node &b)
{
	node res;
	res.sum = a.sum + b.sum;
	res.lsum = max(a.lsum, a.sum + b.lsum);
	res.rsum = max(b.rsum, b.sum + a.rsum);
	return res;
}
void maintain(int u)
{
	auto res = merge(tr[tr[u].l], tr[tr[u].r]);
	tr[u].sum = res.sum;
	tr[u].lsum = res.lsum;
	tr[u].rsum = res.rsum;
}

int build(int l, int r)
{
	int u = ++idx;
	if (l == r) {
		tr[u].lsum = tr[u].rsum = tr[u].sum = 1;
		return u;
	}
	int mid = l + r >> 1;
	tr[u].l = build(l, mid);
	tr[u].r = build(mid + 1, r);
	maintain(u);
	return u;
}
void change(int u, int k, int val, int l = 1, int r = n)
{
	if (l == r) {
		tr[u].lsum = tr[u].rsum = tr[u].sum = val;
		return ;
	}
	int mid = l + r >> 1;
	int v = ++idx;
	if (k <= mid) {
		tr[v] = tr[tr[u].l];
		tr[u].l = v;
		change(tr[u].l, k, val, l, mid);
	}
	else {
		tr[v] = tr[tr[u].r];
		tr[u].r = v;
		change(tr[u].r, k, val, mid + 1, r);
	}
	maintain(u);
}
node query(int u, int L, int R, int val, int l = 1, int r = n)
{
	if (L > R) {
		node res;
		return res;
	}
	if (L <= l && r <= R) return tr[u];
	int mid = l + r >> 1;
	if (L <= mid && mid < R) return merge(query(tr[u].l, L, R, val, l, mid), query(tr[u].r, L, R, val, mid + 1, r));
	else if (L <= mid) return query(tr[u].l, L, R, val, l, mid);
	else return query(tr[u].r, L, R, val, mid + 1, r);
}

int check(int a, int b, int c, int d, int val)
{
	int res = query(root[val], b + 1, c - 1, val).sum;
	res += query(root[val], a, b, val).rsum;
	res += query(root[val], c, d, val).lsum;
	return res;
}

int calc(int a, int b, int c, int d)
{
	int l = 0, r = nums.size() - 1;
	while (l < r) {
		int mid = l + r + 1 >> 1;
		if (check(a, b, c, d, mid) >= 0) l = mid;
		else r = mid - 1;
	}
	return l;
}

int main(void)
{
	ios::sync_with_stdio(0);
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		cin >> A[i];
		nums.emplace_back(A[i]);
	}
	sort(nums.begin(), nums.end());
	nums.erase(unique(nums.begin(), nums.end()), nums.end());
	for (int i = 1; i <= n; ++i) {
		A[i] = lower_bound(nums.begin(), nums.end(), A[i]) - nums.begin();
		Map[A[i]].emplace_back(i);
	}

	root[0] = build(1, n);
	for (int i = 1; i < nums.size(); ++i) {
		root[i] = ++idx;
		tr[idx] = tr[root[i - 1]];
		for (int j : Map[i - 1]) {
			change(root[i], j, -1);
		}
	}

	cin >> m;
	int lastans = 0;
	for (int i = 1; i <= m; ++i) {
		static int tmp[4];
		for (int i = 0; i < 4; ++i) {
			cin >> tmp[i];
			tmp[i] = (tmp[i] + lastans) % n + 1;
		}
		sort(tmp, tmp + 4);
		printf("%d\n", lastans = nums[calc(tmp[0], tmp[1], tmp[2], tmp[3])]);
	}
	return 0;
}
