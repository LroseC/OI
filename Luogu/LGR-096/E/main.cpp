#include <queue>
#include <cctype>
#include <cstdio>

using namespace std;

template<typename T = int>
inline T read(void)
{
	T res = 0, f = 1; char ch = getchar();
	while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
	while (isdigit(ch)) { res = res * 10 + ch - '0'; ch = getchar(); }
	return res * f;
}

int n;
priority_queue<int> heap;

int main(void)
{
	n = read();
	int t = n / 3;
}