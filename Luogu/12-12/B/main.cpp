#include <set>
#include <map>
#include <vector>
#include <cctype>
#include <cstdio>
#include <random>
#include <algorithm>

using namespace std;
using LL = long long;

struct FSI
{
	template<typename T>
	FSI& operator>>(T &res) {
		res = 0; T f = 1; char ch = getchar();
		while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
		while (isdigit(ch)) { res = res * 10 + ch - '0'; ch = getchar(); }
		res = res * f; return *this;
	}
} io;

const int N = 1e5 + 10;
using PII = pair<int, int>;

int n, m;
int a[N];

multiset<int> S1;
set<int> S2;
long long ans = 0;

int main(void)
{
	io >> n;
	for (int i = 1; i <= n; ++i) io >> a[i];
	for (int i = 1; i < n; ++i)
		for (int j = i + 1; j <= n; ++j) {
			if (a[j] < a[i]) {
				S1.insert(make_pair(a[i], a[j]));
				S2.insert(make_pair(a[i], a[j]));
			}
		}
	printf("%ld\n", S2.size());
	io >> m;
	while (m--) {
		int x, y; io >> x >> y;
		for (int i = 1; i < x; ++i) {
			if (a[i] > a[x]) {
				PII res = make_pair(a[i], a[x]);
				auto it = S1.find(res);
				S1.erase(it);
				if (!S1.count())
			}
		}
	}
	return 0;
}
/*
namespace FHQ
{
	struct PII
	{
		int x, y;
		PII(void) { x = y = 0; }
		PII(int _x, int _y) : x(_x), y(_y) {}
	};
	const int SIZE = N * 50;
	int idx;
	int stk[N], top;
	int ch[SIZE][2];
	int w[SIZE], v[SIZE], sz[SIZE], cnt[SIZE];
	int New(int val)
	{
		int id;
		if (top) id = stk[top--];
		else id = ++idx;
		w[id] = rand(); v[id] = val;
		sz[id] = cnt[id] = 1;
		ch[id][0] = ch[id][1] = 0;
		return id;
	}
	void maintain(int u) { sz[u] = sz[ch[u][0]] + cnt[u] + sz[ch[u][1]]; }
	PII split(int x, int val)
	{
		PII res;
		if (!x) return res;
		if (v[x] <= val) {
			res = split(ch[x][1], val);
			ch[x][1] = res.x;
			res.x = x;
		}
		else {
			res = split(ch[x][0], val);
			ch[x][0] = res.y;
			res.y = x;
		}
		maintain(x);
		return res;
	}
	int merge(int x, int y)
	{
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
	void insert(int &root, int val)
	{
		auto a = split(root, val - 1);
		auto b = split(a.y, val);
		if (b.x) ++cnt[b.x];
		else b.x = New(val);
		root = merge(a.x, merge(b.x, b.y));
	}
	void del(int &root, int val)
	{
		auto a = split(root, val - 1);
		auto b = split(a.y, val);
		if (cnt[b.x] == 1) {
			stk[++top] = b.x;
			b.x = 0;
		}
		else --cnt[b.x];
		root = merge(a.x, merge(b.x, b.y));
	}
	int le(int &root, int val)
	{
		auto t = split(root, val - 1);
		int tmp = sz[t.x];
		root = merge(t.x, t.y);
		return tmp;
	}
	int re(int &root, int val)
	{
		auto t = split(root, val);
		int tmp = sz[t.y];
		root = merge(t.x, t.y);
		return tmp;
	}
}

LL ans;
int n, m;
int A[N], B[N];
int tr[N << 2];
vector<int> nums;
map< int, set<int> > S;

void build(int u = 1, int l = 1, int r = n)
{
	for (int i = l; i <= r; ++i) FHQ::insert(tr[u], A[i]);
	if (l == r) return;
	int mid = l + r >> 1;
	build(u << 1, l, mid);
	build(u << 1 | 1, mid + 1, r);
}
void del(int x, int u = 1, int l = 1, int r = n)
{
	FHQ::del(tr[u], A[x]);
	if (l == r) return;
	int mid = l + r >> 1;
	if (x <= mid) del(x, u << 1, l, mid);
	else del(x, u << 1 | 1, mid + 1, r);
}
void add(int x, int u = 1, int l = 1, int r = n)
{
	FHQ::insert(tr[u], A[x]);
	if (l == r) return;
	int mid = l + r >> 1;
	if (x <= mid) add(x, u << 1, l, mid);
	else add(x, u << 1 | 1, mid + 1, r);
}
int queryle(int L, int R, int val, int u = 1, int l = 1, int r = n)
{
	if (L <= l && r <= R) {
		return FHQ::le(tr[u], val);
	}
	int res = 0;
	int mid = l + r >> 1;
	if (L <= mid) res += queryle(L, R, val, u << 1, l, mid);
	if (R > mid) res += queryle(L, R, val, u << 1 | 1, mid + 1, r);
	return res;
}
int queryre(int L, int R, int val, int u = 1, int l = 1, int r = n)
{
	if (L <= l && r <= R) {
		return FHQ::re(tr[u], val);
	}
	int res = 0;
	int mid = l + r >> 1;
	if (L <= mid) res += queryre(L, R, val, u << 1, l, mid);
	if (R > mid) res += queryre(L, R, val, u << 1 | 1, mid + 1, r);
	return res;
}

int get(int x)
{
	auto &_S = S[A[x]];
	auto it = _S.find(x);
	auto jt = it; ++jt;
	LL res = 0;
	if (it == _S.begin() && jt == _S.end()) {
		if (x == 2) puts("???");
		return queryle(x, n, A[x]) + queryre(1, x, A[x]);
	}
	else if (it == _S.begin()) {
		if (x == 2) puts("...");
		return queryle(x, *jt, A[x]);
	}
	else if (jt == _S.end()) {
		if (x == 2) puts("!!!");
		jt = it; --jt;
		return queryre(*jt, x, A[x]);
	}
	return 0;
}

int main(void)
{
	io >> n;
	for (int i = 1; i <= n; ++i) {
		io >> A[i];
		B[i] = A[i];
		S[A[i]].insert(i);
		nums.emplace_back(A[i]);
	}

	sort(nums.begin(), nums.end());
	nums.erase(unique(nums.begin(), nums.end()), nums.end());
	for (int i = 1; i <= n; ++i)
		B[i] = lower_bound(nums.begin(), nums.end(), B[i]) - nums.begin() + 1;

	build();
	for (int i = 1; i <= n; ++i) {
		int tmp = get(i);
		printf("get(%d) = %d\n", i, tmp);
		ans += tmp;
	}
	io >> m;
	printf("%lld\n", ans);
	while (m--) {
		int x, y; io >> x >> y;
		del(x);
		ans -= get(x);
		S[A[x]].erase(x);
		A[x] = y;
		S[A[x]].insert(x);
		ans += get(x);
		add(x);
		printf("%lld\n", ans);
	}
	return 0;
}
*/