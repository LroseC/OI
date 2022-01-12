#include <cctype>
#include <cstdio>

using namespace std;

struct FSI
{
	template<typename T>
	FSI& operator>>(T &res)
	{
		res = 0; T f = 1; char ch = getchar();
		while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
		while (isdigit(ch)) { res = res * 10 + ch - '0'; ch = getchar(); }
		res = res * f;
		return *this;
	}
} IO;

const int N = 110;

int n, len;
int a[N];
int cnt[2];

int main(void)
{
	int T; IO >> T;
	while (T--) {
		IO >> n >> len;
		for (int i = 1; i <= n; ++i)
			IO >> a[i];
		int res = 0;
		for (int digit = len; digit >= 0; --digit) {
			cnt[0] = cnt[1] = 0;
			for (int i = 1; i <= n; ++i)
				++cnt[a[i] >> digit & 1];
			if (cnt[1] > cnt[0])
				res |= 1 << digit;
		}
		printf("%d\n", res);
	}
	return 0;
}
