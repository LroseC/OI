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
const int N = 2e6 + 10;

int n, m, K;
char str[N];
int setFlag[N];

int main(void)
{
//	freopen("operation.in", "r", stdin);
//	freopen("operation.out", "w", stdout);
	read >> n >> K >> m;
	scanf("%s", str + 1);
	for (int i = 1; i <= n; ++i)
		str[i] -= '0';
	for (int TIME = 1; TIME <= m; ++TIME) {
		int l, r; read >> l >> r;
		int flag = 0, res = 0;
		for (int i = l; i <= r; ++i) {
			flag ^= setFlag[i];
			int nval = str[i] ^ flag;
			if (nval) {
				if (i + K - 1 <= r) {
					++res;
					flag ^= 1;
					if (i + K <= r)
						setFlag[i + K] ^= 1;
				}
				else {
					res = -1;
					break;
				}
			}
		}
		for (int i = l; i <= r; ++i)
			setFlag[i] = 0;
		printf("%d\n", res);
	}
	return 0;
}
