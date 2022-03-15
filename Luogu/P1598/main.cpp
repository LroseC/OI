#include <cctype>
#include <cstdio>
#include <algorithm>

using namespace std;

int cnt[26];
char s[4][110];

int main(void)
{
	for (char i = 1, ch; i <= 4; ++i)
		do {
			ch = getchar();
			if (isupper(ch)) ++cnt[ch - 'A'];
		}
		while (ch != '\n' && ch != -1);

	int n = 0;
	for (int i = 0; i < 26; ++i)
		n = max(n, cnt[i]);

	for (int i = n; i; --i, puts(""))
		for (int j = 0; j < 26; ++j, putchar(' '))
			putchar(cnt[j] >= i ? '*' : ' ');
	for (int j = 0; j < 26; ++j, putchar(' '))
		putchar('A' + j);
	return 0;
}