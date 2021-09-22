#include <vector>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 2e5 + 10;
typedef pair<int, int> PII;
inline int lowbit(int x) { return x & -x; }

inline int read(void)
{
	int res = 0, f = 1; char ch = getchar();
	while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
	while (isdigit(ch)) { res = res * 10 + ch - '0'; ch = getchar(); }
	return res * f;
}

int n, m;
int f[N];
int tr[N];
int ans = 0;
vector<int> ed[N];
vector<int> tmp[N];

void add(int k, int val)
{
	for (int i = k; i < N; i += lowbit(i)) tr[i] = max(tr[i], val);
}
int query(int k)
{
	int res = 0;
	for (int i = k; i; i -= lowbit(i)) res = max(res, tr[i]);
	return res;
}

int main(void)
{
	ios::sync_with_stdio(0);
	cin >> n >> m;
	for (int i = 1; i <= m; ++i) {
		int a, b;
		cin >> a >> b;
		ed[a].emplace_back(b);
	}
	for (int i = 1; i <= n; ++i) {
		tmp[i].resize(ed[i].size());
		for (int j = 0; j < ed[i].size(); ++j) {
			tmp[i][j] = query(ed[i][j] - 1) + 1;
			ans = max(ans, tmp[i][j]);
		}
		for (int j = 0; j < ed[i].size(); ++j)
			add(ed[i][j], tmp[i][j]);
	}
	cout << ans << endl;
	return 0;
}