#include <cstdio>
#include <iostream>

using namespace std;

int n;
int ans;
int cnt[110];
string str[110];

string kkk;

void dfs(string now, int len)
{
	ans = max(ans, len);
	for (int i = 1; i <= n; ++i) {
		if (cnt[i] == 2) continue;
		for (int j = 1; j < min(now.size(), str[i].size()); ++j) {
			string a = now.substr(now.size() - j);
			string b = str[i].substr(0, j);
			if (a == b) {
				++cnt[i];
				dfs(str[i], len + str[i].size() - j);
				--cnt[i];
			}
		}
	}
}

int main(void)
{
	cin >> n;
	for (int i = 1; i <= n; ++i) cin >> str[i];
	char ch; cin >> ch;
	for (int i = 1; i <= n; ++i) {
		if (str[i][0] == ch) {
			++cnt[i];
			dfs(str[i], str[i].size());
			--cnt[i];
		}
	}
	cout << ans << endl;
}