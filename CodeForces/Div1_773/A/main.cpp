#include <vector>
#include <climits>
#include <cstring>
#include <iostream>
#include <algorithm>

#define read std::cin
using i32 = int;
using i64 = long long;
using vi32 = std::vector<i32>;
using PII = std::pair<i32, i32>;
const int N = 2e5 + 10;

vi32 nums;
i32 n, x;
i32 a[N], cnt[N];

void work(void)
{
	read >> n >> x;
	nums.clear();
	for (int i = 1; i <= n; ++i) {
		read >> a[i];
		nums.emplace_back(a[i]);
	}
	std::sort(a + 1, a + 1 + n);
	std::sort(nums.begin(), nums.end());
	nums.erase(std::unique(nums.begin(), nums.end()), nums.end());
	std::fill(cnt, cnt + nums.size(), 0);
	for (int i = 1; i <= n; ++i) {
		a[i] = std::lower_bound(nums.begin(), nums.end(), a[i]) - nums.begin();
		++cnt[a[i]];
	}
	i32 res = 0;
	for (int i = 1; i <= n; ++i) {
		if (!cnt[a[i]]) continue;
		i32 vi = nums[a[i]];
		i64 vix = 1ll * vi * x;
		auto it = std::lower_bound(nums.begin(), nums.end(), vix);
		if (it == nums.end() || *it != vix) res += cnt[a[i]];
		else {
			i32 j = it - nums.begin();
			cnt[j] -= cnt[a[i]];
			if (cnt[j] < 0) {
				res += std::abs(cnt[j]);
				cnt[j] = 0;
			}
		}
		cnt[a[i]] = 0;
	}
	printf("%d\n", res);
}

int main(void)
{
	//Think twice, code once.
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	i32 tt; read >> tt;
	while (tt--) {
		work();
	}
	return 0;
}
