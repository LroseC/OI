#include <queue>
#include <cstdio>
#include <cstring>

using namespace std;

struct PII
{
	int h, x, y;
	bool operator<(const PII &b) const
	{
		return h > b.h;
	}
};

int T;
int r, c, ans;
int f[1010][1010];
bool vis[1010][1010];
int gox[] = {1, -1, 0, 0};
int goy[] = {0, 0, 1, -1};
priority_queue<PII> EMPTY, q;

void Dij(void);

int main()
{
	scanf("%d", &T);
	for (int k = 1; k <= T; ++k) {
		ans = 0;
		scanf("%d%d", &r, &c);
		for (int i = 1; i <= r ; ++i)
			for (int j = 1; j <= c; ++j) scanf("%d", &f[i][j]);
	
		Dij();
	
		printf("Case #%d: %d\n", k, ans);
	}

	return 0;
}

void Dij(void)
{
	q = EMPTY;
	memset(vis, 0, sizeof vis);
	for (int i = 1; i <= r; ++i) {
		q.push({0, i, 1});
		q.push({0, i, c});
	}
	for (int i = 2; i < c; ++i) {
		q.push({0, 1, i});
		q.push({0, r, i});
	}

	while (q.size()) {
		PII now = q.top();
		q.pop();
		if (vis[now.x][now.y]) continue;
		vis[now.x][now.y] = 1;
//		printf("%d,%d:%d\n", now.x, now.y, now.h);
		ans += max(0, now.h - f[now.x][now.y]);
		for (int i = 0; i < 4; ++i) {
			int xx = now.x + gox[i], yy = now.y + goy[i];
			if (vis[xx][yy] || xx <= 0 || yy <= 0 || xx > r || yy > c) continue;
			q.push({max(now.h, f[now.x][now.y]), xx, yy});
		}
	}

	return;
}
