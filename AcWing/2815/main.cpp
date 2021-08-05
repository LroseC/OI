#include <cstdio>
#include <climits>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 1e5 + 10, M = 2e5 + 10;
inline int lowbit(int x) { return x & -x; }

struct Data
{
	int a, b, c, cnt, res;
	bool operator<(const Data &y) const
	{
		if (a != y.a) return a < y.a;
		if (b != y.b) return b < y.b;
		return c < y.c;
	}
	bool operator==(const Data &y) const
	{
		return a == y.a && b == y.b && c == y.c;
	}
	void print(void)
	{
		printf("a = %d, b = %d, c = %d, cnt = %d, res = %d\n", a, b, c, cnt, res);
	}
} a[N], t[N];
int n, m;
int ans[N];
int tr[M];

void add(int x, int v)
{
	for (int i = x; i <= m; i += lowbit(i)) tr[i] += v;
}
int sum(int x)
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
	int i = l, j = mid + 1, k = l;
	while (i <= mid && j <= r) {
		if (a[i].b <= a[j].b) add(a[i].c, a[i].cnt), t[k++] = a[i++];
		else a[j].res += sum(a[j].c), t[k++] = a[j++];
	}
	while (i <= mid) add(a[i].c, a[i].cnt), t[k++] = a[i++];
	while (j <= r) a[j].res += sum(a[j].c), t[k++] = a[j++];
	for (int i = l; i <= mid; ++i) add(a[i].c, -a[i].cnt);
	for (int i = l; i <= r; ++i) a[i] = t[i];
}

int main(void)
{
	scanf("%d%d" ,&n, &m);
	for (int i = 1; i <= n; ++i) {
		int x, y, z;
		scanf("%d%d%d", &x, &y, &z);
		a[i] = {x, y, z, 1, 0};
	}
	sort(a + 1, a + 1 + n);
	int k = 1;
	for (int i = 2; i <= n; ++i) {
		if (a[i] == a[k]) ++a[k].cnt;
		else a[++k] = a[i];
	}
	merge_sort(1, k);
	for (int i = 1; i <= k; ++i) {
		ans[a[i].res + a[i].cnt - 1] += a[i].cnt;
		// printf("WTF = %d\n", a[i].res + a[i].cnt - 1);
	}
	for (int i = 0; i < n; ++i) printf("%d\n", ans[i]);

	return 0;
}