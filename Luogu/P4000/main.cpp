#include <map>
#include <cstdio>
#include <random>
#include <cstring>
#include <iostream>
#include <unordered_map>

using namespace std;

const int N = 3e7 + 10;
const int BL = 1 << 18;
int mod;
using LL = long long;
using ULL = unsigned long long;

struct Matrix
{
	int r, c;
	int num[2][2];
	int* operator[](int x) { return num[x]; }
	friend void print(Matrix &a)
	{
		for (int i = 0; i < a.r; ++i, puts(""))
			for (int j = 0; j < a.c; ++j)
				printf("%d ", a[i][j]);
	}
	friend Matrix operator*(Matrix &a, Matrix &b)
	{
		Matrix res;
		res.r = a.r, res.c = b.c;
		memset(res.num, 0, sizeof res.num);
		for (int i = 0; i < a.r; ++i)
			for (int j = 0; j < b.c; ++j)
				for (int k = 0; k < a.c; ++k) {
					res[i][j] = (res[i][j] + 1ll * a[i][k] * b[k][j]) % mod;
				}
		return res;
	}
} BASE[2][BL];
unordered_map<ULL, LL> M;
char str[N];

mt19937_64 basic_rd(time(NULL));
LL rd(void)
{
	return basic_rd() & ((1ll << 36) - 1);
}

int init_BASE(void)
{
	//init BASE[0]
	auto &x = BASE[0][0];
	x.r = x.c = 2;
	x[0][0] = x[1][1] = 1;
	x[1][0] = x[0][1] = 0;
	auto &y = BASE[0][1];
	y.r = y.c = 2;
	y[0][0] = 0;
	y[1][0] = y[0][1] = y[1][1] = 1;
	for (int i = 2; i < BL; ++i)
		BASE[0][i] = BASE[0][i - 1] * BASE[0][1];

	//init BASE[1]
	BASE[1][0] = BASE[0][0];
	BASE[1][1] = BASE[0][BL - 1] * BASE[0][1];
	for (int i = 2; i < BL; ++i)
		BASE[1][i] = BASE[1][i - 1] * BASE[1][1];
	return 0;
}
pair<int, int> calc(LL x)
{
	--x;
	Matrix res;
	res.r = 1, res.c = 2;
	res[0][0] = res[0][1] = 1;
	auto ma = BASE[1][x / BL] * BASE[0][x % BL];
	res = res * ma;
	return make_pair(res[0][0], res[0][1]);
}
int main(void)
{
	scanf("%s", str + 1);
	cin >> mod;
	init_BASE();
	LL len;
	while (1) {
		LL pos = rd();
		auto t = calc(pos);
		ULL a = (ULL)t.first << 32 | t.second;
		if (M.count(a)) {
			len = abs(M[a] - pos);
			break;
		}
		M[a] = pos;
	}
	LL n = 0;
	for (int i = 1; str[i]; ++i)
		n = (n * 10 + str[i] - '0') % len;
	auto t = calc(n);
	printf("%d\n", t.first);
	return 0;
}
