#include <queue>
#include <cstdio>

using namespace std;

const int N = 3e4 + 10;

int n;
char str[N];

bool vis[N], ed[N], instk[N];
int idx, ch[N][2], fail[N];

void insert(char s[])
{
	int u = 0;
	for (int i = 0; s[i]; ++i) {
		if (!ch[u][s[i] - '0'])
			ch[u][s[i] - '0'] = ++idx;
		u = ch[u][s[i] - '0'];
	}
	ed[u] = 1;
}
void build(void)
{
	queue<int> q;
	for (int i = 0; i < 2; ++i)
		if (ch[0][i]) q.emplace(ch[0][i]);
	while (q.size()) {
		int u = q.front(); q.pop();
		for (int i = 0; i < 2; ++i) {
			if (ch[u][i]) {
				q.emplace(ch[u][i]);
				fail[ch[u][i]] = ch[fail[u]][i];
				ed[ch[u][i]] |= ed[fail[ch[u][i]]];
			}
			else
				ch[u][i] = ch[fail[u]][i];
		}
	}
}
bool calc(int u)
{
	vis[u] = 1;
	instk[u] = 1;
	for (int i = 0; i < 2; ++i) {
		if (!ed[ch[u][i]]) {
			if (instk[ch[u][i]]) return 1;
			else if (!vis[ch[u][i]] && calc(ch[u][i])) return 1;
		}
	}
	instk[u] = 0;
	return 0;
}

int main(void)
{
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%s", str + 1);
		insert(str + 1);
	}
	build();
	puts(calc(0) ? "TAK" : "NIE");
	return 0;
}
