#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 1e7;

int n, m;
char str[N], s[110];
struct Node
{
	int len, fa;
	int ch[4];
} node[N << 1];
int last = 1, tot = 1;

int get(char x)
{
	if (x == 'N') return 1;
	if (x == 'E') return 2;
	if (x == 'S') return 3;
	return 0;
}

void extend(int c)
{
	int p = last, np = last = ++tot;
	node[np].len = node[p].len + 1;
	for (; p && !node[p].ch[c]; p = node[p].fa) node[p].ch[c] = np;
	if (!p) node[np].fa = 1;
	else {
		int q = node[p].ch[c];
		if (node[q].len == node[p].len + 1) node[np].fa = q;
		else {
			int nq = ++tot;
			node[nq] = node[q];
			node[nq].len = node[p].len + 1;
			node[q].fa = node[np].fa = nq;
			for (; p && node[p].ch[c] == q; p = node[p].fa) node[p].ch[c] = nq;
		}
	}
}

int Query(char *s)
{
	int len = strlen(s + 1);
	int p = 1, res = 0, i = 1;
	while (node[p].ch[get(s[i])] && i <= len) p = node[p].ch[get(s[i])], ++i, ++res;
	return res;
}

int main(void)
{
	scanf("%d%d", &n, &m);
	scanf("%s", str + 1);
	for (int i = 1; i <= n; ++i) extend(get(str[i]));
	for (int i = 1; i <= m; ++i) {
		scanf("%s", s + 1);
		printf("%d\n", Query(s));
	}
}