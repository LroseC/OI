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
		res = res * f;
		return *this;
	}
} IO;

const int N = 2e5 + 10;

int last[N];
int a[N];

int main(void)
{
	int T; IO >> T;
	while (T--) {
		int n; IO >> n;
		int ans = INT_MAX;
		for (int i = 1; i <= n; ++i) {
			IO >> a[i];
			if (last[a[i]] != 0)
				ans = min(ans, i - last[a[i]]);
			last[a[i]] = i;
		}
		if (ans == INT_MAX) puts("-1");
		else printf("%d\n", n - ans);
		for (int i = 1; i <= n; ++i)
			last[a[i]] = 0;
	}
	return 0;
}
