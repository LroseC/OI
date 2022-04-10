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
const int N = 2e5 + 10;

int n, m, cnt1, cnt2;
int a[N];
bool vis[N];

int main(void)
{
	read >> n;
	for (int i = 1; i <= n; ++i)
		read >> a[i];
	if (a[1] == 1) {
		puts("No");
		return 0;
	}
	while (n && a[n] == 0) --n;
	if (n == 0) {
		puts("Yes");
		return 0;
	}
	a[0] = a[n + 1] = -1;
	for (int i = 1; i <= n; ++i)
		if (a[i] == a[i - 1] || a[i] == a[i + 1])
			vis[i] = 1;
	for (int i = 1; i <= n; ++i) {
		if (vis[i]) {
			m = i;
			break;
		}
		++cnt1;
	}
	for (int i = m; i < n; ++i)
		if (a[i] != a[i + 1]) ++cnt2;
	if (cnt1 >= cnt2) puts("Yes");
	else puts("No");
	return 0;
}
