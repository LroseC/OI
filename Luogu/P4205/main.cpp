#include <set>
#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

char blk[12][4][5] =
{
	{
		"**",
		"* "
	},
	{
		"****",
		"    ",
		"    ",
		"    "
	},
	{
		"***",
		"*  ",
		"   "
	},
	{
		"**",
		"**"
	},
	{
		"*  ",
		"*  ",
		"***"
	},
	{
		"****",
		" *  ",
		"    ",
		"    "
	},
	{
		"***",
		"* *",
		"   "
	},
	{
		"***",
		"** ",
		"   "
	},
	{
		"*** ",
		"  **",
		"    ",
		"    "
	},
	{
		" * ",
		"***",
		" * "
	},
	{
		"*  ",
		"** ",
		" **"
	},
	{
		"****",
		"*   ",
		"    ",
		"    "
	}
};

#define x first
#define y second
const int N = 32000;
typedef pair<int, int> PII;

int idx;
int ans[N], top;
int row[N], col[N], s[N];
int u[N], d[N], l[N], r[N];
char G[10][11];
int id[10][10];
bool vis[12];
vector<char> solc;
set<vector<PII>> S;
vector<vector<PII>> sol;

void rev1(char s[4][5]);//水平翻转
void rev2(char s[4][5]);//对角线翻转
vector<PII> get(char s[4][5], int dx, int dy);
bool check(char s[4][5], int dx, int dy, int op);
void init(void);
void add(int &hh, int &tt, int i, int j);
void remove(int p);
void resume(int p);
bool dfs();

int main(void)
{
	for (int i = 0, cnt = 0; i < 10; ++i)
		for (int j = 0; j <= i; ++j)
			id[i][j] = ++cnt;

	for (int i = 0; i < 10; ++i) scanf("%s", G[i]);
	for (int i = 0; i < 10; ++i)
		for (int j = 0; j <= i; ++j) {
			if (G[i][j] != '.')
				vis[G[i][j] - 'A'] = 1;
		}
	init();

	for (int i = 0; i < 12; ++i)
		for (int rv = 0; rv < 2; ++rv) {
			for (int rtt = 0; rtt < 4; ++rtt) {
				for (int dx = -10; dx <= 10; ++dx)
					for (int dy = -10; dy <= 10; ++dy)
						if (check(blk[i], dx, dy, i)) {
							auto t = get(blk[i], dx, dy);
							if (S.count(t)) continue;
							S.insert(t);
							int hh = idx, tt = idx;
							for (auto p : t) {
								add(hh, tt, sol.size(), id[p.x][p.y]);
							}
							add(hh, tt, sol.size(), 56 + i);
							sol.emplace_back(t);
							solc.emplace_back(i + 'A');
						}
				rev1(blk[i]);
				rev2(blk[i]);
			}
			rev1(blk[i]);
		}
	if (dfs()) {
		for (int i = 1; i <= top; ++i) {
			for (auto p : sol[ans[i]])
				G[p.x][p.y] = solc[ans[i]];
		}
		for (int i = 0; i < 10; ++i) puts(G[i]);
	}
	else puts("No solution");
	return 0;
}

void rev1(char s[4][5])
{
	int n = strlen(s[0]);
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n / 2; ++j)
			swap(s[i][j], s[i][n - j - 1]);
}
void rev2(char s[4][5])
{
	int n = strlen(s[0]);
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < i; ++j)
			swap(s[i][j], s[j][i]);
}
vector<PII> get(char s[4][5], int dx, int dy)
{
	vector<PII> res;
	int n = strlen(s[0]);
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			if (s[i][j] == '*')
				res.emplace_back(PII({i + dx, j + dy}));
	return res;
}
bool check(char s[4][5], int dx, int dy, int op)
{
	auto point = get(s, dx, dy);
	for (auto p : point)
		if (p.x < 0 || p.y < 0 || p.x > 9 || p.y > p.x)
			return 0;

	if (!vis[op]) {
		for (auto p : point)
			if (G[p.x][p.y] != '.') {
				return 0;
			}
	}
	else {
		for (auto p : point)
			if (G[p.x][p.y] != 'A' + op) {
				return 0;
			}
	}
	return 1;
}
void init(void)
{
	int m = 55 + 12;
	for (int i = 0; i <= m; ++i) {
		u[i] = d[i] = i;
		l[i] = i - 1; r[i] = i + 1;
	}
	l[0] = m; r[m] = 0;
	idx = m + 1;
}
void add(int &hh, int &tt, int i, int j)
{
	row[idx] = i, col[idx] = j, ++s[j];
	u[idx] = j; d[idx] = d[j];
	d[u[idx]] = idx; u[d[idx]] = idx;
	l[idx] = hh, r[idx] = tt;
	l[r[idx]] = idx; r[l[idx]] = idx;
	tt = idx++;
}
void remove(int p)
{
	r[l[p]] = r[p]; l[r[p]] = l[p];
	for (int i = d[p]; i != p; i = d[i])
		for (int j = l[i]; j != i; j = l[j]) {
			--s[col[j]];
			u[d[j]] = u[j], d[u[j]] = d[j];
		}
}
void resume(int p)
{
	for (int i = u[p]; i != p; i = u[i])
		for (int j = r[i]; j != i; j = r[j]) {
			u[d[j]] = j; d[u[j]] = j;
			++s[col[j]];
		}
	r[l[p]] = p; l[r[p]] = p;
}
bool dfs(void)
{
	if (!r[0]) return 1;
	int p = r[0];
	for (int i = r[0]; i; i = r[i]) {
		if (s[i] < s[p])
			p = i;
	}
	remove(p);
	for (int i = d[p]; i != p; i = d[i]) {
		ans[++top] = row[i];
		for (int j = l[i]; j != i; j = l[j]) remove(col[j]);
		if (dfs()) return 1;
		for (int j = r[i]; j != i; j = r[j]) resume(col[j]);
		--top;
	}
	resume(p);
	return 0;
}