#include <queue>
#include <cstdio>
#include <cstring>

using namespace std;

const int N = 200 * 80;

int n;
int idx, ed[N], fail[N], ch[N][26];
int cnt[160];
char str[(int)1e6 + 10];
char s[160][100];

void initnode(int u)
{
	ed[u] = fail[u] = 0;
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
	ed[u] = id;
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
			if (ed[j]) ++cnt[ed[j]];
		}
	}
}

int main(void)
{
	while (scanf("%d", &n), n) {
		idx = 0;
		initnode(0);
		memset(cnt, 0, (n + 1) * sizeof(int));
		for (int i = 1; i <= n; ++i) {
			scanf("%s", s[i]);
			insert(i, s[i]);
		}
		build();
		scanf("%s", str);
		query(str);
		int maxcnt = 0;
		for (int i = 1; i <= n; ++i) maxcnt = max(maxcnt, cnt[i]);
		printf("%d\n", maxcnt);
		for (int i = 1; i <= n; ++i) {
			if (cnt[i] == maxcnt) printf("%s\n", s[i]);
		}
	}
	return 0;
}