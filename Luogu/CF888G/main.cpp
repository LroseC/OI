#include <cctype>
#include <cstdio>
#include <climits>
#include <iostream>
#include <algorithm>

using namespace std;

using LL = long long;
const int N = 2e5 + 10;

LL ans;
int n;
int A[N];
int root, idx;
int ch[N * 31][2], L[N * 31], R[N * 31];

void insert(int &u, int val, int id, int dep)
{
	if (!u) u = ++idx;
	if (dep < 0) return;
	int e = val >> dep & 1;
	if (!L[u]) L[u] = id;
	R[u] = id;
	insert(ch[u][e], val, id, dep - 1);
}
int query(int u, int val, int dep)
{
	if (dep < 0) return 0;
	int e = val >> dep & 1;
	if (ch[u][e]) return query(ch[u][e], val, dep - 1);
	else return query(ch[u][e ^ 1], val, dep - 1) | (1 << dep);
}
void dfs(int u, int dep)
{
	if (ch[u][0] && ch[u][1]) {
		int res = INT_MAX;
		for (int i = L[ch[u][0]]; i <= R[ch[u][0]]; ++i)
			res = min(res, query(ch[u][1], A[i], dep - 1) | (1 << dep)); //!!!
		ans += res;
	}
	if (ch[u][0]) dfs(ch[u][0], dep - 1);
	if (ch[u][1]) dfs(ch[u][1], dep - 1);
}

int main(void)
{
	ios::sync_with_stdio(0);
	cin >> n;
	for (int i = 1; i <= n; ++i) cin >> A[i];
	sort(A + 1, A + 1 + n);
	for (int i = 1; i <= n; ++i) insert(root, A[i], i, 30);
	dfs(root, 30);
	printf("%lld\n", ans);
	return 0;
}
