#include <cmath>
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

const int N = 110;
const double eps = 1e-6;

i32 n;
double val[N][N];

bool gauss(void)
{
	for (int c = 1; c <= n; ++c) {
		i32 r = c;
		for (int t = r; t <= n; ++t)
			if (val[t][c]) {
				for (int i = 1; i <= n + 1; ++i) {
					std::swap(val[r][i], val[t][i]);
				}
			}
		if (std::fabs(val[r][c]) < eps) return 1;
		for (int i = n + 1; i >= c; --i) {
			val[r][i] /= val[r][c]	;
		}
		for (int i = 1; i <= n; ++i) {
			if (i == r) continue;
			double div = val[i][c];
			for (int j = 1; j <= n + 1; ++j) {
				val[i][j] -= div * val[r][j];
			}
		}
	}
	return 0;
}

int main(void)
{
	//Think twice, code once.
	read >> n;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n + 1; ++j) {
			read >> val[i][j];
		}
	if (gauss()) {
		puts("No Solution");
	}
	else {
		for (int i = 1; i <= n; ++i) {
			printf("%.2lf\n", val[i][n + 1]);
		}
	}
	return 0;
}
