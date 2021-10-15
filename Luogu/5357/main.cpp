#include <queue>
#include <vector>
#include <cstdio>
#include <cstring>

using namespace std;

const int N = 2e5 + 10;

int n;
vector<int> ed[N];
int idx, fail[N], ch[N][26];
int cnt[N];
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
		for (int j = u; j; j = fail[j]) {
			if (ed[j].size())
				for (auto t : ed[j])
					++cnt[t];
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
	int maxcnt = 0;
	for (int i = 1; i <= n; ++i)
		printf("%d\n", cnt[i]);
	return 0;
}