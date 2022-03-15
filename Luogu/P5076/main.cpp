#include <cstdio>
#include <climits>
#include <iostream>

using namespace std;

struct node
{
	int x, l, r;
	node (int x, int l, int r) : x(x), l(l), r(r) {}
} nd[10010];

int n;
int idx, root;

void insert(int x)
{
	if (!root) {
		nd[++idx] = node(x, 0, 0);
		root = idx;
		return;
	}
	int p = root;
	int ls = 0;
	while (p) {
		ls = p;
		if (nd[p].x < x) p = nd[p].l;
		else p = nd[p].r;
	}
	if (nd[ls].x < x) nd[ls].l = ++idx;
	else nd[ls].r = ++idx;
	nd[idx] = node(x, 0, 0);
}

int main(void)
{
	cin >> n;
	insert(-INT_MAX);
	insert(INT_MAX);
	while (n--) {
		int op, x; cin >> op >> x;
		if (op == 1) cout << rk(x) << '\n';
		if (op == 2) cout << val(x) << '\n';
		if (op == 3) cout << pre(x) << '\n';
		if (op == 4) cout << nex(x) << '\n';
		if (op == 5) insert(x);
	}
	return 0;
}