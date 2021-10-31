#include <vector>
#include <cctype>
#include <cstdio>

using namespace std;

const int N = 5e3 + 10;

template<typename T = int>
T read(void)
{
	T res = 0, f = 1; char ch = getchar();
	while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
	while (isdigit(ch)) { res = res * 10 + ch - '0'; ch = getchar(); }
	return res * f;
}

int n;
char str[N];
vector<int> dif;

int main(void)
{
	n = read();
	scanf("%s", str + 1);
	for (int i = 1; i < n; ++i)
		if (str[i] == str[i + 1])
			dif.emplace_back(i);
	
	printf("%d\n", (dif.size() + 1) / 2);
	for (int i = 0; i < dif.size(); i += 2) {
		if (dif.size() - i == 1) {
			int now = dif[i] + 1;
			char ans;
			for (char ch = 'A'; ch <= 'C'; ++ch) {
				if ((now == 0 || str[now - 1] != ch) && (now == n || str[now + 1] != ch)) {
					ans = ch;
					break;
				}
			}
			printf("%d %d %c%c%c\n", now, now, ans, ans, ans);
		}
		else {
			int n1 = dif[i] + 1, n2 = dif[i + 1];
			printf("%d %d BCA", n1, n2);
			putchar('\n');
		}
	}
	return 0;
}