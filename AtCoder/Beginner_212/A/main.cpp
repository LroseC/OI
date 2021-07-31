#include <cstdio>
#include <iostream>

using namespace std;

int a, b;

int main(void)
{
	cin >> a >> b;
	if (a && b) puts("Alloy");
	else if (a) puts("Gold");
	else if (b) puts("Silver");
	return 0;
}
