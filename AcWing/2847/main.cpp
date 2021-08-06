#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

#define ll long long
const int N = 5e5 + 10;

struct Data
{
	int x, y, z, w, id, k;
	ll res;
	bool operator<(const Data &b) const
	{
		if (x != b.x) return x < b.x;
		if (y != b.y) return y < b.y;
		return z < b.z;
	}
};

int n, m;
Data q[N], t[N];
ll ans[N];

void merge_sort(int l, int r)
{
	if (l == r) return;
	int mid = l + r >> 1;
	merge_sort(l, mid), merge_sort(mid + 1, r);
	int i = l, j = mid + 1, k = l;
	ll sum = 0;
	while (i <= mid && j <= r)
		if (q[i].y <= q[j].y) sum += q[i].w * !q[i].z, t[k++] = q[i++];
		else q[j].res += sum, t[k++] = q[j++];
	while (i <= mid) sum += q[i].w * !q[i].z, t[k++] = q[i++];
	while (j <= r) q[j].res += sum, t[k++] = q[j++];
	for (int i = l; i <= r; ++i) q[i] = t[i];
}

int main(void)
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i) {
		int x, y, w;
		scanf("%d%d%d", &x, &y, &w);
		q[i] = {x, y, 0, w};
	}
	int k = n;
	for (int i = 1; i <= m; ++i) {
		int x1, y1, x2, y2;
		scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
		q[++k] = {x2, y2, 1, 0, i, 1, 0};
		q[++k] = {x1 - 1, y2, 1, 0, i, -1, 0};
		q[++k] = {x2, y1 - 1, 1, 0, i, -1, 0};
		q[++k] = {x1 - 1, y1 - 1, 1, 0, i, 1, 0};
	}
	sort(q + 1, q + 1 + k);
	merge_sort(1, k);
	for (int i = 1; i <= k; ++i)
		if (q[i].z)
			ans[q[i].id] += q[i].res * q[i].k;
	for (int i = 1; i <= m; ++i) printf("%lld\n", ans[i]);

	return 0;
}