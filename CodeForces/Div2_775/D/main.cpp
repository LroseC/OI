#include <vector>
#include <cctype>
#include <cstdio>
#include <algorithm>

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

const int N = 1e6 + 10;

bool vis[N];

int main(void)
{
	int T; read >> T;
	while (T--) {
		int n, m; read >> n >> m;
		std::vector<int> a(n);
		for (int i = 0; i < n; ++i) {
			read >> a[i];
			vis[a[i]] = 1;
		}
		std::sort(a.begin(), a.end());
		a.erase(std::unique(a.begin(), a.end()), a.end());
		n = a.size();
		bool flag = 1;
		for (int i = 0; i < n; ++i) {
			for (int j = 1; 1ll * j * a[i] <= m; ++j)
				if (!vis[j]) {
					auto it = std::lower_bound(a.begin(), a.end(), a[i] * j);
					if (it != a.end() && *it < a[i] * (j + 1)) {
						flag = 0;
						break;
					}
				}
			if (!flag) break;
		}
		puts(flag ? "Yes" : "No");
		for (int i = 0; i < n; ++i)
			vis[a[i]] = 0;
	}
	return 0;
}
