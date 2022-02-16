#include <queue>
#include <vector>
#include <cctype>
#include <cstdio>

using namespace std;

struct FSI
{
	template<typename T>
	FSI& operator>>(T &res)
	{
		res = 0; T f = 1; char ch = getchar();
		while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
		while (isdigit(ch)) { res = res * 10 + ch - '0'; ch = getchar(); }
		res = res * f; return *this;
	}
} read;

const int N = 1e5 + 10;

int n, m;
char str[N];
int stk[N], top;
int pos[N], ans[N];

int idx, ch[N][26], fail[N];
bool failedge[N][26];
bool ed[N];

struct Query
{
	int v, id;
	Query(int _v, int _id) : v(_v), id(_id) {}
};
int dfn[N], dfncnt;
int L[N], R[N];
vector<Query> Q[N];
vector<int> Fail[N];

int nowpos;

namespace BIT
{
	int tr[N];

	inline int lowbit(int x) { return x & -x; }
	void add(int x, int val)
	{
		for (int i = x; i < N; i += lowbit(i))
			tr[i] += val;
	}
	int query(int x)
	{
		int res = 0;
		for (int i = x; i; i -= lowbit(i))
			res += tr[i];
		return res;
	}
	int query(int l, int r)
	{
		return query(r) - query(l - 1);
	}
}

void back(void)
{
	nowpos = stk[--top];
}
void addend(int id)
{
	ed[nowpos] = 1;
	pos[id] = nowpos;
}
void insert(int son)
{
	if (!ch[nowpos][son])
		ch[nowpos][son] = ++idx;
	nowpos = ch[nowpos][son];
	stk[++top] = nowpos;
}

void build(void)
{
	queue<int> q;
	for (int i = 0; i < 26; ++i)
		if (ch[0][i]) {
			q.emplace(ch[0][i]);
		}
	while (q.size()) {
		int u = q.front(); q.pop();
		for (int i = 0; i < 26; ++i) {
			if (ch[u][i]) {
				q.emplace(ch[u][i]);
				fail[ch[u][i]] = ch[fail[u]][i];
			}
			else {
				failedge[u][i] = 1;
				ch[u][i] = ch[fail[u]][i];
			}
		}
	}
	for (int i = 1; i <= idx; ++i)
		Fail[fail[i]].emplace_back(i);
}

void dfs_fail(int u)
{
	dfn[u] = ++dfncnt;
	L[u] = dfncnt;
	for (int v : Fail[u])
		dfs_fail(v);
	R[u] = dfncnt;
}
void calc(int u)
{
	BIT::add(dfn[u], 1);
	if (ed[u])
		for (auto t : Q[u])
			ans[t.id] = BIT::query(L[t.v], R[t.v]);
	for (int i = 0; i < 26; ++i)
		if (ch[u][i] && !failedge[u][i]) calc(ch[u][i]);
	BIT::add(dfn[u], -1);
}

int main(void)
{
	scanf("%s", str + 1);
	for (int i = 1; str[i]; ++i) {
		if (str[i] == 'B' && top)
			back();
		else if (str[i] == 'P')
			addend(++n);
		else
			insert(str[i] - 'a');
	}

	build();

	read >> m;
	for (int i = 1; i <= m; ++i) {
		int u, v; read >> u >> v;
		/*
		   u 出现在 v 结尾
		   <=> fail[fail...[v]] = u;
		   <=> v 在 u 的 fail 子树中
		   所以只需要求出 v 的子串中有多少个在 u 的 fail 子树中
		*/
		Q[pos[v]].emplace_back(pos[u], i);
	}
	dfs_fail(0); //把 fail 树转化为序列
	calc(0); //然后在 trie 树上 dfs 统一处理所有答案
	for (int i = 1; i <= m; ++i)
		printf("%d\n", ans[i]);
	return 0;
}
