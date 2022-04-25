#include <vector>
#include <cctype>
#include <cstdio>
#include <algorithm>

struct FSI
{
	template<typename T>
	FSI& operator>>(T &res)
	{
		res = 0; T f = 1; char ch = getchar();
		while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
		while (isdigit(ch)) { res = res * 10 + (ch - '0') * f; ch = getchar(); }
		return *this;
	}
} read;

using i64 = long long;
const int N = 1e5 + 10;

struct Vector
{
	int x, y;
	Vector(void) {}
	Vector(int _x, int _y) { x = _x, y = _y; }
};
struct node
{
	int max;
};

int n;
std::vector< std::pair<Vector, Vector> > Line;
node tr[N << 2];

bool greaterSlope(int id1, int id2)
{
	Vector p1 = Line[id1].first, p2 = Line[id1].second;
	Vector q1 = Line[id2].first, q2 = Line[id2].second;
	return 1.0 * (p1.y - p2.y) * (q1.x - q2.x) > 1.0 * (q1.y - q2.y) * (p1.x - p2.x);
}
inline double calc(int id, int pos)
{
	Vector l1 = Line[id].first;
	Vector l2 = Line[id].second;
	if (l2.x == l1.x) return std::max(l1.y, l2.y);
	return 1.0 * (l2.y - l1.y) * (pos - l1.x) / (l2.x - l1.x) + l1.y;
}

void add(int L, int R, int id, int u = 1, int l = 1, int r = 40000)
{
	if (L <= l && r <= R) {
		if (l == r) {
			if (calc(id, l) > calc(tr[u].max, l) || !tr[u].max)
				tr[u].max = id;
			return;
		}
		if (!tr[u].max) {
			tr[u].max = id;
			return;
		}
		int mid = l + r >> 1;
		bool flag = calc(id, mid) > calc(tr[u].max, mid);
		if (greaterSlope(id, tr[u].max)) {
			if (flag)
				add(L, R, tr[u].max, u << 1, l, mid);
			else
				add(L, R, id, u << 1 | 1, mid + 1, r);
		}
		else {
			if (flag)
				add(L, R, tr[u].max, u << 1 | 1, mid + 1, r);
			else
				add(L, R, id, u << 1, l, mid);
		}
		if (flag)
			tr[u].max = id;
		return;
	}
	int mid = l + r >> 1;
	if (L <= mid)
		add(L, R, id, u << 1, l, mid);
	if (R > mid)
		add(L, R, id, u << 1 | 1, mid + 1, r);
}
int query(int pos, int u = 1, int l = 1, int r = 40000)
{
	if (l == r)
		return tr[u].max;
	int mid = l + r >> 1;
	if (pos <= mid) {
		int t = query(pos, u << 1, l, mid);
		if (!t || !tr[u].max)
			return t + tr[u].max;
		return calc(t, pos) > calc(tr[u].max, pos) ? t : tr[u].max;
	}
	else {
		int t = query(pos, u << 1 | 1, mid + 1, r);
		if (!t || !tr[u].max)
			return t + tr[u].max;
		return calc(t, pos) > calc(tr[u].max, pos) ? t : tr[u].max;
	}
}

int main(void)
{
	read >> n;
	Line.resize(1);
	for (int i = 1, lastans = 0; i <= n; ++i) {
		int op;
		read >> op;
		if (op == 0) {
			int k;
			read >> k;
			k = (k + lastans - 1) % 39989 + 1;
			printf("%d\n", lastans = query(k));
		}
		else {
			int x0, y0, x1, y1;
			read >> x0 >> y0 >> x1 >> y1;
			x0 = (x0 + lastans - 1) % 39989 + 1;
			x1 = (x1 + lastans - 1) % 39989 + 1;
			y0 = (y0 + lastans - 1) % (int)1e9 + 1;
			y1 = (y1 + lastans - 1) % (int)1e9 + 1;
			if (x0 > x1) {
				std::swap(x0, x1);
				std::swap(y0, y1);
			}
			Line.emplace_back(std::make_pair(Vector(x0, y0), Vector(x1, y1)));
			add(x0, x1, Line.size() - 1);
		}
	}
	return 0;
}
