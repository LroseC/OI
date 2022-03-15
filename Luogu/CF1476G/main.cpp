#include <vector>
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
		while (isdigit(ch)) { res = res * 10 + ch - '0'; ch = getchar(); }
		res = res * f; return *this;
	}
} read;

const int N = 1e5 + 10, B = 2154;

struct Query
{
	int id, t, l, r, k;
	bool operator<(const Query &other) const
	{
		if (l / B != other.l / B) return l < other.l;
		if (r / B != other.r / B) return r < other.r;
		return t < other.t;
	}
};

int n, m;
int a[N];
int cnt[N], ccnt[N], tpos[N], tcg[N];
int pre[N], nex[N];
int ans[N];

void add(int u)
{
	if (u == 0) return;
	nex[u] = nex[0];
	pre[u] = 0;
	pre[nex[u]] = nex[pre[u]] = u;
}
void del(int u)
{
	if (u == 0) return;
	pre[nex[u]] = pre[u];
	nex[pre[u]] = nex[u];
}
void Add(int pos)
{
	if (cnt[a[pos]])
		--ccnt[cnt[a[pos]]];
	if (ccnt[cnt[a[pos]]] == 0)
		del(cnt[a[pos]]);
	++cnt[a[pos]];
	if (ccnt[cnt[a[pos]]] == 0)
		add(cnt[a[pos]]);
	++ccnt[cnt[a[pos]]];
}
void Dec(int pos)
{
	--ccnt[cnt[a[pos]]];
	if (ccnt[cnt[a[pos]]] == 0)
		del(cnt[a[pos]]);
	--cnt[a[pos]];
	if (ccnt[cnt[a[pos]]] == 0)
		add(cnt[a[pos]]);
	if (cnt[a[pos]])
		++ccnt[cnt[a[pos]]];
}
int calc(int K)
{
	std::vector<int> tmp;
	for (int u = nex[0]; u; u = nex[u])
		tmp.emplace_back(u);
	std::sort(tmp.begin(), tmp.end());
	int i = 0, j = -1;
	int res = 0x3f3f3f3f, mycnt = 0;
	while (i < tmp.size()) {
		while (j + 1 < tmp.size() && mycnt < K)
			++j, mycnt += ccnt[tmp[j]];
		if (mycnt >= K)
			res = std::min(res, tmp[j] - tmp[i]);
		mycnt -= ccnt[tmp[i]], ++i;
	}
	return res == 0x3f3f3f3f ? -1 : res;
}

int main(void)
{
	read >> n >> m;
	for (int i = 1; i <= n; ++i)
		read >> a[i];
	int tim = 0;
	std::vector<Query> q;
	for (int i = 1; i <= m; ++i) {
		int op; read >> op;
		if (op == 1) {
			Query tmp;
			tmp.id = q.size() + 1;
			tmp.t = tim;
			read >> tmp.l >> tmp.r >> tmp.k;
			q.emplace_back(tmp);
		}
		else {
			++tim;
			read >> tpos[tim] >> tcg[tim];
		}
	}
	std::sort(q.begin(), q.end());

	int L = 1, R = 0, T = 0;
	for (int i = 0; i < q.size(); ++i) {
		while (T < q[i].t) {
			++T;
			if (L <= tpos[T] && tpos[T] <= R) {
				Dec(tpos[T]);
				std::swap(a[tpos[T]], tcg[T]);
				Add(tpos[T]);
			}
			else std::swap(a[tpos[T]], tcg[T]);
		}
		while (T > q[i].t) {
			if (L <= tpos[T] && tpos[T] <= R) {
				Dec(tpos[T]);
				std::swap(a[tpos[T]], tcg[T]);
				Add(tpos[T]);
			}
			else std::swap(a[tpos[T]], tcg[T]);
			--T;
		}
		while (L > q[i].l) Add(--L);
		while (R < q[i].r) Add(++R);
		while (L < q[i].l) Dec(L++);
		while (R > q[i].r) Dec(R--);

		ans[q[i].id] = calc(q[i].k);
	}
	for (int i = 1; i <= q.size(); ++i)
		printf("%d\n", ans[i]);
	return 0;
}
