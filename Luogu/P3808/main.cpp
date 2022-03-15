#include <queue>
#include <cstdio>
#include <cstring>

using namespace std;

const int N = 1e6 + 10;

int n;
int idx;
int ed[N];
int fail[N];
int ch[N][26];
char str[N];

void insert(char str[])
{
	int u = 0;
	for (int i = 0; str[i]; ++i) {
		if (!ch[u][str[i] - 'a'])
			ch[u][str[i] - 'a'] = ++idx;
		u = ch[u][str[i] - 'a'];
	}
	++ed[u];
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
				fail[ch[u][i]] = ch[fail[u]][i];
				q.emplace(ch[u][i]);
			}
		}
	}
}
int query(char str[])
{
	int u = 0, res = 0;
	for (int i = 0; str[i]; ++i) {
		u = ch[u][str[i] - 'a'];
		for (int j = u; j && ~ed[j]; j = fail[j]) {
			res += ed[j];
			ed[j] = -1;
		}
	}
	return res;
}

int main(void)
{
	scanf("%d", &n);
	while (n--) {
		scanf("%s", str);
		insert(str);
	}
	build();
	scanf("%s", str);
	printf("%d\n", query(str));
	return 0;
}