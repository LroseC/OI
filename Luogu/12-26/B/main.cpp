#include <cctype>
#include <cstdio>
#include <cstring>

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
} IO;

const int N = 3e5 + 10;
const int mod = 998244353;

class BIT
{
	private:
		int tr[N];
		inline int lowbit(int x) { return x & -x; }
	public:
		void clear(void) { memset(tr, 0, sizeof tr); }
		void insert(int x, int val)
		{
			for (int i = x; i < N; i += lowbit(i))
				tr[i] += val;
		}
		int query(int x)
		{
			int res = 0;
			for (int i = x; i; i -= lowbit(i))
				res += tr[i];
			return res;
		}
} bit;

int n, ans;
int A[N];
int stk[N];
bool vis[N];

void dfs(int id, int limit)
{
	if (id > limit)
	{
		bit.clear();
		int res = 0;
		for (int i = limit; i >= 1; --i) {
			res = (res + bit.query(stk[i] + 1)) & 1;
			bit.insert(stk[i] + 1, 1);
		}
		res = res ? -1 : 1;
		for (int i = 1; i <= limit; ++i)
			res = 1ll * res * A[(i - 1) & stk[i]] % mod;
		ans = (ans + res) % mod;
	}
	for (int i = 0; i < n; ++i)
		if (!vis[i]) {
			vis[i] = 1;
			stk[id] = i;
			dfs(id + 1, limit);
			vis[i] = 0;
		}
}

int main(void)
{
	IO >> n;
	for (int i = 0; i < n; ++i) IO >> A[i];
	dfs(1, n);
	printf("%d\n", ans);
	return 0;
}
