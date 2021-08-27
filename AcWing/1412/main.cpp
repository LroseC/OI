#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 1010, M = 1010;

int n;
int MA[6][6] = 
{
	{1, 0, 1, 1, 0, 0},
	{0, 1, 0, 0, 1, 0},
	{0, 1, 0, 0, 1, 0},
	{0, 1, 0, 0, 1, 0},
	{1, 0, 1, 1, 0, 1},
	{0, 0, 0, 0, 1, 0},
};
int ans[N][6][M];
int res[M];

void add(int a[], int b[])
{
	for (int i = 0; i < M; ++i) a[i] += b[i];
	for (int i = 0; i < M - 1; ++i) {
		a[i + 1] += a[i] / 10;
		a[i] %= 10;
	}
}

int main(void)
{
	cin >> n;
	ans[1][1][0] = ans[1][4][0] = 1;
	for (int i = 2; i < n; ++i)
		for (int j = 0; j < 6; ++j)
			for (int k = 0; k < 6; ++k)
				if (MA[j][k])
					add(ans[i][k], ans[i - 1][j]);
	add(res, ans[n - 1][0]);
	add(res, ans[n - 1][4]);
	add(res, res);
	

	int k = M - 1;
	while (k && !res[k]) --k;
	for (int i = k; i >= 0; --i) cout << res[i];
	cout << endl;
	return 0;
}