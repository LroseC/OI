#include <cctype>
#include <cstdio>

using namespace std;

struct FastStreamInput
{
	using FSI = FastStreamInput;
	template<typename T>
	FSI& operator >> (T &res)
	{
		res = 0; T f = 1; char ch = getchar();
		while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
		while (isdigit(ch)) { res = res * 10 + ch - '0'; ch = getchar(); }
		res = res * f; return *this;
	}
} cin;

const int S = 1 << 18;
const int mod = 1e9 + 7;

inline int getbit(int x, int i) { return (x >> i - 1) & 1; }

int n, a, b, c;
int f[45][S];

inline bool check(int x)
{
	if (!getbit(x, c)) return 0;
	if (!getbit(x, b + c)) return 0;
	if (!getbit(x, a + b + c)) return 0;
	return 1;
}

int main(void)
{
	cin >> n >> a >> b >> c;
	f[0][0] = 1;
	for (int i = 0; i < n; ++i)
		for (int state = 0; state < S; ++state)
			for (int num = 1; num <= 10; ++num) {
				int to = ((state << num) | (1 << num - 1)) & (S - 1);
				if (!check(to)) f[i + 1][to] = (f[i + 1][to] + f[i][state]) % mod;
			}
	
	int ans = 1;
	for (int i = 0; i < n; ++i) ans = 10ll * ans % mod;
	for (int i = 0; i < S; ++i)
		ans = (ans - f[n][i] + mod) % mod;
	printf("%d\n", ans);
	return 0;
}