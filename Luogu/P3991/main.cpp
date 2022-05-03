#include <cctype>
#include <cstdio>
#include <random>
#include <cstring>

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
const int N = 1e5 + 10;

int n, idx;
int root;
struct node
{
	int w, l, r;
	int v[4];
	int a, b, c;
	int cnt;
	i64 sz, f[4][4], of[4][4];
} tr[N << 2];

int New(int a, int b, int c, int x)
{
	++idx;
	tr[idx].w = rand();
	tr[idx].l = tr[idx].r = 0;
	tr[idx].v[0] = tr[idx].v[3] = a;
	tr[idx].v[1] = b, tr[idx].v[2] = c;
	tr[idx].cnt = tr[idx].sz = x;
	std::memset(tr[idx].of, 0xcf, sizeof tr[idx].of);
	for (int i = 0; i < 4; ++i)
		for (int j = i; j < 4; ++j)
			for (int k = i; k <= j; ++k)
				tr[idx].of[i][j] = std::max(tr[idx].of[i][j], 1ll * tr[idx].v[k] * x);
	std::memcpy(tr[idx].f, tr[idx].of, sizeof tr[idx].of);
	return idx;
}
void mergeF(i64 f1[4][4], i64 f2[4][4], i64 ans[4][4])
{
	static i64 f[4][4];
	std::memset(f, 0xcf, sizeof f);
	for (int i = 0; i < 4; ++i)
		for (int j = i; j < 4; ++j)
			for (int k = i; k <= j; ++k)
				f[i][j] = std::max(f[i][j], f1[i][k] + f2[k][j]);
	std::memcpy(ans, f, sizeof f);
}
void maintain(int u)
{
	tr[u].sz = tr[tr[u].l].sz + tr[tr[u].r].sz + tr[u].cnt;

	mergeF(tr[tr[u].l].f, tr[u].of, tr[u].f);
	mergeF(tr[u].f, tr[tr[u].r].f, tr[u].f);
}
int merge(int x, int y)
{
	if (!x || !y) return x + y;
	if (tr[x].w < tr[y].w) {
		tr[x].r = merge(tr[x].r, y);
		maintain(x);
		return x;
	}
	else {
		tr[y].l = merge(x, tr[y].l);
		maintain(y);
		return y;
	}
}
std::pair<int, int> split(int u, int x)
{
	if (!u) return std::make_pair(0, 0);
	if (tr[tr[u].l].sz >= x) {
		auto t = split(tr[u].l, x);
		tr[u].l = t.second;
		maintain(u);
		t.second = u;
		return t;
	}
	else if (tr[tr[u].l].sz + tr[u].cnt > x) {
		int a = New(tr[u].v[0], tr[u].v[1], tr[u].v[2], x - tr[tr[u].l].sz);
		int b = New(tr[u].v[0], tr[u].v[1], tr[u].v[2], tr[u].cnt - tr[a].cnt);
		return std::make_pair(merge(tr[u].l, a), merge(b, tr[u].r));
	}
	else {
		auto t = split(tr[u].r, x - tr[tr[u].l].sz - tr[u].cnt);
		tr[u].r = t.first;
		maintain(u);
		t.first = u;
		return t;
	}
}

int main(void)
{
	srand(time(NULL));
	read >> n;
	i64 last = 0;
	while (n--) {
		int p, a, b, c, x;
		read >> p >> a >> b >> c >> x;
		auto t = split(root, p);
		root = merge(t.first, merge(New(a, b, c, x), t.second));
		printf("%lld\n", tr[root].f[0][3] - last);
		last = tr[root].f[0][3];
	}
	return 0;
}
