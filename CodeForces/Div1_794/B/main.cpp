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
		std::cin >> a >> b >> c >> d;
		std::cin >> str;
		int cntA = 0, cntB = 0;
		for (int i = 0; str[i]; ++i) {
			cntA += str[i] == 'A';
			cntB += str[i] == 'B';
		}
		if (cntA != a + c + d || cntB != b + c + d) {
			puts("NO");
			continue;
		}
		char last = str[0];
		int len = 1;
		vint sq;
		for (int i = 1; str[i]; ++i) {
			if (str[i] != last) {
				sq.emplace_back(len);
				len = 1, last = str[i];
			}
		}
		sq.emplace_back(len);
		last = str[0] - 'A';
		for (int i = 1; i < sq.size(); ++i, last ^= 1) {
			if (sq[i - 1] > 1 && sq[i] > 1) {
				if (last == 0 && c) --c;
				if (last == 1 && d) --d;
			}
		}
		last = str[0] - 'A';
		for (int i = 0; i < sq.size(); ++i, last ^= 1) {
			if (sq[i] == 1 && (i == 0 || sq[i - 1] > 1)) {
				int left = i;
				int type = last;
				while (i + 1 < sq.size() && sq[i + 1] == 1) ++i, last ^= 1;
			}
		}
	}
	return 0;
}
