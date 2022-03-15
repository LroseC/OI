#include <cstdio>

using namespace std;

extern "C" int Seniorious(int);

extern "C" int Chtholly(int n, int OvO)
{
	int l = 1, r = n;
	while (l < r) {
		int mid = l + r + 1 >> 1;
		if (Seniorious(mid) <= 0)
			l = mid;
		else r = mid - 1;
	}
	return l;
}
