#include <cctype>
#include <cstdio>
#include <cstring>

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

const int N = 2e5 + 10;

char str[N];
int cnt[26];

int main(void)
{
	int T; read >> T;
	while (T--) {
		scanf("%s", str + 1);
		std::memset(cnt, 0, sizeof cnt);
		int n = std::strlen(str + 1);
		for (int i = 1; str[i]; ++i)
			++cnt[str[i] - 'a'];
		for (int i = 1; str[i]; ++i) {
			if (cnt[str[i] - 'a'] == 1) {
				printf("%s\n", str + i);
				break;
			}
			--cnt[str[i] - 'a'];
		}
	}
	return 0;
}
