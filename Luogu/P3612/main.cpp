#include <cstring>
#include <iostream>

using namespace std;

typedef long long LL;

LL n;
LL len;
char str[1000];

char get(LL x)
{
	if (x <= len) return str[x];
	int bit = 1;
	while (x > (len << bit)) ++bit;
	--bit;
	x -= len << bit;
	--x;
	if (x < 1) x = len << bit;
	return get(x);
}

int main(void)
{
	cin >> str + 1 >> n;
	len = strlen(str + 1);
	cout << get(n) << endl;
	return 0;
}