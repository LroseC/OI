#include <cmath>
#include <cctype>
#include <cstdio>

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

using i64 = long long;
const int N = 1e5 + 10;

int n, m;
int ans[N << 1];
bool vis[N << 1];

int main(void)
{
	read >> n >> m;
	if (m == 1 || m == n * 2 - 1) {
		puts("No");
		return 0;
	}
	puts("Yes");
	int delta = abs(n - m);
	if (delta == 0) {
		for (int i = 1; i <= n * 2 - 1; ++i)
			printf("%d ", i);
	}
	else if (n < m) {
		for (int i = n + 2, j = delta; j; ++i, --j) {
			ans[i] = i - 2;
			vis[i - 2] = 1;
		}
		int now = 1;
		for (int i = 1; i <= n * 2 - 1; ++i) {
			if (ans[i]) continue;
			while (vis[now]) ++now;
			ans[i] = now;
			vis[now] = 1;
		}
		for (int i = 1; i <= n * 2 - 1; ++i)
			printf("%d ", ans[i]);
		puts("");
	}
	else {
		for (int i = n - 2, j = delta; j; --i, --j) {
			ans[i] = i + 2;
			vis[i + 2] = 1;
		}
		int now = 1;
		for (int i = 1; i <= n * 2 - 1; ++i) {
			if (ans[i]) continue;
			while (vis[now]) ++now;
			ans[i] = now;
			vis[now] = 1;
		}
		for (int i = 1; i <= n * 2 - 1; ++i)
			printf("%d ", ans[i]);
		puts("");
	}
	return 0;
}
