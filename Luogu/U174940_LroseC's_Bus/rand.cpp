#include <random>
#include <iostream>

using namespace std;

int n, m;

int main(void)
{
	ios::sync_with_stdio(false);
	n = 10, m = 10;
	cout << n << endl;
	for (int i = 1; i <= 10; ++i) {
		int u = myrand(1, 20), v = myrand(1, 20);
		int tx = myrand(1, 10), ty = myrand(1, 10);
		cout << u << ' ' << v << ' ' << tx << ' ' << ty << endl;
	}
	cout << m << endl;
	for (int i = 1; i <= 10; ++i) {
		int X = myrand(1, 10), Y = myrand(1, 20);
		cout << X << ' ' << Y << endl;
	}
	return 0;
}