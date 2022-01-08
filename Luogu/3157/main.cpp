#include <cstdio>
#include <iostream>

using namespace std;

using LL = long long;
const int N = 1e5 + 10;

namespace FHQ
{
	struct node
	{
		int w, key, cnt, sz;
		node *l, *r;
		int size(void)
		{
			return this == NULL ? 0 : this->sz;
		}
	};
	void maintain(node *u)
	{
		u->sz = u->l->size() + u->r->size() + u->cnt;
	}
};

int n, m;
int a[N];
LL ans;
node *Pre[N], *Nex[N];

void addPre(int k, int val)
{
	for (int i = k; i <= n; i += lowbit(i))
		FHQ::insert(Pre[i], val);
}
void addNex(int k, int val)
{
	for (int i = k; i; i -= lowbit(i))
		FHQ::insert(Nex[i], val);
}
LL queryPre(int k, int val)
{
	LL res = 0;
	for (int i = k; i; i -= lowbit(i))
		res += FHQ::queryBigger(tr[i], val);
	return res;
}
LL queryNex(int k, int val)
{
	LL res = 0;
	for (int i = k; i <= n; i += lowbit(i))
		res += FHQ::querySmaller(tr[i], val);
	return res;
}
void add(int k, int val)
{
	addPre(k, val);
	addNex(k, val);
}
LL query(int k)
{
	return queryPre(k - 1, val) + queryNex(k + 1, val);
}

int main(void)
{
	ios::sync_with_stdio(0);
	cin >> n >> m;
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
		add(i, a[i]);
		ans += query(i);
	}
	for (int i = 1; i <= m; ++i) {
		printf("%lld\n", ans);
		int k;
		cin >> k;
		ans -= query(i);
		del(i, a[i]);
	}
	return 0;
}
