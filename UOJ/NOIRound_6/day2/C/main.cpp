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

using i32 = int;
using i64 = long long;
using PII = std::pair<i32, i32>;
const int N = 5e3 + 10;

i32 nex[N], f[N], cnt[N];

i64 getAns(i32 n, char str[], int nex[])
{
	for (int i = 0; i < n; ++i)
		putchar(str[i]);
	putchar('\n');
	nex[0] = 0;
	for (int i = 1, j = 0; i < n; ++i) {
		while (j && str[i] != str[j]) j = nex[j - 1];
		if (str[i] == str[j]) j += 1;
		nex[i] = j;
	}
	i64 res = f[1];
	std::memset(cnt, 0, sizeof cnt);
	for (int i = 1; i < n; ++i)
		++cnt[nex[i]];
	for (int i = n - 1; i >= 0; --i) {
		cnt[nex[i - 1]] += cnt[i];
	}
	for (int x = nex[n - 1]; x; x = nex[x - 1]) {
		res += f[cnt[x] + 1];
	}
	return res;
}

i32 n, m;
char str[N];

int main(void)
{
	//Think twice, code once.
	read >> n >> m;
	scanf("%s", str + 1);
	for (int i = 1; i <= n; ++i)
		read >> f[i];
	while (m--) {
		i32 l, r;
		read >> l >> r;
		printf("%lld\n", getAns(r - l + 1, str + l, nex));
	}
	return 0;
}
