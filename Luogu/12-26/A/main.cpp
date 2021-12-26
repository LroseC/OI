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
} IO;

const int N = 3e5 + 10;

struct Query
{
	int op, x, w, k;
};

int n, m, K;
int A[N];
int ans[N];
Query q[N];
set<int> S[N];

void add(int x, int w, int f)
{
	auto it = S[w].find(x);
	--it;
	int pre = *it;
	++it;

	++it;
	int nex = *it;
	--it;

	for (int k = 1; k <= K; ++k) {
		int p = max(pre, x - k) + 1;
		int n = min(nex, x + k) - 1;
		ans[k] += max(0, n - p + 1 - k + 1) * f;
	}
}

int main(void)
{
	IO >> n >> m;
	for (int i = 1; i <= n; ++i) {
		S[i].insert(0);
		S[i].insert(n + 1);
	}
	for (int i = 1; i <= n; ++i) {
		IO >> A[i];
		S[A[i]].insert(i);
	}
	for (int i = 1; i <= m; ++i) {
		IO >> q[i].op;
		if (q[i].op == 1)
			IO >> q[i].x >> q[i].w;
		else {
			IO >> q[i].k;
			K = max(K, q[i].k);
		}
	}
	for (int i = 1; i <= n; ++i) {
		add(i, A[i], 1);
	}
	for (int i = 1; i <= m; ++i) {
		if (q[i].op == 1) {
			int x = q[i].x, w = q[i].w;
			add(x, A[x], -1);
			S[A[x]].erase(x);
			A[x] = w;
			S[A[x]].insert(x);
			add(x, A[x], +1);
		}
		else {
			printf("%d\n", ans[q[i].k]);
		}
	}
	return 0;
}
