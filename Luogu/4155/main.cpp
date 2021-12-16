#include <cctype>
#include <cstdio>
#include <climits>
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
} io;

const int N = 2e5 + 10;

struct Person
{
	int l, r;
	int id;
	Person(void) { l = r = 0; }
	Person(int _l, int _r, int _id) : l(_l), r(_r), id(_id) {}
	bool operator<(const Person &other) const
	{
		return l < other.l;
	}
};

int n, m;
Person per[N << 1];
int nex[N << 2][30];
int ans[N];

int main(void)
{
	per[0].l = per[0].r = INT_MAX;
	io >> n >> m;
	for (int i = 1; i <= n; ++i) {
		per[i].id = i;
		io >> per[i].l >> per[i].r;
	}
	sort(per + 1, per + 1 + n);
	for (int i = 1; i <= n; ++i) {
		if (per[i].r < per[i].l) per[i].r += m;
		per[i + n].l = per[i].l + m;
		per[i + n].r = per[i].r + m;
	}
	for (int i = 1; i <= n << 1; ++i) {
		nex[i][0] = upper_bound(per + 1, per + 1 + 2 * n, Person(per[i].r, 0, 0)) - per - 1;
	}
	for (int k = 1; k < 30; ++k) {
		for (int i = 1; i <= n << 1; ++i)
			nex[i][k] = nex[nex[i][k - 1]][k - 1];
	}
	for (int i = 1; i <= n; ++i) {
		int t = i;
		int res = 1;
		for (int k = 29; k >= 0; --k) {
			if (per[nex[t][k]].r < per[i].l + m) {
				t = nex[t][k];
				res += 1 << k;
			}
		}
		ans[per[i].id] = res + 1;
	}
	for (int i = 1; i <= n; ++i) printf("%d ", ans[i]);
	puts("");
	return 0;
}
