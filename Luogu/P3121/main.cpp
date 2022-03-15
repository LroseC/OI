#include <queue>
#include <cstdio>
#include <cstring>

using namespace std;

const int N = 1e5 + 10;

int n;
int len[N];
int stk[N];
char str[N];
char tmp[N];
char ans[N];

int idx, ch[N][26], fail[N], endpos[N];

void insert(int id, char s[])
{
	int u = 0;
	for (int i = 0; s[i]; ++i) {
		if (!ch[u][s[i] - 'a'])
			ch[u][s[i] - 'a'] = ++idx;
		u = ch[u][s[i] - 'a'];
	}
	endpos[u] = id;
}
void build(void)
{
	queue<int> q;
	for (int i = 0; i < 26; ++i)
		if (ch[0][i]) q.emplace(ch[0][i]);
	while (q.size()) {
		int u = q.front(); q.pop();
		for (int i = 0; i < 26; ++i) {
			if (ch[u][i]) {
				fail[ch[u][i]] = ch[fail[u]][i];
				q.emplace(ch[u][i]);
			}
			else
				ch[u][i] = ch[fail[u]][i];
		}
	}
}

int main(void)
{
	scanf("%s", str + 1);
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%s", tmp + 1);
		insert(i, tmp + 1);
		len[i] = strlen(tmp + 1);
	}
	build();
	int u = 1, top = 0;
	for (int i = 1; str[i]; ++i) {
		u = ch[u][str[i] - 'a'];
		stk[++top] = u;
		ans[top] = str[i];
		if (endpos[u]) {
			int id = endpos[u];
			top -= len[id];
			u = stk[top];
		}
	}
	ans[++top] = '\0';
	printf("%s\n", ans + 1);
	return 0;
}
