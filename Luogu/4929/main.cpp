#include <cstdio>

using namespace std;

const int N = 510, M = N * N;

int n, m, idx;
int row[M], col[M];
int s[N];
int u[M], d[M], l[M], r[M];
int ans[N], top;

void Init(void)
{
	for (int i = 0; i <= m; ++i) {
		u[i] = d[i] = i;
		l[i] = i - 1; r[i] = i + 1;
	}
	l[0] = m; r[m] = 0;
	idx = m + 1;
}
void Add(int &hh, int &tt, int i, int j)
{
	row[idx] = i; col[idx] = j; ++s[j];
	u[idx] = j; d[idx] = d[j];
	u[d[idx]] = idx; d[u[idx]] = idx;
	l[idx] = hh; r[idx] = tt;
	r[l[idx]] = idx; l[r[idx]] = idx;
	tt = idx++;
}
void remove(int p)
{
	r[l[p]] = r[p]; l[r[p]] = l[p];
	for (int i = d[p]; i != p; i = d[i])
		for (int j = r[i]; j != i; j = r[j]) {
			u[d[j]] = u[j]; d[u[j]] = d[j];
			--s[col[j]];
		}
}
void resume(int p)
{
	for (int i = u[p]; i != p; i = u[i])
		for (int j = l[i]; j != i; j = l[j]) {
			++s[col[j]];
			d[u[j]] = j; u[d[j]] = j;
		}
	r[l[p]] = p, l[r[p]] = p;
}

bool dfs(void)
{
	if (!r[0]) return 1;
	int p = r[0];
	for (int i = r[0]; i; i = r[i])
		if (s[i] < s[p])
			p = i;
	remove(p);
	for (int i = d[p]; i != p; i = d[i]) {
		ans[++top] = row[i];
		for (int j = r[i]; j != i; j = r[j]) remove(col[j]);
		if (dfs()) return 1;
		for (int j = l[i]; j != i; j = l[j]) resume(col[j]);
		--top;
	}
	resume(p);
	return 0;
}

int main(void)
{
	scanf("%d%d", &n, &m);
	Init();
	for (int i = 1; i <= n; ++i) {
		int hh = idx, tt = idx;
		for (int j = 1; j <= m; ++j) {
			int x; scanf("%d", &x);
			if (x) Add(hh, tt, i, j);
		}
	}
	top = 0;
	if (dfs())
		for (int i = 1; i <= top; ++i)
			printf("%d ", ans[i]);
	else puts("No Solution!");
	return 0;
}