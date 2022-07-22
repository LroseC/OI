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

using i32 = int;
using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;
using vint = std::vector<int>;
using PII = std::pair<int, int>;
const int N = 2005;

i32 K;
i32 cnt[N];
i32 sum[N][N], C[N][N];
i64 fac[N];
inline i32 Mod(i32 x) { return x >= K ? x - K : x; }

int main(void)
{
	//Think twice, code once.
	int tt;
	read >> tt >> K;
	for (int i = 0; i < N; ++i) {
		C[i][0] = 1 % K;
		for (int j = 1; j <= i; ++j) {
			C[i][j] = Mod(C[i - 1][j - 1] + C[i - 1][j]);
			sum[i][j] = (j == 0 ? 0 : sum[i][j - 1]) + (C[i][j] == 0);
		}
		for (int j = i + 1; j < N; ++j)
			sum[i][j] = sum[i][j - 1];
	}
	while (tt--) {
		int n, m;
		read >> n >> m;
		i32 res = 0;
		for (int i = 0; i <= n; ++i)
			res += sum[i][m];
		printf("%d\n", res);
	}
	return 0;
}
