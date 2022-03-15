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
} read;

const int N = 510, M = 6e4 + 10;
using LL = long long;
struct Change
{
	int x, y, val;
	Change(void) { x = y = val = 0; }
	Change(int _x, int _y, int _val) : x(_x), y(_y), val(_val) {}
};
struct Query
{
	int x1, y1, x2, y2, k, id;
	Query(void) { x1 = y1 = x2 = y2 = k = 0; }
	Query(int _x1, int _y1, int _x2, int _y2, int _k, int _id) : x1(_x1), y1(_y1), x2(_x2), y2(_y2), k(_k), id(_id) {}
};

int n, m;
int cgcnt;
Change change[N * N], cgt[N * N];
Query q[M], qt[M];
int ans[M];
int tr[N][N];

inline int lowbit(int x) { return x & -x; }
void insert(int x, int y)
{
	for (int i = x; i <= n; i += lowbit(i))
		for (int j = y; j <= n; j += lowbit(j))
			++tr[i][j];
}
void remove(int x, int y)
{
	for (int i = x; i <= n; i += lowbit(i))
		for (int j = y; j <= n; j += lowbit(j))
			--tr[i][j];
}
int query(int x, int y)
{
	int res = 0;
	for (int i = x; i; i -= lowbit(i))
		for (int j = y; j; j -= lowbit(j))
			res += tr[i][j];
	return res;
}
void calc(int CL, int CR, int L, int R, int l, int r)
{
	if (L > R) return;
	if (l == r) {
		for (int i = L; i <= R; ++i)
			ans[q[i].id] = l;
		return;
	}
	int mid = l + r >> 1;
	int cleft = CL, cright = CR;
	for (int i = CL; i <= CR; ++i) {
		if (change[i].val <= mid) {
			cgt[cleft++] = change[i];
			insert(change[i].x, change[i].y);
		}
		else cgt[cright--] = change[i];
	}
	for (int i = CL; i <= CR; ++i) change[i] = cgt[i];

	int left = L, right = R;
	for (int i = L; i <= R; ++i) {
		int x1 = q[i].x1, y1 = q[i].y1, x2 = q[i].x2, y2 = q[i].y2;
		int tmp = query(x2, y2) - query(x1 - 1, y2) - query(x2, y1 - 1) + query(x1 - 1, y1 - 1);
		if (q[i].k <= tmp)
			qt[left++] = q[i];
		else
			q[i].k -= tmp, qt[right--] = q[i];
	}
	for (int i = L; i <= R; ++i) q[i] = qt[i];
	for (int i = CL; i <= CR; ++i)
		if (change[i].val <= mid)
			remove(change[i].x, change[i].y);
	calc(CL, cright, L, right, l, mid);
	calc(cleft, CR, left, R, mid + 1, r);
}

int main(void)
{
	read >> n >> m;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j) {
			int x; read >> x;
			change[++cgcnt] = Change(i, j, x);
		}
	for (int i = 1; i <= m; ++i) {
		int x1, y1, x2, y2, k;
		read >> x1 >> y1 >> x2 >> y2 >> k;
		q[i] = Query(x1, y1, x2, y2, k, i);
	}
	calc(1, n * n, 1, m, 1, (int)1e9);
	for (int i = 1; i <= m; ++i)
		printf("%d\n", ans[i]);
	return 0;
}
