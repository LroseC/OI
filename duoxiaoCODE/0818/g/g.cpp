#include <cctype>
#include <cstdio>
#include <cstdint>
#include <cstring>
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

using i32 = int32_t;
using i64 = int64_t;
using PII = std::pair<i32, i32>;

i32 n, m;
i32 G[1110][1110];
i32 color[1110];

bool check(void)
{
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			if (G[i][j] && color[i] == color[j]) return 0;
	return 1;
}
void dfscolor(i32 id)
{
	if (id > n) {
		if (check()) {
			printf("A ");
			for (int i = 1; i <= n; ++i)
				printf("%d ", color[i]);
			puts("");
			exit(0);
		}
		return;
	}
	for (int i = 1; i <= 4; ++i) {
		color[id] = i;
		dfscolor(id + 1);
	}
}
int del2[100], del[100];
int stk[100], top;
i32 getSz(i32 u)
{
	del2[u] = 1;
	i32 sz = 1;
	for (int v = 1; v <= n; ++v)
		if (!del2[v]) {
			sz += getSz(v);
		}
	return sz;
}
void dfscircle(i32 u, i32 cnt)
{
	del[u] = 1;
	stk[++top] = u;
	for (int v = 1; v <= n; ++v) {
		if (!del[v] && G[u][v]) {
			G[u][v] = G[v][u] = 0;
			dfscircle(v, cnt + 1);
			G[u][v] = G[v][u] = 1;
		}
		if (del[v] && G[u][v] && (cnt & 1)) {
			std::memset(del2, 0, sizeof del2);
			if (getSz(1) == n) {
				printf("B %d ", top);
				for (int i = 1; i <= top; ++i)
					printf("%d ", stk[i]);
				puts("");
				exit(0);
			}
		}
	}
	--top;
	del[u] = 0;
}

int main(void)
{
#ifndef DEBUG
	freopen("g.in", "r", stdin);
	freopen("g.out", "w", stdout);
#endif
	//Think twice, code once.
	read >> n >> m;
	for (int i = 1; i <= m; ++i) {
		i32 u, v;
		read >> u >> v;
		G[u][v] = G[v][u] = 1;
	}
	if (n <= 5) {
		dfscolor(1);
		for (int i = 1; i <= n; ++i) {
			dfscircle(i, 1);
		}
	}
	puts("wxh ak ioi2019");
	return 0;
}
