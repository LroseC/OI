#include <cstdio>

using namespace std;

#define reg register
#define ll long long
#define max(a, b) (a > b ? a : b)
#define min(a, b) (a < b ? a : b)
inline void swap(int &a, int &b) {int t = a;a = b;b = t;}
const int N = 2e6 + 10;

struct PII
{
	int sum, lans, rans, ans;
	PII(int a, int b, int c, int d) : sum(a), lans(b), rans(c), ans(d) {}
	PII(void) {}
};

namespace Seg_Tree
{
	int idx;
	int l[N], r[N];
	int ls[N], rs[N];
	int sum[N], ans[N], lans[N], rans[N];

	void Maintain(int x);
	int Build(int l, int r);
	PII Query(int l, int r, int p);
	void Change(int x, int y, int p);
}

int n, m;
int a[N];

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);

	Seg_Tree::Build(1, n);

	int opt, x, y;
	for (int i = 0; i < m; ++i) {
		scanf("%d%d%d", &opt, &x, &y);
		switch(opt) {
			case 1:
				if (x > y) swap(x, y);
				printf("%d\n", Seg_Tree::Query(x, y, 1).ans);
				break;
			case 2:
				Seg_Tree::Change(x, y, 1);
				break;
		}
	}

	return 0;
}
void Seg_Tree::Maintain(int p)
{
	using namespace Seg_Tree;
	sum[p] = sum[ls[p]] + sum[rs[p]];
	lans[p] = max(lans[ls[p]], sum[ls[p]] + lans[rs[p]]);
	rans[p] = max(rans[rs[p]], sum[rs[p]] + rans[ls[p]]);
	ans[p] = max(rans[ls[p]] + lans[rs[p]], max(ans[ls[p]], ans[rs[p]]));
}
int Seg_Tree::Build(int L, int R)
{
	using namespace Seg_Tree;
	int p = ++idx;
	l[p] = L, r[p] = R;
	if (L == R) {
		sum[p] = ans[p] = lans[p] = rans[p] = a[L];
		return p;
	}
	int mid = L + R >> 1;
	ls[p] = Build(L, mid);
	rs[p] = Build(mid + 1, R);
	Maintain(p);
	return p;
}
PII Seg_Tree::Query(int L, int R, int p)
{
	using namespace Seg_Tree;
	int mid = l[p] + r[p] >> 1;
	if (L == l[p] && R == r[p]) return PII(sum[p], lans[p], rans[p], ans[p]);
	if (L > mid) return Query(L, R, rs[p]);
	if (R <= mid) return Query(L, R, ls[p]);
	PII left = Query(L, mid, ls[p]), right = Query(mid + 1, R, rs[p]);
	return PII(left.sum + right.sum, max(left.lans, left.sum + right.lans), max(right.rans, right.sum + left.rans), max(left.rans + right.lans, max(left.ans,right.ans)));
}
void Seg_Tree::Change(int x, int y, int p)
{
	using namespace Seg_Tree;
	if (l[p] == r[p]) {
		sum[p] = ans[p] = lans[p] = rans[p] = y;
		return;
	}
	int mid = l[p] + r[p] >> 1;
	if (x > mid) Change(x, y, rs[p]);
	else Change(x, y, ls[p]);
	Maintain(p);
	return;
}
