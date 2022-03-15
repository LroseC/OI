#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int n;
int r[110];
vector<int> nums;

int h(void)
{
	int res = 0;
	for (int i = 2; i <= n; ++i) res += (abs(r[i] - r[i - 1]) != 1);
	return res;
}
bool check(void)
{
	for (int i = 1; i <= n; ++i)
		if (r[i] != i - 1) return 0;
	return 1;
}

bool IDA_star(int dep, int limit)
{
	int tmp = h();
	if (dep + tmp > limit) return 0;
	if (check()) return 1;
	for (int right = 2; right <= n; ++right) {
		reverse(r + 1, r + right + 1);
		if (IDA_star(dep + 1, limit)) return 1;
		reverse(r + 1, r + right + 1);
	}
	return 0;
}

int main(void)
{
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		cin >> r[i];
		nums.emplace_back(r[i]);
	}
	sort(nums.begin(), nums.end());
	nums.erase(unique(nums.begin(), nums.end()), nums.end());
	for (int i = 1; i <= n; ++i) r[i] = lower_bound(nums.begin(), nums.end(), r[i]) - nums.begin();
	int depth = 0;
	while (!IDA_star(0, depth)) ++depth;
	cout << depth << endl;
	return 0;
}