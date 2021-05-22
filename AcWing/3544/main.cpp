#include <cstdio>
#include <string>
#include <iostream>

using namespace std;

int T;
int n;
int cnt;
string str;

int main()
{
	scanf("%d", &T);
	while (T--) {
		str.clear();
		bool flag = 0;
		while (1) {
			char ch = getchar();
			if (flag && ch == '\n') break;
			if (ch == '1' || ch == '0') flag = 1;
			if (ch == '1') {
				++cnt;
				str.push_back(ch);
			}
			else {
				if (cnt >= 5) {
					cnt = 0;
					continue;
				}
				str.push_back(ch);
				cnt = 0;
			}
		}
		cout << str << endl;
	}
	return 0;
}
