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
const int N = 2e5 + 10;

i64 cnt[N];
std::vector<int> num[N];

int main(void)
{
	int n; read >> n;
	std::vector<int> a(n);
	for (int i = 0; i < n; ++i) {
		read >> a[i];
		num[a[i]].emplace_back(i);
	}
	i64 res = 0;
	for (int i = 0; i < n; ++i) {
		auto &arr = num[a[i]];
		int c = std::lower_bound(arr.begin(), arr.end(), i) - arr.begin();
		cnt[i] = (i == 0 ? 0 : cnt[i - 1]) + (i - c);
		if (i != 0)
			res = res + cnt[i - 1] - 1ll * c * (i - c);
	}
	printf("%lld\n", res);
	return 0;
}
