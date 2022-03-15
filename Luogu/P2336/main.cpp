#include <cmath>
#include <vector>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <algorithm>

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

const int N = 2e6 + 10, LOG = 25;

int n, m;
int len[N], pos[N];
int ansn[N], ansm[N];
int rkid[N];
vector<int> id, str;

int sa[N], rk[N], height[N], x[N << 1], y[N << 1], c[N];
int lg2[N], st[N][LOG];

void buildSA(void)
{
	int n = str.size() - 1, m = 1e4 + 10;
	for (int i = 1; i <= n; ++i) ++c[x[i] = str[i]];
	for (int i = 1; i <= m; ++i) c[i] += c[i - 1];
	for (int i = n; i >= 1; --i) sa[c[x[i]]--] = i;

	for (int k = 1; k <= n; k <<= 1) {
		int num = 0;
		for (int i = n - k + 1; i <= n; ++i) y[++num] = i;
		for (int i = 1; i <= n; ++i)
			if (sa[i] > k) y[++num] = sa[i] - k;

		for (int i = 0; i <= m; ++i) c[i] = 0;
		for (int i = 1; i <= n; ++i) ++c[x[i]];
		for (int i = 1; i <= m; ++i) c[i] += c[i - 1];
		for (int i = n; i >= 1; --i) sa[c[x[y[i]]]--] = y[i], y[i] = 0;

		swap(x, y);
		num = x[sa[1]] = 1;
		for (int i = 2; i <= n; ++i)
			x[sa[i]] = (y[sa[i]] == y[sa[i - 1]] && y[sa[i] + k] == y[sa[i - 1] + k]) ? num : ++num;
		if (num == n) break;
		m = num;
	}

	for (int i = 1; i <= n; ++i)
		rk[sa[i]] = i;

	for (int i = 1, k = 0; i <= n; ++i) {
		if (rk[i] == 1) continue;
		int j = sa[rk[i] - 1];
		if (k) --k;
		while (i + k <= n && j + k <= n && str[i + k] == str[j + k])
			++k;
		height[rk[i]] = k;
	}
}
void buildST(void)
{
	int n = str.size() - 1;
	lg2[1] = 0;
	for (int i = 2; i <= n; ++i)
		lg2[i] = lg2[(i >> 1)] + 1;

	for (int i = 1; i <= n; ++i)
		st[i][0] = height[i];
	for (int i = 1; i <= lg2[n]; ++i)
		for (int j = 1; j + (1 << i) - 1 <= n; ++j)
			st[j][i] = min(st[j][i - 1], st[j + (1 << i - 1)][i - 1]);
}
int queryST(int l, int r)
{
	++l;
	int len = r - l + 1;
	return min(st[l][lg2[len]], st[r - (1 << lg2[len]) + 1][lg2[len]]);
}

int getleft(int rank, int len)
{
	int l = 1, r = rank;
	while (l < r) {
		int mid = l + r >> 1;
		if (queryST(mid, rank) >= len) r = mid;
		else l = mid + 1;
	}
	return l;
}
int getright(int rank, int len)
{
	int l = rank, r = str.size() - 1;
	while (l < r) {
		int mid = l + r + 1 >> 1;
		if (queryST(rank, mid) >= len) l = mid;
		else r = mid - 1;
	}
	return r;
}

int BLEN;
int Getid(int x) { return x / BLEN; }

struct Query
{
	int id;
	int l, r;


	Query(int _id, int _l, int _r) : id(_id), l(_l), r(_r) {}
	bool operator<(const Query &other)
	{
		if (Getid(l) == Getid(other.l))
			return r < other.r;
		return l < other.l;
	}
};

vector<Query> q;
int nowans, cnt[N];

void Add(int x, int tim)
{
	if (!rkid[x]) return;
	if (cnt[rkid[x]] == 0) {
		++nowans;
		ansn[rkid[x]] -= tim;
	}
	++cnt[rkid[x]];
}
void Dec(int x, int tim)
{
	if (!rkid[x]) return;
	--cnt[rkid[x]];
	if (cnt[rkid[x]] == 0) {
		--nowans;
		ansn[rkid[x]] += tim;
	}
}
void calc(void)
{
	BLEN = max(1, (int)sqrt(n));
	sort(q.begin(), q.end());
	int L = 1, R = 0;
	int tim = 0;
	for (auto t : q) {
		++tim;
		while (L > t.l) Add(--L, tim);
		while (R < t.r) Add(++R, tim);
		while (L < t.l) Dec(L++, tim);
		while (R > t.r) Dec(R--, tim);
		ansm[t.id] = nowans;
	}
	++tim;
	while (L <= R) Dec(L++, tim);
}

int main(void)
{
	read >> n >> m;
	str.emplace_back(1e4 + 1);
	id.emplace_back(0);
	for (int i = 1; i <= n; ++i) {
		int len; read >> len;
		for (int j = 1; j <= len; ++j) {
			int x; read >> x;
			str.emplace_back(x);
			id.emplace_back(i);
		}
		str.emplace_back(1e4 + 1);
		id.emplace_back(0);

		read >> len;
		for (int j = 1; j <= len; ++j) {
			int x; read >> x;
			str.emplace_back(x);
			id.emplace_back(i);
		}
		str.emplace_back(1e4 + 1);
		id.emplace_back(0);
	}
	for (int i = 1; i <= m; ++i) {
		read >> len[i];
		pos[i] = str.size();
		for (int j = 1; j <= len[i]; ++j) {
			int x; read >> x;
			str.emplace_back(x);
			id.emplace_back(0);
		}
		str.emplace_back(1e4 + 1);
		id.emplace_back(0);
	}

	buildSA();
	buildST();
	for (int i = 1; i < id.size(); ++i)
		rkid[i] = id[sa[i]];

	for (int i = 1; i <= m; ++i) {
		int p = pos[i];
		int L = getleft(rk[p], len[i]);
		int R = getright(rk[p], len[i]);
		q.emplace_back(i, L, R);
	}

	calc();
	for (int i = 1; i <= m; ++i)
		printf("%d\n", ansm[i]);
	for (int i = 1; i <= n; ++i)
		printf("%d ", ansn[i]);
	puts("");
	return 0;
}
