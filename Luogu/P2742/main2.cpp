#include <cmath>
#include <vector>
#include <cctype>
#include <cstdio>
#include <cstdint>
#include <iostream>
#include <algorithm>

#define read std::cin
using i32 = int32_t;
using i64 = int64_t;
using u32 = uint32_t;
using u64 = uint64_t;
using vi32 = std::vector<i32>;
using PII = std::pair<i32, i32>;
using PDD = std::pair<double, double>;
const int N = 2e5 + 10;

template<typename T>
T sq(T x) { return x * x; }
double getDis(PDD a, PDD b)
{ return sqrt(sq(a.first - b.first) + sq(a.second - b.second)); }

i32 n;
PDD p[N];
i32 stk[N], top;

int main(void)
{
	//Think twice, code once.
	std::ios::sync_with_stdio(false);
	read >> n;
	for (int i = 1; i <= n; ++i) {
		read >> p[i].first >> p[i].second;
	}
	std::sort(p + 1, p + 1 + n);
	std::vector<PDD> ans;
	for (int op = 0; op < 2; ++op) {
		top = 0;
		for (int i = (op == 0 ? 1 : n); (op == 0 ? i <= n : i >= 1); i += (op == 0 ? 1 : -1)) {
			while (top > 1) {
				i32 a = stk[top - 1], b = stk[top];
				double left = 1ll * (p[i].second - p[b].second) * (p[b].first - p[a].first);
				double right = 1ll * (p[b].second - p[a].second) * (p[i].first - p[b].first);
				if (left <= right) top -= 1;
				else break;
			}
			stk[++top] = i;
		}
		for (int i = 1 + op; i <= top - op; ++i) ans.emplace_back(p[stk[i]]);
	}
	double res = 0;
	for (int i = 0; i < ans.size(); ++i) {
		res += getDis(ans[(i - 1 + ans.size()) % ans.size()], ans[i]);
	}
	printf("%.2lf\n", std::round(res * 100) / 100.0);
	return 0;
}
