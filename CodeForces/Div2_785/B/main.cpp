#include <set>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using i64 = long long;
using vint = std::vector<int>;
using PII = std::pair<int, int>;

int main(void)
{
	//Think twice, code once.
	std::ios::sync_with_stdio(false);
	int tt; std::cin >> tt;
	while (tt--) {
		std::string s;
		std::cin >> s;
		int n = s.size();
		std::set<char> S;
		for (int i = 0; i < n; ++i) {
			S.insert(s[i]);
		}
		std::set<char> cnt;
		for (int i = 0; i < S.size(); ++i)
			cnt.insert(s[i]);
		if (cnt.size() != S.size()) {
			puts("No");
			continue;
		}
		else {
			bool flag = 1;
			for (int i = 0; i < n; i += S.size()) {
				for (int j = 0; j < S.size() && i + j < n; ++j)
					if (s[i + j] != s[j]) flag = 0;
			}
			puts(flag ? "Yes" : "No");
		}
	}
	return 0;
}
