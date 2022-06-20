#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using i64 = long long;
using PII = std::pair<int, int>;
const int N = 1e5 + 10;

char str[N];
char nstr[N], res[N];
char ans[N];

bool geq(char a[], char b[], int len)
{
	for (int i = len; i >= 1; --i)
		if (a[i] < b[i]) return 0;
	return 1;
}

int main(void)
{
	int tt; std::cin >> tt;
	while (tt--) {
		int n;
		std::cin >> n >> str + 1;
		std::reverse(str + 1, str + 1 + n);
		for (int i = 1; i <= n; ++i) {
			str[i] -= '0';
			nstr[i] = str[i];
		}
		int len = n;
		++nstr[len];
		if (nstr[len] == 10) {
			nstr[len] = 0;
			nstr[++len] = 1;
		}
		for (int i = 1; i <= len; ++i)
			res[i] = nstr[i];
		for (int i = 1; i <= len / 2; ++i) {
			res[i] = res[len - i + 1];
		}
		if (!geq(res, nstr, len)) {
			for (int i = (len + 1) / 2; i >= 1; --i) {
				if (res[len - i + 1] != 9) {
					++res[len - i + 1];
					break;
				}
				res[i] = 0;
			}
			for (int i = 1; i <= len / 2; ++i) {
				res[i] = res[len - i + 1];
			}
		}
		for (int i = 1; i <= n; ++i)
			ans[i] = 0;
		for (int i = 1; i <= n; ++i) {
			ans[i] += res[i] - str[i];
//			std::cout << i << ':' << (int)res[i] << ',' << (int)str[i] << ',' << (int)ans[i] << '\n';
			if (ans[i] < 0) {
				--ans[i + 1];
				ans[i] += 10;
			}
//			std::cout << i << ':' << (int)res[i] << ',' << (int)str[i] << ',' << (int)ans[i] << '\n';
		}
		for (int i = n; i >= 1; --i)
			std::cout << (char)(ans[i] + '0');
		std::cout << '\n';
	}
	return 0;
}
