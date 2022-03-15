#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 2e4 + 10;
inline int lowbit(int x) { return x & -x; }

int vis[N];
string str[N];

void Print(int x)
{
	if (vis[x]) return;
	vis[x] = 1;
	if (x == lowbit(x)) {
		for (int i = 16; i >= 0; --i)
			if (x >> i & 1) {
				Print(i);
				str[x] = "2(" + str[i] + ")";
			}
		return;
	}
	for (int i = 16, flag = 0; i >= 0; --i)
		if (x >> i & 1) {
			if (flag) str[x] += "+";
			else flag = 1;
			Print(1 << i);
			str[x] += str[1 << i];
		}
}

int main(void)
{
	int x;
	cin >> x;
	str[1] = "2(0)";
	str[2] = "2";
	vis[1] = vis[2] = 1;
	Print(x);
	cout << str[x];
	// for (int i = 11,flag = 0; i >= 0; --i) {
		// if ((x >> i) & 1) {
			// if (flag) cout << '+';
			// else flag = 1;
			// cout << str[i];
		// }
	// }
	cout << '\n';
	return 0;
}