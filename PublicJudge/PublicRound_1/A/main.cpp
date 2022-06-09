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
const int N = 3e5 + 10;

int n;
int a[N], b[N], f[N];
int left[N][32];

inline int lowbit(int x) { return x & -x; }
inline int sign(int x)
{
	return x < 0 ? -1 : 1;
}
inline int getId(int x)
{
	if (x == 0)
		return 0;
	else
		return x / lowbit(x);
}
int calc(int L, int R)
{
	if (b[L] == 0) return 1;
	int minbi = 0x3f3f3f3f;
	for (int i = L; i <= R; ++i) {
		b[i] = lowbit(b[i]);
		minbi = std::min(minbi, b[i]);
	}
	for (int i = L; i <= R; ++i) {
		b[i] /= minbi;
	}
	for (int j = 0; j < 31; ++j)
		for (int i = L; i <= R; ++i) {
			left[i][j] = -1;
			if (b[i] == 1 << j)
				left[i][j] = i - 1;
			else if (left[i][j - 1] != -1 && left[i][j - 1] >= L)
				left[i][j] = left[left[i][j - 1]][j - 1];
		}
	f[L - 1] = 0;
	for (int i = L; i <= R; ++i) {
		f[i] = 0x3f3f3f3f;
		for (int j = 0; j < 31; ++j)
			if (left[i][j] != -1)
				f[i] = std::min(f[i], f[left[i][j]] + 1);
	}
	return f[R];
}

void work(void)
{
	read >> n;
	for (int i = 1; i <= n; ++i) {
		read >> a[i];
	}
	--n;
	for (int i = 1; i <= n; ++i) {
		b[i] = a[i + 1] - a[i];
	}
	int res = 0;
	for (int i = 1, j = 1; j <= n; ++j) {
		if (sign(b[i]) != sign(b[j]) || getId(b[i]) != getId(b[j])) {
			res += calc(i, j - 1);
			i = j;
		}
		if (j == n && i <= j)
			res += calc(i, j);
	}
	printf("%d\n", res + 1);
}

int main(void)
{
	int tt; read >> tt;
	while (tt--) {
		work();
	}
}
