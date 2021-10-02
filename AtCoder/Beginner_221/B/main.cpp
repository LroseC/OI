#include <vector>
#include <cstdio>
#include <string>
#include <cstring>
#include <iostream>

using namespace std;

string a, b;

int main(void)
{
	cin >> a >> b;
	if (a == b) {
		puts("Yes");
		return 0;
	}
	else {
		vector<int> dif;
		for (int i = 0; i < a.size(); ++i)
			if (a[i] != b[i]) dif.emplace_back(i);
		if (dif.size() >= 2 && (dif[0] - dif[1] == 1 || dif[0] - dif[1] == -1)) swap(a[dif[0]], a[dif[1]]);
		if (a == b) puts("Yes");
		else puts("No");
	}
	return 0;
}