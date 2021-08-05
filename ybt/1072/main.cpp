#include <cmath>
#include <cstdio>
#include <iostream>

using namespace std;

int n;
double origin;
double a, b;
double f[100];

int main(void)
{
	cin >> n;
	cin >> a >> b;
	origin = b / a;
	for (int i = 1; i < n; ++i) cin >> a >> b, f[i] = b / a;
	for (int i = 1; i < n; ++i) {
		if (f[i] - origin > 0.05) puts("better");
		else if (origin - f[i] > 0.05) puts("worse");
		else puts("same");
	}
	return 0;
}