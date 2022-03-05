#include <vector>
#include <cctype>
#include <cstdio>

struct FSI
{
	template<typename T>
	FSI& operator>>(T &res)
	{
		res = 0; T f = 1; char ch = getchar();
		while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
		while (isdigit(ch)) { res = res * 10 + ch - '0'; ch = getchar(); }
		res = res * f; return *this;
	}
} read;

const int N = 1e5 + 10;
using i64 = long long;

int n, m;
char a[N], b[N];
vector<int> q[N];
i64 sum, ans[n], d[N << 1];

int main(void)
{
	read >> n >> m;
	scanf("%s%s", a + 1, b + 1);
	for (char ch = 'A'; ch <= 'Z'; ++ch) {
		for (int i = 1; i <= n; ++i)
			s[i] = s[i - 1] + (a[i] == ch) - (b[i] == ch);
		for (int i = 1; i <= m; ++i)
			tag[i] |= s[L[i - 1]] != s[R[i]];
	}
	for (int i = 1; i <= m; ++i)
		if (!tag[i]) {
			q[L[i] - 1].emplace_back(-i);
			q[R[i]].emplace_back(i);
		}
	for (char ch = 'A'; ch <= 'Z'; ++ch) {
		for (int i = 1; i <= n; ++i) {
			if(a[i] == ch) {
				d[N + p + 1] += i << 1;
				++p;
				sum += d[p + N] - i;
			}
			if(b[i] == ch) {
				sum -= d[p + N] - i;
				--p;
				d[N + p + 1] -= i << 1;
			}
			for(int v : q[i]) {
				if (v > 0)
					ans[v] += sum;
				else
					ans[-v] -= sum;
			}
		}
		memset(d + N - n, 0, n << 4);
		sum = p = 0;
	}
	for (int i = 1; i <= m; ++i)
		printf("%d\n", ans[i] >> 1 | -tag[i]);
	return 0;
}
