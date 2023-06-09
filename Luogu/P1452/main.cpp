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
const int N = 1e5 + 10;

i64 sq(i32 x) { return 1ll * x * x; }
i64 getDis(const PII &a, const PII &b)
{ return sq(a.first - b.first) + sq(a.second - b.second); }

i32 n;
PII p[N];
i32 stk[N], top;

int main(void)
{
	//Think twice, code once.
	read >> n;
	for (int i = 1; i <= n; ++i) {
		read >> p[i].first >> p[i].second;
	}
	std::sort(p + 1, p + 1 + n);
	std::vector<PII> ans;
	for (int i = 1; i <= n; ++i) {
		while (top > 1) {
			i32 a = stk[top - 1], b = stk[top];
			i64 left = 1ll * (p[i].second - p[b].second) * (p[b].first - p[a].first);
			i64 right = 1ll * (p[b].second - p[a].second) * (p[i].first - p[b].first);
			if (left <= right) top -= 1;
			else break;
		}
		stk[++top] = i;
	}
	for (int i = 1; i <= top; ++i) ans.emplace_back(p[stk[i]]);
	top = 0;
	for (int i = n; i >= 1; --i) {
		while (top > 1) {
			i32 a = stk[top - 1], b = stk[top];
			i64 left = 1ll * (p[i].second - p[b].second) * (p[b].first - p[a].first);
			i64 right = 1ll * (p[b].second - p[a].second) * (p[i].first - p[b].first);
			if (left <= right) top -= 1;
			else break;
		}
		stk[++top] = i;
	}
	for (int i = 2; i < top; ++i) ans.emplace_back(p[stk[i]]);
	i64 res = 0;
	const i32 mod = ans.size();
	auto Mod = [&](i32 x) { return x >= mod ? x - mod : x; };
	for (int i = 0, j = 0; i < ans.size(); ++i) {
		while (getDis(ans[i], ans[j]) < getDis(ans[i], ans[Mod(j + 1)])) j = Mod(j + 1);
		res = std::max(res, getDis(ans[i], ans[j]));
	}
	printf("%lld\n", res);
	return 0;
}
