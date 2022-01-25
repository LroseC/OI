#include <cstdio>
#include <algorithm>

using namespace std;

struct DIII
{
	int a, b, c;
	bool operator<(const DIII &other) const
	{
		return a < other.a;
	}
};

bool vis[10];
int ans[10];
int idx;
DIII res[1000010];

int power10(int x)
{
	int res = 1;
	for (int i = 1; i <= x; ++i)
		res = res * 10;
	return res;
}

void dfs(int id)
{
	if (id == 10) {
		if (ans[3] == ans[1] * 3)
			res[++idx] = {ans[1], ans[2], ans[3]};
		return;
	}
	if (id == 7)
		if (ans[2] != ans[1] * 2)
			return;
	for (int i = 1; i <= 9; ++i)
		if (!vis[i]) {
			vis[i] = 1;
			int numid = (id - 1) / 3 + 1;
			int numcnt = (id - 1) % 3;
			ans[numid] += i * power10(numcnt);
			dfs(id + 1);
			ans[numid] -= i * power10(numcnt);
			vis[i] = 0;
		}
}

int main(void)
{
	dfs(1);
	sort(res + 1, res + 1 + idx);
	for (int i = 1; i <= idx; ++i)
		printf("%d %d %d\n", res[i].a, res[i].b, res[i].c);
	return 0;
}
