#include <vector>
#include <iostream>
#include <algorithm>
#include <functional>

using namespace std;

int a;
int ans;
vector<int> nums;
vector<int> l, r;
vector<int> tmp1, tmp2;

void dfs(int t)
{
	if (t == nums.size()) {
		tmp1 = l, tmp2 = r;
		sort(tmp1.begin(), tmp1.end(), greater<int>());
		sort(tmp2.begin(), tmp2.end(), greater<int>());
		int n = 0, m = 0;
		for (auto x : tmp1) n = n * 10 + x;
		for (auto x : tmp2) m = m * 10 + x;
		if (n != 0 && m != 0)
			ans = max(ans, n * m);
		return;
	}
	l.emplace_back(nums[t]);
	dfs(t + 1);
	l.pop_back();
	r.emplace_back(nums[t]);
	dfs(t + 1);
	r.pop_back();
}

int main(void)
{
	cin >> a;
	while (a) nums.emplace_back(a % 10), a /= 10;
	dfs(0);
	printf("%d\n", ans);
	return 0;
}