#include <cctype>
#include <cstdio>
#include <algorithm>

struct FSI
{
	template<typename T>
	FSI& operator>>(T &res)
	{
		res = 0; T f = 1; char ch = getchar();
		while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
		while (isdigit(ch)) { res = res * 10 + (ch - '0') * f; ch = getchar(); }
		return *this;
	}
} read;

using i64 = long long;
using PII = std::pair<int, int>;
const int N = 1e5 + 10;

struct less
{
	bool operator()(const PII &a, const PII &b)
	{
		auto getPlain = [](PII p)
		{
			if (p.first < 0) {
				if (p.second > 0) return 0;
				else return 1;
			}
			else {
				if (p.second < 0) return 2;
				else return 3;
			}
		};
		auto cmpPlain = [](PII a, PII b)
		{ return 1ll * a.first * b.first < 0 || 1ll * a.second * b.second < 0; };
		if (cmpPlain(a, b)) return getPlain(a) < getPlain(b);
		return 1ll * a.second * b.first < 1ll * b.second * a.first;
	}
};
struct leq
{
	bool operator()(const PII &a, const PII &b)
	{
		auto getPlain = [](PII p)
		{
			if (p.first < 0) {
				if (p.second > 0) return 0;
				else return 1;
			}
			else {
				if (p.second < 0) return 2;
				else return 3;
			}
		};
		auto cmpPlain = [](PII a, PII b)
		{ return 1ll * a.first * b.first < 0 || 1ll * a.second * b.second < 0; };
		if (cmpPlain(a, b)) return getPlain(a) < getPlain(b);
		return 1ll * a.second * b.first <= 1ll * b.second * a.first;
	}
};
struct node
{
	PII val;
	int w, size;
	node *l, *r;
} tr[N];
int m, idx, cnt, tot;
node *root = tr;
PII point[N];
bool vis[N];

node* New(PII v)
{
	node *u = tr + ++idx;
	u->val = v;
	u->size = 1;
	u->w = rand();
	u->l = u->r = tr;
	return u;
}
void maintain(node *u)
{ u->size = u->l->size + u->r->size + 1; }
template<typename T>
std::pair<node*, node*> split(node *u, PII v, T cmp)
{
	if (u == tr) return std::make_pair(tr, tr);
	std::pair<node*, node*> t;
	if (cmp(u->val, v)) {
		t = split(u->r, v, cmp);
		u->r = t.first;
		t.first = u;
	}
	else {
		t = split(u->l, v, cmp);
		u->l = t.second;
		t.second = u;
	}
	maintain(u);
	return t;
}
node* merge(node *x, node *y)
{
	if (x == tr) return y;
	if (y == tr) return x;
	if (x->w < y->w) {
		x->r = merge(x->r, y);
		maintain(x);
		return x;
	}
	else {
		y->l = merge(x, y->l);
		maintain(y);
		return y;
	}
}
void insert(PII v)
{
	auto t = split(root, v, less());
	root = merge(t.first, merge(New(v), t.second));
}
void remove(PII v)
{
	auto a = split(root, v, less());
	auto b = split(a.second, v, leq());
	b.first = merge(b.first->l, b.first->r);
	root = merge(a.first, merge(b.first, b.second));
}

int main(void)
{
	tr[0].l = tr[0].r = tr;
	read >> m;
	for (int T = 1; T <= m; ++T) {
		static char str[10];
		scanf("%s", str);
		if (str[0] == 'A') {
			++tot;
			int a, b, c;
			read >> a >> b >> c;
			point[++cnt] = std::make_pair(a, c - b);
			insert(point[cnt]);
		}
		else if (str[0] == 'D') {
			int x;
			read >> x;
			if (!vis[x]) {
				--tot;
				vis[x] = 1;
				remove(point[x]);
			}
		}
		else {
			int k;
			read >> k;
			auto a = split(root, std::make_pair(-1, -k), leq());
			auto b = split(a.second, std::make_pair(1, k), less());
			printf("%d\n", b.first->size);
			root = merge(a.first, merge(b.first, b.second));
		}
	}
	return 0;
}
