#include <vector>
#include <cctype>
#include <cstdio>
#include <cstdint>
#include <cstring>
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
const int N = 1e6 + 10;

i32 n, m;
char str[N];
i32 x[N], y[N], c[N], sa[N], rk[N], height[N];

void buildSA(void)
{
	m = 200;
	for (int i = 1; i <= n; ++i) ++c[x[i] = str[i]];
	for (int i = 1; i <= m; ++i) c[i] += c[i - 1];
	for (int i = n; i >= 1; --i) sa[c[x[i]]--] = i;
	for (int i = 1; i <= m; ++i) c[i] = 0;
	for (int k = 1; k <= n; k <<= 1) {
		i32 num = 0;
		for (int i = n - k + 1; i <= n; ++i) y[++num] = i;
		for (int i = 1; i <= n; ++i)
			if (sa[i] > k) y[++num] = sa[i] - k;
		for (int i = 1; i <= n; ++i) ++c[x[i]];
		for (int i = 1; i <= m; ++i) c[i] += c[i - 1];
		for (int i = n; i >= 1; --i) sa[c[x[y[i]]]--] = y[i], y[i] = 0;
		for (int i = 1; i <= m; ++i) c[i] = 0;
		std::swap(x, y);
		x[sa[1]] = num = 1;
		for (int i = 2; i <= n; ++i) {
			i32 t1 = sa[i] + k <= n ? y[sa[i] + k] : 0;
			i32 t2 = sa[i - 1] + k <= n ? y[sa[i - 1] + k] : 0;
			if (y[sa[i]] != y[sa[i - 1]] || t1 != t2) {
				num += 1;
			}
			x[sa[i]] = num;
		}
		if (num == n) break;
		m = num;
	}
	for (int i = 1; i <= n; ++i) {
		rk[sa[i]] = i;
	}
	for (int i = 1, j = 0; i <= n; ++i) {
		if (j) --j;
		if (rk[i] == 1) continue;
		while (str[i + j] == str[sa[rk[i] - 1] + j]) j += 1;
		height[rk[i]] = j;
	}
}

int main(void)
{
	//Think twice, code once.
	scanf("%s", str + 1);
	n = strlen(str + 1);
	buildSA();
	for (int i = 1; i <= n; ++i) {
		printf("%d ", sa[i]);
	}
	puts("");
	for (int i = 1; i <= n; ++i) {
		printf("%d ", height[i]);
	}
	puts("");
	return 0;
}
