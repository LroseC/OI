#include <vector>
#include <climits>
#include <iostream>
#include <algorithm>

#define read std::cin
using i32 = int;
using i64 = long long;
using vi32 = std::vector<i32>;
using PII = std::pair<i32, i32>;
const int N = 1e6 + 10;

int n, m, nm;
char str[N];
i32 dec[N], res[N];

void work(void)
{
	read >> n >> m;
	nm = n * m;
	read >> str + 1;
	for (int i = 1; i <= nm; ++i) {
		dec[i] = res[i] = 0;
	}
	for (int i = 1, cnt = 0; i <= nm; ++i) {
		if (str[i] == '0') ++cnt;
		else cnt = 0;
		if (cnt >= m) ++dec[i];
	}
	for (int i = 1; i < m; ++i) {
		if (str[i] != '0') break;
		++dec[i];
	}
	for (int i = m + 1; i <= nm; ++i) {
		dec[i] += dec[i - m];
	}
	for (int i = 1; i <= nm; ++i) {
		res[i] -= dec[i];
		dec[i] = 0;
	}
	for (int i = 1; i <= m; ++i) {
		if (str[i] == '0') {
			int t;
			for (t = i; t <= nm; t += m) {
				if (str[t] != '0')
					break;
			}
			t = std::min(t, nm + 1);
			++dec[i];
			--dec[t];
		}
	}
	for (int i = 1; i <= nm; ++i) {
		dec[i] += dec[i - 1];
		res[i] -= dec[i];
	}
	for (int i = 1; i <= nm; ++i) {
		printf("%d ", (i - 1) / m + 1 + std::min(m, i) + res[i]);
	}
	puts("");
}

int main(void)
{
	//Think twice, code once.
#ifndef DEBUG
	std::ios::sync_with_stdio(false);
#endif
	int tt; read >> tt;
	while (tt--) {
		work();
	}
	return 0;
}
