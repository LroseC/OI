#include <cctype>
#include <cstdio>
#include <random>

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
} io;

const int N = 1e5 + 10;

int n, m;

namespace FHQ_Treap
{
	struct PII
	{
		int x, y;
		PII(void) : x(0), y(0) {}
		PII(int _x, int _y) : x(_x), y(_y) {}
	};
	int root, idx;
	bool tag[N];
	int ch[N][2];
	int w[N], v[N], sz[N];
	int New(int val)
	{
		++idx; sz[idx] = 1; w[idx] = rand();
		v[idx] = val; ch[idx][0] = ch[idx][1] = 0; return idx;
	}
	void swp(int u)
	{
		if (!u) return;
		tag[u] ^= 1;
		swap(ch[u][0], ch[u][1]);
	}
	void maintain(int u)
	{
		sz[u] = sz[ch[u][0]] + sz[ch[u][1]] + 1;
	}
	void spread(int u)
	{
		if (tag[u]) {
			tag[u] = 0;
			swp(ch[u][0]);
			swp(ch[u][1]);
		}
	}
	void Print(int u = root)
	{
		if (u == 0) return;
		spread(u);
		Print(ch[u][0]);
		printf("%d ", v[u]);
		Print(ch[u][1]);
	}
	int merge(int x, int y)
	{
		spread(x), spread(y);
		if (!x || !y) return x + y;
		if (w[x] > w[y]) {
			ch[x][1] = merge(ch[x][1], y);
			maintain(x);
			return x;
		}
		else {
			ch[y][0] = merge(x, ch[y][0]);
			maintain(y);
			return y;
		}
	}
	PII split(int u, int rk)
	{
		if (!u) return PII(0, 0);
		spread(u);
		if (sz[ch[u][0]] + 1 <= rk) {
			PII t = split(ch[u][1], rk - sz[ch[u][0]] - 1);
			ch[u][1] = t.x;
			maintain(u);
			return PII(u, t.y);
		}
		else {
			PII t = split(ch[u][0], rk);
			ch[u][0] = t.y;
			maintain(u);
			return PII(t.x, u);
		}
	}
	void change(int L, int R)
	{
		PII a = split(root, L - 1);
		PII b = split(a.y, R - L + 1);
		swp(b.x);
		root = merge(a.x, merge(b.x, b.y));
	}
}

int main(void)
{
	io >> n >> m;
	for (int i = 1; i <= n; ++i) {
		int x = i;
		FHQ_Treap::root = FHQ_Treap::merge(FHQ_Treap::root, FHQ_Treap::New(x));
	}
	for (int i = 1; i <= m; ++i) {
		int l, r; io >> l >> r;
		if (l > r) swap(l, r);
		FHQ_Treap::change(l, r);
	}
	FHQ_Treap::Print();
	puts("");
	return 0;
}