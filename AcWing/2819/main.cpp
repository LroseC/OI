#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long ll;
const int N = 1e5 + 10;
inline int lowbit(int x) { return x & -x; }

struct Data
{
	int a, t;
	int res;
} q[N], t[N];
int n, m;
int pos[N];
ll ans[N];
int tr[N];

void add(int x, int v)
{
	for (int i = x; i <= n; i += lowbit(i)) tr[i] += v;
}
int query(int x)
{
	int res = 0;
	for (int i = x; i; i -= lowbit(i)) res += tr[i];
	return res;
}

void merge_sort(int l, int r)
{
	if (l == r) return;
	int mid = l + r >> 1;
	merge_sort(l, mid), merge_sort(mid + 1, r);

	int i = mid, j = r;
	while (i >= l && j >= mid + 1)
		if (q[i].a > q[j].a) add(q[i].t, 1), --i;
		else q[j].res += query(q[j].t - 1), --j;
	while (j >= mid + 1) q[j].res += query(q[j].t - 1), --j;
	for (int k = i + 1; k <= mid; ++k) add(q[k].t, -1);

	j = l, i = mid + 1;
	while (j <= mid && i <= r)
		if (q[i].a < q[j].a) add(q[i].t, 1), ++i;
		else q[j].res += query(q[j].t - 1), ++j;
	while (j <= mid) q[j].res += query(q[j].t - 1), ++j;
	for (int k = mid + 1; k < i; ++k) add(q[k].t, -1);

	i = l, j = mid + 1;
	int k = l;
	while (i <= mid && j <= r)
		if (q[i].a < q[j].a) t[k++] = q[i++];
		else t[k++] = q[j++];
	while (i <= mid) t[k++] = q[i++];
	while (j <= r) t[k++] = q[j++];
	for (int i = l; i <= r; ++i) q[i] = t[i];
}


int main(void)
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i) {
		int x; scanf("%d", &x);
		pos[x] = i;
		q[i].a = x;
	}
	for (int i = 1; i <= m; ++i) {
		int x; scanf("%d", &x);
		q[pos[x]].t = n - i + 1;
		pos[x] = -1;
	}
	for (int i = 1, j = m; i <= n; ++i)
		if (pos[i] != -1) {
			q[pos[i]].t = n - (++j) + 1;
			q[pos[i]].a = i;
		}
	
	merge_sort(1, n);
	for (int i = 1; i <= n; ++i) ans[q[i].t] = q[i].res;
	for (int i = 2; i <= n; ++i) ans[i] += ans[i - 1];
	for (int i = n, j = 1; j <= m; --i, ++j) printf("%lld\n", ans[i]);
	return 0;
}