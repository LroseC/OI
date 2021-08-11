#include <cstdio>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

string origin, str;

int main(void)
{
	int n = 0;
	char ch;
	do {
		ch = getchar();
		if (ch >= 'a' && ch <= 'z') ch -= ' ';
		if (ch != '\n') origin.push_back(ch);
	} while (ch != '\n');

	int i = 0;
	int ans = -1, cnt = 0;
	do {
		ch = getchar();
		if (ch >= 'a' && ch <= 'z') ch -= ' ';
		if (ch == ' ' || ch == '\n') {
			if (str == origin)
				if (++cnt == 1)
					ans = i - str.size();
			str.clear();
		}
		else str.push_back(ch);
		++i;
	} while (ch != '\n');
	if (ans == -1) puts("-1");
	else printf("%d %d\n", cnt, ans);
	return 0;
}