#include <map>
#include <cstdio>

using namespace std;

int x, y;
map<int, char> mp;

void Print(int x)
{
	if (!x) return;
	Print(x / y);
	printf("%c", mp[x % y]);
}

int main(void)
{
	for (int i = 0; i < 10; ++i) mp[i] = i + '0';
	for (int i = 10; i < 16; ++i) mp[i] = i + 'A' - 10;
	scanf("%d%d", &x, &y);
	Print(x);
}