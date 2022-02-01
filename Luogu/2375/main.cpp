#include <cctype>
#include <cstdio>
#include <cstring>

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
} read;

const int N = 1e6 + 10, mod = 1e9 + 7;

int n;
int nex[N], cnt[N], ans[N];
char str[N];

int main(void)
{
	int T;
	read >> T;
	while (T--) {
		scanf("%s", str);
		n = strlen(str);
		for (int i = 1, j = 0; i < n; ++i) {
			while (j && str[i] != str[j])
				j = nex[j - 1];
			if (str[i] == str[j])
				++j;
			nex[i] = j;
			ans[j] = ans[nex[j - 1]] + 1;
		}
		for (int i = 1, j = 0; i < n; ++i) {
			while (j && str[i] != str[j])
				j = nex[j - 1];
			if (str[i] == str[j])
				++j;
			while (
	return 0;
}
