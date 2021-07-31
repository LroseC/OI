#include <cstdio>
#include <iostream>

using namespace std;

char str[20];

bool check(void)
{
	for (int i = 1; i <= 4; ++i) str[i] -= '0';
	for (int i = 1; i < 4; ++i)
		if ((str[i] + 1) % 10 != str[i + 1]) return 0;
	return 1;
}

int main(void)
{
	scanf("%s", str + 1);
	if (str[1] == str[2] && str[2] == str[3] && str[3] == str[4])
		puts("Weak");
	else if(check())
		puts("Weak");
	else puts("Strong");

	return 0;
}
