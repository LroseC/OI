#include <cctype>
#include <cstdio>

using namespace std;

inline int lowbit(int x) { return x & -x; }

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

int n, m, q;
int a[310][310];
int tr[110][310][310];

void add(int id, int x, int y, int val)
{
	for (int i = x; i <= n; i += lowbit(i))
		for (int j = y; j <= m; j += lowbit(j))
			tr[id][i][j] += val;
}
int query(int id, int x, int y)
{
	int res = 0;
	for (int i = x; i; i -= lowbit(i))
		for (int j = y; j; j -= lowbit(j))
			res += tr[id][i][j];
	return res;
}

int main(void)
{
	cin >> n >> m;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j) {
			cin >> a[i][j];
			add(a[i][j], i, j, 1);
		}
	cin >> q;
	while (q--) {
		int op; cin >> op;
		if (op == 1) {
			int x, y, c;
			cin >> x >> y >> c;
			add(a[x][y], x, y, -1);
			a[x][y] = c;
			add(a[x][y], x, y, 1);
		}
		else {
			int x1, x2, y1, y2, c;
			cin >> x1 >> x2 >> y1 >> y2 >> c;
			printf("%d\n", query(c, x2, y2) - query(c, x1 - 1, y2) - query(c, x2, y1 - 1) + query(c, x1 - 1, y1 - 1));
		}
	}
	return 0;
}
