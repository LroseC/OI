#include <map>
#include <cstdio>
#include <algorithm>

using namespace std;

const int N = 5e5 + 10;

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
} cin;
struct Query
{
	int id, ansid;
	int l, r;
};
struct PII
{
	int x, y;
};
struct cmpl
{
	bool operator()(const Query &a, const Query &b)
	{
		return a.l < b.l;
	}
};
struct cmpr
{
	bool operator()(const Query &a, const Query &b)
	{
		if (a.id != b.id) return a.id < b.id;
		return a.r < b.r;
	}
};

int ans = 1;
int n, m, block_len = 2;
int A[N];
Query q[N];
int ll[N], rr[N];
int L[N], R[N];
int cnt[N], __cnt[N];
PII tans[N];

void Add(int x)
{
	++cnt[A[x]];
	if (cnt[A[x]] >= cnt[ans])
		ans = A[x];
}
void Dec(int x)
{
	--cnt[A[x]];
}
inline int Getid(int x) { return (x - 1) / block_len + 1; }
inline int GetL(int id) { return (id - 1) * block_len + 1; }
inline int GetR(int id) { return id * block_len; }

int main(void)
{
	cin >> n >> m;
	for (int i = 1; i <= n; ++i) cin >> A[i];
	for (int i = 1; i <= m; ++i) {
		q[i].ansid = i;
		cin >> q[i].l >> q[i].r;
		ll[i] = q[i].l, rr[i] = q[i].r;
	}
	for (int i = 1; i <= m; ++i) {
		q[i].id = Getid(q[i].l);
	}
	sort(q + 1, q + 1 + m, cmpr());
	int l = 1, r = 0, lastblock;
	for (int i = 1; i <= m; ++i) {
		if (Getid(q[i].l) == Getid(q[i].r)) {
			int ans = 0;
			int l = q[i].l, r = q[i].l - 1;
			while (r < q[i].r) {
				++r;
				++__cnt[A[r]];
				if (__cnt[A[r]] > __cnt[ans]) ans = A[r];
			}
			tans[q[i].ansid].x = ans;
			tans[q[i].ansid].y = __cnt[ans];
			while (r > q[i].l - 1) --__cnt[A[r]], r--;
			continue;
		}
		if (Getid(q[i].l) != lastblock) {
			int RR = GetR(Getid(q[i].l));
			while (l < r) Dec(r--);
			l = RR + 1, r = RR;
			ans = 0;
			lastblock = Getid(q[i].l);
		}
		while (r < q[i].r) Add(++r);
		int tmp = ans, tmpl = l;
		while (l > q[i].l) Add(--l);
		tans[q[i].ansid].x = ans;
		tans[q[i].ansid].y = cnt[ans];

		while (tmpl > l) Dec(l++);
		ans = tmp;
	}
	for (int i = 1; i <= m; ++i) {
//		printf("%d, %d\n", tans[i].x, tans[i].y);
		printf("%d\n", tans[i].y > (rr[i] - ll[i] + 1) / 2.0 ? tans[i].x : 0);
	}
	return 0;
}
