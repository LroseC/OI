#include <deque>
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
} read;

const int N = 1e5 + 10;
const int mod = 998244353;

long long sum;
int m, K;
int fac[N];
deque<int> q;

int tr[N];
inline int lowbit(int x) { return x & -x; }
void add(int x, int v)
{
	++x;
	for (int i = x; i; i -= lowbit(i))
		tr[i] += v;
}
int query(int x)
{
	++x;
	int res = 0;
	for (int i = x; i < N; i += lowbit(i))
		res += tr[i];
	return res;
}

int main(void)
{
	fac[0] = 1;
	for (int i = 1; i < N; ++i)
		fac[i] = 1ll * fac[i - 1] * i % mod;
	read >> m >> K;
	while (m--) {
		int opt; read >> opt;
		int v, l, r;
		if (opt == 1) {
			read >> v;
			q.emplace_front(v);
			add(v, 1);
		}
		if (opt == 2) {
			read >> v;
			q.emplace_back(v);
			add(v, 1);
		}
		if (opt == 3) {
			v = q.front();
			add(v, -1);
			q.pop_front();
		}
		if (opt == 4) {
			v = q.back();
			add(v, -1);
			q.pop_back();
		}
		if (opt == 5) {
			read >> l >> r;
			if (sum > r)
				puts("0");
			else
				printf("%d\n", (1ll * query(l) * fac[q.size() - 1] + 1) % mod);
		}
	}
	return 0;
}
