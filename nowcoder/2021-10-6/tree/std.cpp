#include <queue>
#include <vector>
#include <cctype>
#include <cstdio>
#include <algorithm>

using namespace std;

const int N = 1e5 + 10;

inline int read(void)
{
	int res = 0, f = 1; char ch = getchar();
	while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
	while (isdigit(ch)) { res = res * 10 + ch - '0'; ch = getchar(); }
	return res * f;
}
template<typename T>
inline void write(T x, char end = '\n')
{
	static char buf[50]; int p = -1;
	if (x == 0) putchar('0');
	if (x < 0) { putchar('-'); x = -x; }
	while (x) { buf[++p] = x % 10; x /= 10; }
	while (~p) { putchar(buf[p] + '0'); --p; } putchar(end);
}

struct node
{
	int val, dep;
	node *l, *r;
	node() { l = r = NULL; }
	node(int val) : val(val), dep(1), l(NULL), r(NULL) {}
};
inline int Getdep(node *p)
{
	if (p == NULL) return 0;
	return p->dep;
}
inline int Getval(node *p)
{
	if (p == NULL) return 0;
	return p->val;
}
node* merge(node *a, node *b)
{
	if (a == NULL) return b;
	if (b == NULL) return a;
	if (a->val < b->val) swap(a, b);
	a->r = merge(a->r, b);
	if (Getdep(a->r) > Getdep(a->l)) swap(a->l, a->r);
	a->dep = Getdep(a->r) + 1;
	return a;
}
node* emplace(node *p, int val) { return merge(p, new node(val)); }
int top(node *p) { return Getval(p); }
int second(node *p)
{
	if (p == NULL) return 0;
	return max(Getval(p->l), Getval(p->r));
}
node* pop(node *p)
{
	if (p == NULL) return NULL;
	node *t = merge(p->l, p->r);
	delete p;
	return t;
}
void clear(node *p)
{
	if (p == NULL) return;
	clear(p->l);
	clear(p->r);
	delete p;
}
void Print(node *p)
{
	if (p == NULL) return;
	write(p->val);
	Print(p->l); Print(p->r);
}

int n;
vector<int> G[N];

node* dfs(int u, int fa)
{
	node* heap = NULL;
	for (auto v : G[u]) {
		if (v == fa) continue;
		auto t = dfs(v, u);
		heap = merge(heap, t);
	}
	int tmp = 1;
	for (int i = 1; i <= 2; ++i)
		if (heap != NULL) {
			tmp += top(heap); heap = pop(heap);
		}
	heap = emplace(heap, tmp);
	return heap;
}

int main(void)
{
	int T = read();
	while (T--) {
		n = read();
		for (int i = 1; i <= n; ++i) G[i].clear();
		for (int i = 1; i < n; ++i) {
			int u = read(), v = read();
			G[u].emplace_back(v);
			G[v].emplace_back(u);
		}
		auto t = dfs(1, -1);
		write(Getval(t));
	}
	return 0;
}