#include <cmath>
#include <vector>
#include <cctype>
#include <cstdio>
#include <algorithm>
#include <unordered_map>

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

using ull = unsigned long long;
using PUI = pair<ull, int>;
const int N = 1e5 + 10, S = 1e6 + 10;
int BL;

int getid(int pos) { return pos / BL; }
struct Query
{
	int id, l, r;

	Query(void) { id = l = r = 0; }
	Query(int _id, int _l, int _r) : id(_id), l(_l), r(_r) {}
	bool operator<(const Query &other) const
	{
		if (getid(l) != getid(other.l))
			return getid(l) < getid(other.l);
		else return r < other.r;
	}
};

int n, m;
ull myarray[N];
int cnt[S];
ull hashval[N];
vector<Query> q;
unordered_map<ull, int> M;
int ans[N];

ull sq(ull x) { return x * x; }
void Add(int pos, int &res)
{
	auto val = hashval[pos];
	res += M[val];
	++M[val];
}
void Dec(int pos, int &res)
{
	auto val = hashval[pos];
	--M[val];
	res -= M[val];
}

int main(void)
{
	read >> n;
	BL = sqrt(n);
	for (int i = 1; i <= n; ++i)
		read >> myarray[i];
	PUI tmp;
	for (int i = 1; i <= n; ++i) {
		cnt[myarray[i]] ^= 1;
		if (cnt[myarray[i]]) {
			tmp.first += sq(myarray[i]);
			tmp.second ^= myarray[i];
		}
		else {
			tmp.first -= sq(myarray[i]);
			tmp.second ^= myarray[i];
		}
		hashval[i] = tmp.first * tmp.second;
	}

	read >> m;
	for (int i = 1; i <= m; ++i) {
		int l, r; read >> l >> r;
		q.emplace_back(i, l, r);
	}
	sort(q.begin(), q.end());
	int L = 1, R = 0;
	int res = 0;
	++M[0ull];
	for (auto t : q) {
		while (L > t.l) Add(--L - 1, res);
		while (R < t.r) Add(++R, res);
		while (L < t.l) Dec(L++ - 1, res);
		while (R > t.r) Dec(R--, res);
		ans[t.id] = res;
	}
	for (int i = 1; i <= m; ++i)
		printf("%d\n", ans[i]);
	return 0;
}
