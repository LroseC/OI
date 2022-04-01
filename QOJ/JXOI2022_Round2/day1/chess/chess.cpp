#include <map>
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

using i64 = long long;

int n, m;
i64 pwm[20];
int A[20][20], B[20][20];
std::map<i64, int> f;

inline int getCnt(i64 state, int x)
{
	return state / pwm[x] % (m + 1);
}
int dp(i64 state)
{
	if (f.count(state))
		return f[state];
	int cnt = 0;
	for (int i = 0; i < n; ++i)
		cnt += getCnt(state, i);
	bool flag = cnt & 1;
	int res = flag ? 0xcfcfcfcf : 0x3f3f3f3f;
	for (int i = 0; i < n; ++i)
		if (getCnt(state, i) != m) {
			i64 tostate = state + pwm[i];
			if (i == 0 || getCnt(tostate, i - 1) >= getCnt(tostate, i)) {
				if (flag)
					res = std::max(res, dp(tostate) + A[i][getCnt(state, i)]);
				else
					res = std::min(res, dp(tostate) - B[i][getCnt(state, i)]);
			}
		}
	return f[state] = res;
}

int main(void)
{
//	freopen("chess.in", "r", stdin);
//	freopen("chess.out", "w", stdout);
	read >> n >> m;
	pwm[0] = 1;
	for (int i = 1; i < n; ++i)
		pwm[i] = pwm[i - 1] * (m + 1);
	for (int i = 0; i < n; ++i)
		for (int j = 1; j <= m; ++j)
			read >> A[i][j];
	for (int i = 0; i < n; ++i)
		for (int j = 1; j <= m; ++j)
			read >> B[i][j];
	i64 state = 0;
	for (int i = 0; i < n; ++i)
		state += pwm[i] * m;
	int cnt = 0;
	for (int i = 0; i < n; ++i)
		cnt += getCnt(state, i);
	f[state] = (cnt & 1) ? A[n - 1][m] : -B[n - 1][m];
	printf("%d\n", dp(0));
	return 0;
}
