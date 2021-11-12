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

using LL = long long;
const int N = 2e5 + 10;

int n;
int a[N];
int stk[N], top;
int pre[N], nex[N];

int main(void)
{
	io >> n;
	for (int i = 1; i <= n; ++i) io >> a[i];
	for (int i = 1; i <= n; ++i) {
		while (top && a[i] < a[stk[top]]) --top;
		pre[i] = stk[top];
		stk[++top] = i;
	}
	top = 0;
	stk[0] = n + 1;
	for (int i = n; i >= 1; --i) {
		while (top && a[i] < a[stk[top]]) --top;
		nex[i] = stk[top];
		stk[++top] = i;
	}
	LL ans = 0;
	for (int i = 1; i <= n; ++i) {
		ans += 1ll * (nex[i] - i) * (i - pre[i]) * a[i];
	}
	printf("%lld\n", ans);
	return 0;
}