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
using PII = std::pair<int, int>;
const int N = 2010;

int n, K;
char str[N];
char maxCnt[N];
int cnt[N][26], ccnt[N];

bool check(int res)
{
	std::memset(cnt, 0, sizeof cnt);
	std::memset(ccnt, 0, sizeof ccnt);
	for (int i = 0; i < n; ++i) {
		++ccnt[i % res];
		++cnt[i % res][str[i] - 'a'];
		if (cnt[i % res][str[i] - 'a'] > cnt[i % res][maxCnt[i % res] - 'a'])
			maxCnt[i % res] = str[i];
	}
	int tot = 0;
	for (int i = 0; i < res; ++i)
		tot += ccnt[i] - cnt[i][maxCnt[i] - 'a'];
	return tot <= K;
}

int main(void)
{
	read >> n >> K;
	scanf("%s", str);
	for (int i = 1; i <= n; ++i)
		if (n % i == 0 && check(i)) {
			printf("%d\n", i);
			return 0;
		}
	return 0;
}
