#include <set>
#include <cctype>
#include <cstdio>

using namespace std;

const int N = 3e5 + 10;
inline int lowbit(int x) { return x & -x; }
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;

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
} cin;

template<typename T>
void write(T x)
{
	static char buf[12]; int p = -1;
	if (!x) putchar('0');
	if (x < 0) putchar('-'), x = -x;
	while (x) buf[++p] = x % 10, x /= 10;
	while (~p) putchar(buf[p] + '0'), --p;
	putchar('\n');
}

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

int main(void)
{
	cin >> n >> m;
	for (int i = 0; i <= n + 1; ++i)
		S.insert(i);
	for (int i = 1; i <= n; ++i) {
		do a[i] = getchar();
		while (isspace(a[i]));
		if (a[i] == '1') {
			S.erase(i);
			road[i] = 1;
		}
	}
	for (int i = 1; i <= m; ++i) {
		char op = getchar();
		while (isspace(op))
			op = getchar();
		if (op == 't') {
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
			write(query(u, v) + (v <= right_bound) * i);
		}
	}
	return 0;
}
//7 -> 11, 98 -> 101
/*
   一个奇怪的做法: 不用二维差分, 而是树状数组用差分, 线段树直接区间加即可.
   应该还是能过? 
*/
/*
   过了, 并且卡了个大常, 卡进卡常榜前十, 可喜可贺.
*/
