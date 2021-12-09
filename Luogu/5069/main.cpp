#include <set>
#include <cctype>
#include <cstdio>

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

template<int _N>
class BIT
{
	private:
		inline int lowbit(int x) { return x & -x; }
		int tr[_N];
	public:
		BIT(void) { memset(tr, 0, sizeof tr); }
		void add(int x, int val)
		{
			for (int i = x; i < _N; i += lowbit(i))
				tr[i] += val;
		}
		int query(int x)
		{
			int res = 0;
			for (int i = x; i; i -= lowbit(i))
				res += tr[i];
			return res;
		}
};

int ans;
int n, m;
int A[N];
set<int> S;

int main(void)
{
	io >> n >> m;
	for (int i = 1; i <= n; ++i) io >> A[i];
	for (int i = 1; i <= n; ++i) {
		if (isbig(i) || issmall(i)) S.insert(i);
	}
	build();
	auto it = S.begin(), jt = S.end();
	solve(it, jt, 1);
	for (int i = 1; i <= m; ++i) {
		int x, y;
		io >> x >> y;
		it = jt = S.lower_bound(x);
		if (it != S.begin()) {
		}
		for (int j = x - 1; j <= x + 1; ++j)
			if (j >= 1 && j <= n) S.erase(j);
		for (int j = x - 1; j <= x + 1; ++j)
			if (j >= 1 && j <= n) {
				if (isbig(i) || issamll(i)) S.insert(i);
			}
	}
	return 0;
}