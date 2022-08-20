#include <cctype>
#include <cstdio>
#include <cstdint>
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

using i32 = int32_t;
using i64 = int64_t;
using PII = std::pair<i32, i32>;
const int N = 3e5 + 10;

i32 n;
i64 x;
i32 stk[N];
i64 a[N];

bool check(i32 state)
{
	i32 top = 0;
	for (int i = 0; i < n; ++i)
		if (state >> i & 1) {
			for (int j = 1; j <= top; ++j)
				if ((a[i] ^ a[stk[j]]) < x) return 0;
			stk[++top] = i;
		}
	return 1;
}

int main(void)
{
#ifndef DEBUG
	freopen("xor.in", "r", stdin);
	freopen("xor.out", "w", stdout);
#endif
	//Think twice, code once.
	read >> n >> x;
	for (int i = 0; i < n; ++i) {
		read >> a[i];
	}
	i32 res = 0;
	for (int i = 1; i < 1 << n; ++i) {
		res += check(i);
	}
	printf("%d\n", res);
	return 0;
}
