#include <queue>
#include <vector>
#include <cstdio>
#include <cstring>

using namespace std;

const int N = 2e5 + 10;

int n;
vector<int> invG[N];
int inedge[N];
vector<int> ed[N];
int idx, fail[N], ch[N][26];
int cnt[N];
int ans[N];
char str[(int)2e6 + 10];

void initnode(int u)
{
	fail[u] = 0;
	ed[u].clear();
	for (int i = 0; i < 26; ++i)
		ch[u][i] = 0;
}
void insert(int id, char str[])
{
	int u = 0;
	for (int i = 0; str[i]; ++i) {
		if (!ch[u][str[i] - 'a']) {
			initnode(++idx);
			ch[u][str[i] - 'a'] = idx;
		}
		u = ch[u][str[i] - 'a'];
	}
	ed[u].emplace_back(id);
}
void build(void)
{
	static queue<int> q;
	while (q.size()) q.pop();
	for (int i = 0; i < 26; ++i)
		if (ch[0][i]) q.emplace(ch[0][i]);
	while (q.size()) {
		int u = q.front(); q.pop();
		for (int i = 0; i < 26; ++i) {
			if (!ch[u][i]) ch[u][i] = ch[fail[u]][i];
			else {
				q.emplace(ch[u][i]);
				fail[ch[u][i]] = ch[fail[u]][i];
			}
		}
	}
}
void query(char str[])
{
	int u = 0;
	for (int i = 0; str[i]; ++i) {
		u = ch[u][str[i] - 'a'];
		++cnt[u];
		// for (int j = u; j; j = fail[j])
		// 	++cnt[j];
	}
}
void toposort(void)
{
	static queue<int> q;
	while (q.size()) q.pop();
	for (int i = 0; i <= idx; ++i) {
		++inedge[fail[i]];
		invG[i].emplace_back(fail[i]);
	}
	for (int i = 1; i <= idx; ++i) {
		if (inedge[i] == 0) q.emplace(i);
	}
	while (q.size()) {
		int u = q.front(); q.pop();
		for (auto v : invG[u]) {
			--inedge[v];
			cnt[v] += cnt[u];
			if (inedge[v] == 0) q.emplace(v);
		}
	}
}

int main(void)
{
	scanf("%d", &n);
	idx = 0;
	initnode(0);
	memset(cnt, 0, (n + 1) * sizeof(int));
	for (int i = 1; i <= n; ++i) {
		scanf("%s", str);
		insert(i, str);
	}
	build();
	scanf("%s", str);
	query(str);
	toposort();
	for (int i = 1; i <= idx; ++i)
		for (auto x : ed[i])
			ans[x] = cnt[i];
	for (int i = 1; i <= n; ++i)
		printf("%d\n", ans[i]);
	return 0;
}