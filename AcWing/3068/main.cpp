#include <vector>
#include <cstdio>
#include <algorithm>

using namespace std;

typedef long long LL;
const int N = 1010;

struct PII
{
	int x, y;
	bool operator<(const PII &b) const
	{
		return x == b.x ? y < b.y : x < b.x;
	}
};

int n;
PII l[N], r[N];
vector<int> nums;
PII q[N];

int get(int Left, int Right)
{
	int cnt = 0;
	for (int i = 1; i <= n; ++i)
		if (l[i].x <= Left && r[i].x >= Right)
			q[++cnt] = {l[i].y, r[i].y};
	if (cnt == 0) return 0;
	sort(q + 1, q + 1 + cnt);

	int res = 0;
	int st = q[1].x, ed = q[1].y;
	for (int i = 2; i <= cnt; ++i) {
		if (ed >= q[i].x) ed = max(ed, q[i].y);
		else {
			res += ed - st;
			st = q[i].x, ed = q[i].y;
		}
	}
	return res + ed - st;
}

int main(void)
{
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%d%d%d%d", &l[i].x, &l[i].y, &r[i].x, &r[i].y);
		nums.push_back(l[i].x), nums.push_back(r[i].x);
	}
	sort(nums.begin(), nums.end());
	nums.erase(unique(nums.begin(), nums.end()), nums.end());
	
	LL ans = 0;
	for (int i = 1; i < nums.size(); ++i) {
		ans += 1ll * (nums[i] - nums[i - 1]) * get(nums[i - 1], nums[i]);
	}
	printf("%lld\n", ans);
}