#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>

using namespace std;

template<typename Int> inline void read(Int &res)
{
	res = 0; char ch = getchar();
	while (!isdigit(ch)) ch = getchar();
	while (isdigit(ch)) { res = res * 10 + (ch ^ '0'); ch = getchar(); }
}
template<typename Int> inline void write(Int x)
{
	static char buf[20]; int p = -1;
	if (!x) putchar('0');
	if (x < 0) { putchar('-'); x = -x; }
	while (x) { buf[++p] = x % 10 ^ '0'; x /= 10; }
	while (p >= 0) { putchar(buf[p]); --p; }
}

struct Ans
{
	int x, y, dir;
};

int n;
int G[5][7];
bool del[5][7];
int bG[16][5][7];
int cnt[16];
int bcnt[16][16];
Ans ans[16];

void move(void)
{
	int flag = 1;
	while (flag) {
		flag = 0;
		memset(del, 0, sizeof del);
		for (int i = 0; i < 5; ++i) {
			int y = -1;
			for (int j = 0; j < 7; ++j)
				if (G[i][j])
					G[i][++y] = G[i][j];
			while (y < 6) G[i][++y] = 0;
		}
		for (int i = 0; i < 5; ++i)
			for (int j = 1, l = 0, r = 0; j < 7; ++j) {
				if (G[i][j] == G[i][l] && G[i][j]) r = j;
				else l = j;
				if (r - l == 2)
					for (int k = l; k <= r; ++k) del[i][k] = 1;
				else if (r - l > 2) del[i][j] = 1;
			}
		for (int j = 0; j < 7; ++j)
			for (int i = 1, l = 0, r = 0; i < 5; ++i) {
				if (G[i][j] == G[l][j] && G[i][j]) r = i;
				else l = r = i;
				if (r - l == 2)
					for (int k = l; k <= r; ++k) del[k][j] = 1;
				else if (r - l > 2) del[i][j] = 1;
			}
		for (int i = 0; i < 5; ++i)
			for (int j = 0; j < 7; ++j)
				if (del[i][j]) {
					flag = 1;
					--cnt[0];
					--cnt[G[i][j]];
					G[i][j] = 0;
				}
	}
}

bool dfs(int dep)
{
	// printf("dep = %d\n", dep);
	// for (int i = 0; i < 5; ++i, puts(""))
	// 	for (int j = 0; j < 7; ++j) printf("%2d ", G[i][j]);
	if (dep > n && cnt[0] == 0) return 1;
	if (dep > n) return 0;
	if (cnt[0] == 0) return 0;
	for (int i = 1; i <= 10; ++i)
		if (cnt[i] > 0 && cnt[i] < 3) return 0;
	memcpy(bG[dep], G, sizeof G);
	memcpy(bcnt[dep], cnt, sizeof cnt);
	for (int x = 0; x < 5; ++x)
		for (int y = 0; y < 7; ++y) {
			if (!G[x][y]) continue;
			if (x != 4) {
				swap(G[x][y], G[x + 1][y]);
				move();
				ans[dep] = {x, y, 1};
				if (dfs(dep + 1)) return 1;
				memcpy(G, bG[dep], sizeof G);
				memcpy(cnt, bcnt[dep], sizeof cnt);
			}
			if (x && !G[x - 1][y]) {
				swap(G[x][y], G[x - 1][y]);
				move();
				ans[dep] = {x, y, -1};
				if (dfs(dep + 1)) return 1;
				memcpy(G, bG[dep], sizeof G);
				memcpy(cnt, bcnt[dep], sizeof cnt);
			}
		}
	return 0;
}

int main(void)
{
	read(n);
	for (int i = 0; i < 5; ++i) {
		int t, y = 0;
		while (read(t), t) {
			G[i][y] = t;
			++cnt[t];
			++cnt[0];
			++y;
		}
	}
	// move();
	// for (int i = 0; i < 5; ++i, puts(""))
		// for (int j = 0; j < 7; ++j) printf("%2d ", G[i][j]);
	// return 0;
	if (dfs(1)) {
		for (int i = 1; i <= n; ++i) 
			printf("%d %d %d\n", ans[i].x, ans[i].y, ans[i].dir);
	}
	else puts("-1");
	return 0;
}