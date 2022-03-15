#include <cctype>
#include <cstdio>
#include <algorithm>

using namespace std;

#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;

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
	FSI& operator>>(char &ch)
	{
		do ch = getchar();
		while (isspace(ch));
		return *this;
	}
} IO;

const int N = 2e5 + 10;
int M;
int mod;
inline int lowbit(int x) { return x & -x; }

int n, m;
int tr[N];

void add(int k, int t)
{
	for (int i = k; i; i -= lowbit(i))
		tr[i] = max(tr[i], t);
}
int query(int k)
{
	int res = 0;
	for (int i = k; i <= M; i += lowbit(i))
		res = max(tr[i], res);
	return res;
}

int main(void)
{
	IO >> m >> mod;
	M = m;
	int lastans = 0;
	for (int i = 1; i <= m; ++i) {
		char op; int x;
		IO >> op >> x;
		if (op == 'Q')
			--M, printf("%d\n", lastans = query(n - x + 1));
		else
			add(++n, (0ll + x + lastans) % mod);
	}
	return 0;
}
