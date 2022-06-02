#include <cctype>
#include <cstdio>
#include <cstring>
#include <algorithm>

struct FSI
{
	template<typename T>
	FSI& operator>>(T &res)
	{
		res = 0; T f = 1; char ch = getchar();
		while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
		while (isdigit(ch)) { res = res * 10 + (ch - '0') * f; ch = getchar(); }
		return *this;
	}
} read;

using i64 = long long;
const int N = 2e5 + 10;

int n;
char str[N];
int max1, min0;
int nex1[N], nex0[N];

void work(void)
{
	scanf("%s", str + 1);
	n = std::strlen(str + 1);
	max1 = 0;
	for (int i = 1; i <= n; ++i)
		if (str[i] == '1') {
			nex1[i] = max1;
			max1 = i;
		}
	min0 = n + 1;
	for (int i = n; i >= 1; --i)
		if (str[i] == '0') {
			nex0[i] = min0;
			min0 = i;
		}
	int cnt = 0;
	for (int i = 1; i <= n; ++i) {
		if (str[i] == '1') {
			int nowmax1 = i == max1 ? nex1[i] : max1;
			if (nowmax1 <= i && i <= min0)
				++cnt;
		}
		if (str[i] == '0') {
			int nowmin0 = i == min0 ? nex0[i] : min0;
			if (max1 <= i && i <= nowmin0)
				++cnt;
		}
		if (str[i] == '?')
			if (max1 <= i && i <= min0)
				++cnt;
	}
	printf("%d\n", cnt);
}

int main(void)
{
	int T; read >> T;
	while (T--) work();
	return 0;
}
