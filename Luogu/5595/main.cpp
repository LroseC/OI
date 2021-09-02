#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

int len;
char str[1000010];
char ans1[1000010], ans2[1000010];

int main(void)
{
	ios::sync_with_stdio(0);
	cin >> str + 1;
	len = strlen(str + 1);
	reverse(str + 1, str + 1 + len);
	int i = 1;
	while (str[i] == 'Z' && i <= len) ans1[i] = ans2[i] = '0', ++i;
	while (i <= len) {
		if (str[i] == 'Z') {
			cout << -1 << endl;
			return 0;
		}
		ans1[i] = '0' + (str[i] == 'X');
		ans2[i] = '0' + (str[i] == 'Y');
		++i;
	}
	reverse(ans1 + 1, ans1 + 1 + len);
	reverse(ans2 + 1, ans2 + 1 + len);
	cout << ans1 + 1 << '\n' << ans2 + 1 << endl;
	return 0;
}