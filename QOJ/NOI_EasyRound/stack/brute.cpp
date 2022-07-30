#include <vector>
#include <cctype>
#include <cstdio>
#include <climits>
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
using vi32 = std::vector<i32>;
using PII = std::pair<i32, i32>;
const int N = 5e3 + 10;

i32 n, m;
i32 top[N], stk[N][N];

int main(void)
{
	//Think twice, code once.
	read >> n >> m;
	for (int i = 1; i <= m; ++i) {
		int op; read >> op;
		if (op == 1) {
			int l, r, x;
			read >> l >> r >> x;
			for (int j = l; j <= r; ++j) {
				stk[j][++top[j]] = x;
			}
		}
		else if (op == 2) {
			int l, r;
			read >> l >> r;
			for (int j = l; j <= r; ++j)
				if (top[j]) --top[j];
		}
		else {
			int pos, k;
			read >> pos >> k;
			if (top[pos] < k) puts("Error");
			else {
				printf("%d\n", stk[pos][top[pos] - k + 1]);
			}
		}
	}
	return 0;
}
