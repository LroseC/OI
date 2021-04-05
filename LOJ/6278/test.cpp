#include <cstdio>
#include <cmath>
#include <algorithm>

using namespace std;

const int N = 50010;

int n, len;
int a[N], ap[N], id[N], add[N];

int Query(int, int, int);
void Add(int, int, int);
void Work(int);
int main()
{
    scanf("%d", &n);
    len = sqrt(n);

    for (int i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
        id[i] = (i - 1) / len + 1;
    }
	for (int i = (n - 1) / len + 1; i > 0; --i) Work(i);

    int opt, l, r, c;
    for (int i = 0; i < n; ++i) {
        scanf("%d%d%d%d", &opt, &l, &r, &c);
        if (opt) printf("%d\n", Query(l, r, c * c));
        else Add(l, r, c);
    }

    return 0;
}
void Add(int l, int r, int x)
{
    int lid = id[l], rid = id[r];
    if (lid == rid) {
        for (int i = l; i <= r; ++i) a[i] += x;
        Work(lid);
        return;
    }
    for (int i = l; id[i] == lid; ++i) a[i] += x;
    for (int i = lid + 1; i < rid; ++i) add[i] += x;
    for (int i = r; id[i] == rid; --i) a[i] += x;
    Work(lid);
    Work(rid);
}
void Work(int idx)
{
    int l = (idx - 1) * len + 1, r = idx * len;
    for (int i = l; i <= r; ++i) ap[i] = a[i];
    sort(ap + l, ap + r + 1);
}
int Query(int L, int R, int X)
{
    int lid = id[L], rid = id[R];
	int x = X - add[lid];
    int ans = 0;
    if (lid == rid) {
		for (int i = L; i <= R; ++i)
			if (a[i] < x) ++ans;
		return ans;
    }

	for (int i = L; id[i] == lid; ++i) {
		if (a[i] < x) ++ans;
	}
	for (int i = lid + 1; i < rid; ++i) {
		x = X - add[i];
		int l = (i - 1) * len + 1, r = i * len, mid;
		while (l < r) {
			mid = l + r + 1 >> 1;
			if (ap[mid] < x) l = mid;
			else r = mid - 1;
		}
		ans += l - (i - 1) * len;
	}
	x = X - add[rid];
	for (int i = R; id[i] == rid; --i) {
		if (a[i] < x) ++ans;
	}

	return ans;
}
/*
4
1 2 2 3
0 1 3 1
1 1 3 2
1 1 4 1
1 2 3 2
*/
