#include <vector>
#include <cctype>
#include <cstdio>
#include <cstdint>
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

using i32 = int32_t;
using i64 = int64_t;
using u32 = uint32_t;
using u64 = uint64_t;
using vi32 = std::vector<i32>;
using PII = std::pair<i32, i32>;
const int N = 610;

i32 n, mod;
i32 v[N][N];

int main(void)
{
	//Think twice, code once.
	read >> n >> mod;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			read >> v[i][j];
		}
	}
	i32 res = 1;
	for (int i = 1; i <= n; ++i) {
		for (int j = i + 1; j <= n; ++j) {
			while (v[j][i]) {
				//b, a % b <=> a, a - b * (a / b);
				i32 div = v[i][i] / v[j][i];
				for (int t = 1; t <= n; ++t) {
					v[i][t] = (v[i][t] - 1ll * v[j][t] * div) % mod;
				}
				res = -res;
				for (int t = 1; t <= n; ++t) {
					std::swap(v[i][t], v[j][t]);
				}
			}
		}
	}
	for (int i = 1; i <= n; ++i)
		res = 1ll * res * v[i][i] % mod;
	printf("%d\n", (res + mod) % mod);
	return 0;
}
