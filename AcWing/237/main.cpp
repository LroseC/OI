#include <map>
#include <vector>
#include <cstdio>
#include <algorithm>

using namespace std;

#define ll long long
const int N = 1e5 + 10;

struct PII
{
	int x, y;
	int type;
	bool operator<(const PII &b) const
	{
		return type > b.type;
	}
};

int T;
int n, idx;
PII x[N];
int a[N * 2];
int fa[N * 2];
map<int, int> m;

int get(int x)
{
	return x == fa[x] ? x : fa[x] = get(fa[x]);
}
int merge(int x, int y)
{
	fa[get(x)] = get(y);
}

int main()
{
	scanf("%d", &T);
	while (T--) {
		for (int i = 1; i <= N * 2 - 1; ++i) fa[i] = i;
		m.clear();
		idx = 0;

		scanf("%d", &n);
		for (int i = 1; i <= n; ++i) {
			scanf("%d%d%d", &x[i].x, &x[i].y, &x[i].type);
			a[++idx] = x[i].x;
			a[++idx] = x[i].y;
		}
		sort(x + 1, x + 1 + n);
		sort(a + 1, a + 1 + idx);
		idx = unique(a + 1, a + 1 + idx) - a - 1;
		for (int i = 1; i <= idx; ++i) m[a[i]] = i;
		for (int i = 1; i <= n; ++i) {
			x[i].x = m[x[i].x];
			x[i].y = m[x[i].y];
		}
		if (x[n].type) {
			puts("YES");
			continue;
		}
		int i = 1;
		while (x[i].type) {
			merge(x[i].x, x[i].y);
			++i;
		}
		bool flag = 0;
		for (; i <= n; ++i)
			if (get(x[i].x) == get(x[i].y)) {
				flag = 1;
				break;
			}
		puts(flag ? "NO" : "YES");
	}

	return 0;
}
