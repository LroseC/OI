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
		res = res * f; return *this;
	}
} io;

int cnt[3];
char str[3][110];

int main(void)
{
	for (int i = 0; i < 3; ++i) {
		cnt[i] = 1;
		scanf("%s", str[i] + 1);
	}
	int u = 0;
	while (str[u][cnt[u]]) {
		++cnt[u];
		u = str[u][cnt[u] - 1] - 'a';
	}
	if (u == 0) puts("A");
	else if (u == 1) puts("B");
	else puts("C");
	return 0;
}