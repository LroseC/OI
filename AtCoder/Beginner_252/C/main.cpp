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
		while (isdigit(ch)) { res = res * 10 + (ch - '0') * f; ch = getchar(); }
		return *this;
	}
} read;

using i64 = long long;

int n;
char s[110][11];

int main(void)
{
	read >> n;
	for (int i = 0; i < n; ++i) {
		scanf("%s", s[i]);
	}
	int ans = 0x3f3f3f3f;
	for (int j = 0; j < 10; ++j) {
		int res = 0;
		std::vector<int> cnt(10);
		for (int i = 0; i < n; ++i) {
			for (int k = 0; k < 10; ++k) {
				if (s[i][k] == j + '0') {
					res = std::max(res, k + cnt[k] * 10);
					++cnt[k];
				}
			}
		}
		ans = std::min(ans, res);
	}
	printf("%d\n", ans);
	return 0;
}
