#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 1e4 + 10;

struct PII
{
	int p, d;
	bool operator<(const PII &b) const
	{
		return p > b.p;
	}
};

int n, ans;
PII a[N];
int fa[N], m[N];

int get(int);
void merge(int, int);

int main()
{
	while(~scanf("%d", &n)) {
		ans = 0;
		memset(a, 0, sizeof a);
		memset(fa, -1, sizeof fa);
		memset(m, 0, sizeof m);

		for (int i = 1; i <= n; ++i) {
			scanf("%d%d", &a[i].p, &a[i].d);
		}
		sort(a + 1, a + 1 + n);
		for (int i = 1; i <= n; ++i) {
			int f = get(a[i].d);
			if (f > 0)
			{
				ans += a[i].p;
				fa[f] = f - 1;
			}
		}
		printf("%d\n", ans);
	}

	return 0;
}
int get(int x)
{
	return ~fa[x] ? fa[x] = get(fa[x]) : x;
}
void merge(int x, int y)
{
	fa[get(x)] = get(y);
}
