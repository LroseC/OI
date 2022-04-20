#include <queue>
#include <vector>
#include <cctype>
#include <cstdio>
#include <cstring>
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
const int N = 2e5 + 10, LG = 20;

int n, m, na, nb, idx;
int a[N], root;
int la[N], ra[N], lb[N], rb[N];
int lena[N], lenb[N];
int lg2[N], st[N][LG];
char str[N];
int sa[N], rk[N], x[N], y[N], c[N], height[N];
int segCnt;
int id[N << 5], inEdge[N << 5];
int ch[N << 5][2];
std::vector<int> G[N << 5];
i64 f[N << 5];

void buildSA(void)
{
	int m = 1000;
	for (int i = 1; i <= n; ++i) ++c[x[i] = str[i]];
	for (int i = 1; i <= m; ++i) c[i] += c[i - 1];
	for (int i = n; i >= 1; --i) sa[c[x[i]]--] = i;
	for (int i = 1; i <= m; ++i) c[i] = 0;

	for (int k = 1; k <= n; k <<= 1) {
		int num = 0;
		for (int i = n - k + 1; i <= n; ++i) y[++num] = i;
		for (int i = 1; i <= n; ++i)
			if (sa[i] - k >= 1) y[++num] = sa[i] - k;

		for (int i = 1; i <= n; ++i) ++c[x[i]];
		for (int i = 1; i <= m; ++i) c[i] += c[i - 1];
		for (int i = n; i >= 1; --i) sa[c[x[y[i]]]--] = y[i], y[i] = 0;
		for (int i = 1; i <= m; ++i) c[i] = 0;
		std::swap(x, y);
		num = 0;
		x[sa[1]] = ++num;
		for (int i = 2; i <= n; ++i) {
			int a = sa[i] + k > n ? 0 : y[sa[i] + k];
			int b = sa[i - 1] + k > n ? 0 : y[sa[i - 1] + k];
			x[sa[i]] = (y[sa[i]] == y[sa[i - 1]] && a == b) ? num : ++num;
		}
		if (num == n) break;
	}
	for (int i = 1; i <= n; ++i)
		rk[sa[i]] = i;
	for (int i = 1, k = 0; i <= n; ++i) {
		if (k) --k;
		if (rk[i] == 1) continue;
		int j = sa[rk[i] - 1];
		while (i + k <= n && j + k <= n && str[i + k] == str[j + k])
			++k;
		height[rk[i]] = k;
	}
}
void buildST(void)
{
	for (int i = 2; i <= n; ++i)
		lg2[i] = lg2[i >> 1] + 1;

	for (int i = 1; i <= n; ++i)
		st[i][0] = height[i];
	for (int k = 1; k < LG; ++k)
		for (int i = 1; i + (1 << k - 1) <= n; ++i)
			st[i][k] = std::min(st[i][k - 1], st[i + (1 << k - 1)][k - 1]);
}
int queryST(int l, int r)
{
	int t = lg2[r - l + 1];
	return std::min(st[l][t], st[r - (1 << t) + 1][t]);
}
void buildSeg(int u = 1, int l = 1, int r = n)
{
	segCnt = std::max(segCnt, u);
	id[u] = ++idx;
	ch[u][0] = ch[u][1] = 0;
	inEdge[id[u]] = 0;
	G[id[u]].clear();
	if (l == r)
		return;
	int mid = l + r >> 1;
	ch[u][0] = u << 1, ch[u][1] = u << 1 | 1;
	buildSeg(u << 1, l, mid);
	buildSeg(u << 1 | 1, mid + 1, r);
	G[id[u]].emplace_back(id[u << 1]);
	G[id[u]].emplace_back(id[u << 1 | 1]);
	printf("%d->%d\n", id[u], id[u << 1]);
	printf("%d->%d\n", id[u], id[u << 1 | 1]);
	inEdge[id[u << 1]] = inEdge[id[u << 1 | 1]] = 1;
}
int add(int pos, int v, int rt, int l = 1, int r = n)
{
	int u = ++segCnt;
	id[u] = ++idx;
	ch[u][0] = ch[rt][0];
	ch[u][1] = ch[rt][1];
	G[id[u]].emplace_back(id[rt]);
	++inEdge[id[rt]];
	if (l == r) {
		G[id[u]].emplace_back(v);
		++inEdge[v];
		return u;
	}
	int mid = l + r >> 1;
	if (pos <= mid)
		ch[u][0] = add(pos, v, ch[u][0], l, mid);
	else
		ch[u][1] = add(pos, v, ch[u][1], mid + 1, r);
	return u;
}
void query(int st, int L, int R, int u, int l = 1, int r = n)
{
	if (L <= l && r <= R) {
		G[st].emplace_back(id[u]);
//		printf("%d->%d\n", st, id[u]);
		++inEdge[id[u]];
		return;
	}
	int mid = l + r >> 1;
	if (L <= mid)
		query(st, L, R, ch[u][0], l, mid);
	if (R > mid)
		query(st, L, R, ch[u][1], mid + 1, r);
}
i64 toposort(void)
{
	i64 res = 0;
	int cnt = 0;
	std::queue<int> q;
	for (int i = 1; i <= idx; ++i) {
		if (i <= na) f[i] = lena[i];
		else f[i] = 0;
		res = std::max(res, f[i]);
		if (inEdge[i] == 0)
			q.emplace(i);
	}
	while (q.size()) {
		int u = q.front(); q.pop();
		++cnt;
		for (int v : G[u]) {
			--inEdge[v];
			f[v] = std::max(f[v], f[u] + (v <= na ? lena[v] : 0));
			res = std::max(res, f[v]);
			if (!inEdge[v])
				q.emplace(v);
		}
	}
	return cnt != idx ? -1 : res;
}

int main(void)
{
	int T; read >> T;
	while (T--) {
		scanf("%s", str + 1);
		n = strlen(str + 1);
		buildSA();
		buildST();
		read >> na;
		for (int i = 1; i <= na; ++i) {
			a[i] = i;
			read >> la[i] >> ra[i];
			lena[i] = ra[i] - la[i] + 1;
		}
		idx = na;
		auto cmpa = [](int a, int b) { return lena[a] > lena[b]; };
		std::sort(a + 1, a + 1 + na, cmpa);
		read >> nb;
		for (int i = 1; i <= nb; ++i) {
			read >> lb[i] >> rb[i];
			lenb[i] = rb[i] - lb[i] + 1;
		}
		read >> m;
		std::vector<PII> control;
		for (int i = 1, x, y; i <= m; ++i) {
			read >> x >> y;
			control.emplace_back(x, y);
		}
		auto cmpb = [](PII a, PII b) { return lenb[a.second] > lenb[b.second]; };
		std::sort(control.begin(), control.end(), cmpb);
		int pos = 1;
		buildSeg();
		root = 1;
		for (auto t : control) {
			while (pos <= lena[a[pos]] && lena[a[pos]] >= lenb[t.second]) {
				root = add(rk[la[a[pos]]], a[pos], root);
//				printf("add(%d, %d)\n", rk[la[a[pos]]], a[pos]);
				++pos;
			}

			int l = 1, r = rk[lb[t.second]], mid;
			while (l < r) {
				int mid = l + r >> 1;
				if (queryST(mid + 1, rk[lb[t.second]]) >= lenb[t.second])
					r = mid;
				else
					l = mid + 1;
			}
			int left = l;
			l = rk[lb[t.second]], r = n;
			while (l < r) {
				int mid = l + r + 1 >> 1;
				if (queryST(rk[lb[t.second]] + 1, mid) >= lenb[t.second])
					l = mid;
				else
					r = mid - 1;
			}
			int right = l;

//			printf("%d->(%d, %d), len = %d\n", t.first, left, right, lenb[t.second]);
			query(t.first, left, right, root);
		}
		printf("%lld\n", toposort());
		for (int i = 1; i <= idx; ++i) {
			G[i].clear();
			inEdge[i] = 0;
		}
	}
	return 0;
}
