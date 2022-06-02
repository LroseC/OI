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
const int N = 2e5 + 10;

int n, K;
int fa[N];
char str[N];

int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
void work(void)
{
	read >> n >> K;
	scanf("%s", str + 1);
	for (int i = 'a'; i <= 'z'; ++i)
		fa[i] = i;
	for (int i = 1; i <= n; ++i) {
		while (find(str[i]) != 'a' && K) {
			int u = find(str[i]);
			fa[u] = u - 1;
			--K;
		}
	}
	for (int i = 1; i <= n; ++i)
		putchar(find(str[i]));
	putchar('\n');
}

int main(void)
{
	int T; read >> T;
	while (T--) work();
	return 0;
}
