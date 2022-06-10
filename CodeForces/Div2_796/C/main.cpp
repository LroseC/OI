#include <cctype>
#include <cstdio>

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
const int N = 1e6 + 10;

int n;
int cnt[1010];
char str[N];

int main(void)
{
	int tt; read >> tt;
	while (tt--) {
		read >> n;
		for (int i = 1; i <= n * 2; ++i) {
			scanf("%s", str + 1);
			for (int j = 1; str[j]; ++j)
				cnt[str[j]] ^= 1;
		}
		scanf("%s", str + 1);
		for (int j = 1; str[j]; ++j)
			cnt[str[j]] ^= 1;
		for (int i = 'a'; i <= 'z'; ++i) {
			if (cnt[i]) {
				cnt[i] = 0;
				printf("%c\n", i);
				break;
			}
		}
	}
	return 0;
}
