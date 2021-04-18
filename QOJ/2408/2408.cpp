#include <queue>
#include <cstdio>
#include <bitset>

using namespace std;

#define reg register
#define ll long long
const int N = 210, M = N * N;

int n, m, Q, idx, cnt;
int f[N][N];
int mp[N][N];
int ru[M], head[M], nex[2 * M], to[2 * M];
int gox[] = {0, 1};
int goy[] = {1, 0};
bitset<M> da[M];
queue<int> q;

void topo(void);
void Add_Edge(int st, int ed);

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j) {
			f[i][j] = getchar();
			while (f[i][j] == ' ' || f[i][j] == '\n') f[i][j] = getchar();
			f[i][j] -= '0';
			mp[i][j] = ++idx;
			da[idx][idx] = 1;
		}
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			for (int e = 0; e < 2; ++e) {
				int xx = i + gox[e], yy = j + goy[e];
				if (xx <= 0 || yy <= 0 || xx > n || yy > m || f[xx][yy] == 1) continue;
				Add_Edge(mp[xx][yy], mp[i][j]);
				++ru[mp[i][j]];
			}
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			if (!ru[mp[i][j]]) q.push(mp[i][j]);
	
	topo();
	
	scanf("%d", &Q);
	int x1, x2, y1, y2;
	while (Q--) {
		scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
		if (da[mp[x1][y1]][mp[x2][y2]]) puts("Safe");
		else puts("Dangerous");
	}
	return 0;
}
void Add_Edge(int st, int ed)
{
	nex[++cnt] = head[st];
	head[st] = cnt;
	to[cnt] = ed;
}
void topo(void)
{
	while (q.size()) {
		int tmp = q.front();
		q.pop();
		for (int e = head[tmp]; e; e = nex[e]) {
			int k = to[e];
			--ru[k];
			da[k] |= da[tmp];
			if (!ru[k]) q.push(k);
		}
	}
	return;
}
