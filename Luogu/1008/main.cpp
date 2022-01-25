#include <cstdio>

using namespace std;

bool vis[10];
int ans[10];

void dfs(int id)
{
	if (id == 10) {
		if (ans[3] == ans[1] * 3)
			printf("%d %d %d\n", ans[1], ans[2], ans[3]);
		return;
	}
	if (id == 7)
		if (ans[2] != ans[1] * 2)
			return;

int main(void)
{
	dfs(1);
	return 0;
}
