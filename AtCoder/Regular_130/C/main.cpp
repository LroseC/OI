#include <vector>
#include <string>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;
using LL = long long;
const char endl = '\n';

struct FastStreamInputOutput
{
	using FSIO = FastStreamInputOutput;
	template<typename T>
	FSIO& operator>>(T &res)
	{
		res = 0; T f = 1; char ch = getchar();
		while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
		while (isdigit(ch)) { res = res * 10 + ch - '0'; ch = getchar(); }
		res *= f; return *this;
	}
	FSIO& operator<<(char x)
	{
		putchar(x);
		return *this;
	}
	FSIO& operator<<(const char x[])
	{
		for (int i = 0; x[i]; ++i) putchar(x[i]);
		return *this;
	}
	template<typename T>
	FSIO& operator<<(const T &res)
	{
		static char buf[50]; int p = -1; T x = res;
		if (x == 0) putchar('0');
		if (x < 0) { putchar('-'); x = -x; }
		while (x) { buf[++p] = x % 10; x /= 10; }
		while (~p) { putchar(buf[p] + '0'); --p; }
		return *this;
	}
} io;

const int N = 1e5 + 10;

int n, m;
char str1[N], str2[N];
int cnt1[10], cnt2[10];
string ans1, ans2;

bool check(int x)
{
	for (int i = 0; i < 10; ++i) {
		if (x - i > 0 && x - i < 10 && cnt2[i] && cnt1[x - i]) {
			--cnt2[i];
			--cnt1[x - i];
			ans1.push_back(x - i + '0');
			ans2.push_back(i + '0');
			return 1;
		}
	}
	return 0;
}

int main(void)
{
	int cnt9 = 0;
	bool swp = 0;
	scanf("%s%s", str1 + 1, str2 + 1);
	n = strlen(str1 + 1);
	m = strlen(str2 + 1);
	if (n > m) {
		swp = 1;
		swap(n, m);
		swap(str1, str2);
	}
	for (int i = 1; i <= n; ++i) ++cnt1[str1[i] - '0'];
	for (int i = 1; i <= m; ++i) ++cnt2[str2[i] - '0'];
	int cha = m - n;
	cnt9 = min(cnt2[9], cha);
	cnt2[9] -= cnt9;
	int tmp = 0;
	bool flag = 0;
	for (int i = 1; i <= n; ++i) {
		int k = 10 - tmp;
		tmp = 0;
		bool sec = 0;
		for (int j = 0; j <= 10; ++j) {
			if (check(k + j)) {
				tmp = 1;
				sec = 1;
				flag = 1;
				break;
			}
		}
		if (!sec) break;
	}
	cnt2[9] += cnt9;
	for (int i = 1; i <= m - n; ++i) {
		if (cnt2[9]) {
			--cnt2[9];
			ans2.push_back('9');
		}
		else {
			for (int i = 0; i < 10; ++i)
				if (cnt2[i]) {
					--cnt2[i];
					ans2.push_back(i + '0');
					break;
				}
		}
	}
	reverse(ans1.begin(), ans1.end());
	reverse(ans2.begin(), ans2.end());
	for (int i = 0; i < 10; ++i) {
		while (cnt1[i]) {
			--cnt1[i];
			ans1.push_back(i + '0');
		}
		while (cnt2[i]) {
			--cnt2[i];
			ans2.push_back(i + '0');
		}
	}
	ios::sync_with_stdio(0);
	// reverse(ans1.begin(), ans1.end());
	// reverse(ans2.begin(), ans2.end());
	// int tot = 0;
	// char ttmp[100010];
	// for (int i = 0; i < n; ++i) ttmp[i] = ans1[i] - '0' + ans2[i] - '0';
	// for (int i = n; i < m; ++i) ttmp[i] = ans2[i] - '0';
	// for (int i = 0; i < m; ++i) {
	// 	ttmp[i + 1] += ttmp[i] / 10;
	// 	ttmp[i] %= 10;
	// 	tot += ttmp[i];
	// }
	// printf("tot = %d\n", tot + ttmp[m]);
	// reverse(ans1.begin(), ans1.end());
	// reverse(ans2.begin(), ans2.end());
	if (swp = 1) swap(ans1, ans2);
	cout << ans1 << '\n' << ans2 << '\n';
	// CHECK YOUR ARRAY TO MAKE SRUE YOUR CODE WON'T RE
	return 0;
}