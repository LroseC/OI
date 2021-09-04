#include <vector>
#include <cstdio>
#include <iostream>

using namespace std;

const int N = 2e5 + 10;

int k, n;
int a[N];
bool vis[N];

int main(void)
{
	ios::sync_with_stdio(0);
	cin >> n >> k;
	if (k == 1) {
		for (int i = n; i; --i) cout << i << ' ';
		cout << endl;
		return 0;
	}
	for (int i = 1; i <= k; ++i) {
		cin >> a[i];
		vis[a[i]] = 1;
	}
	vector<int> ans;
	ans.emplace_back(a[1]);
	for (int i = n; i; --i) {
		if (vis[i]) continue;
		ans.emplace_back(i);
	}
	for (int i = 2; i <= k; ++i) ans.emplace_back(a[i]);
	for (auto x : ans) cout << x << ' ';
	cout << endl;
	return 0;
}