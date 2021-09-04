#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;

typedef long long LL;
typedef pair<int, int> PII;

int n;
int nums[30];
bool vis[1 << 21];
vector<vector<PII>> abc;
vector<PII> a, b;
unordered_map<int, int> mp;

void dfs(int l, int r, int sum, int state, vector<PII> &a)
{
	if (l > r) {
		a.emplace_back(PII({sum, state}));
		return;
	}
	dfs(l + 1, r, sum, state, a);
	dfs(l + 1, r, sum + nums[l], state | (1 << l), a);
	dfs(l + 1, r, sum - nums[l], state | (1 << l), a);
}

int main(void)
{
	cin >> n;
	for (int i = 1; i <= n; ++i) cin >> nums[i];
	dfs(1, n / 2, 0, 0, a);
	dfs(n / 2 + 1, n, 0, 0, b);
	for (auto x : a) {
		if (!mp.count(x.first)) {
			mp[x.first] = abc.size();
			vector<PII> tmp;
			tmp.clear();
			abc.emplace_back(tmp);
		}
		abc[mp[x.first]].emplace_back(x);
	}
	LL ans = 0;
	for (auto x : b) {
		if (!mp.count(-x.first)) continue;
		int k = mp[-x.first];
		for (auto y : abc[k]) {
			if (vis[y.second | x.second]) continue;
			++ans;
			vis[y.second | x.second] = 1;
		}
	}
	cout << ans - 1 << endl;
	return 0;
}