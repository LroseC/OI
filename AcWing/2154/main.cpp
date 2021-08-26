#include <vector>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 1e6 + 10;

int n, m, ans;
int color[N], sz[N], p[N];
vector<int> element[N];

void merge(int &x, int &y)
{
	if (x == y) return;
	if (sz[x] > sz[y]) swap(x, y);
	for (auto a : element[x]) {
		if (color[a - 1] == y) --ans;
		if (color[a + 1] == y) --ans;
	}
	for (auto a : element[x]) {
		color[a] = y;
		element[y].emplace_back(a);
	}
	sz[y] += sz[x];
	element[x].clear();
}

int main(void)
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &color[i]);
		if (color[i] != color[i - 1]) ++ans;
		++sz[i];
		element[color[i]].emplace_back(i);
	}
	for (int i = 0; i < N; ++i) p[i] = i;
	while (m--) {
		int op, x, y;
		scanf("%d", &op);
		if (op == 1) {
			scanf("%d%d", &x, &y);
			merge(p[x], p[y]);
		}
		else printf("%d\n", ans);
	}
	return 0;
}