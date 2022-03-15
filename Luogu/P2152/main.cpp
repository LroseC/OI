#include <bits/stdc++.h>

using namespace std;

typedef long long LL;
const int BASE = 1e9;

class BigInt
{
private:
	int len;
	vector<int> val;
	void maintain(void)
	{
		len = val.size();
		for (int i = len - 1; i >= 0; --i) {
			if (val[i]) break; --len;
		}
		val.resize(len);
	}
	int& operator[](int x)
	{
		return val[x];
	}
public:
	BigInt(void) { len = 0; }
	BigInt(int l) { len = l; val.resize(l); }
	void read(void)
	{
		len = 0; val.resize(len);
		static char buf[(int)1e4 + 10]; int p = 0;
		buf[0] = getchar();
		while (!isdigit(buf[0])) buf[0] = getchar();
		while (isdigit(buf[p])) buf[++p] = getchar(); --p;
		for (int i = p; i >= 0; i -= 9) {
			++len; val.emplace_back(0);
			for (int j = 0, num = 1; j < 9; ++j, num *= 10) {
				if (i - j < 0) break;
				val[len - 1] += (buf[i - j] - '0') * num;
			}
		}
	}
	void print(char end = '\n')
	{
		if (!len) putchar('0');
		else {
			printf("%d", val[len - 1]);
			for (int i = len - 2; i >= 0; --i)
				printf("%09d", val[i]);
		}
		putchar(end);
	}
	friend bool operator<(BigInt &a, BigInt &b);
	friend BigInt operator-(BigInt &a, BigInt &b);
	friend BigInt operator*(BigInt &a, int x);
	friend BigInt operator/(BigInt &a, int x);
	friend BigInt gcd(BigInt a, BigInt b);
};

bool operator<(BigInt &a, BigInt &b)
{
	if (a.len < b.len) return 1;
	if (a.len > b.len) return 0;
	for (int i = a.len - 1; i >= 0; --i) {
		if (a[i] < b[i]) return 1;
		if (a[i] > b[i]) return 0;
	}
	return 0;
}
BigInt operator-(BigInt &a, BigInt &b)
{
	BigInt res(a.len + 1);
	b.len = a.len;
	b.val.resize(a.len);
	for (int i = 0; i < a.len; ++i) {
		res[i] += a[i] - b[i];
		if (res[i] < 0) {
			res[i] += BASE;
			--res[i + 1];
		}
	}
	b.maintain();
	res.maintain(); return res;
}
BigInt operator*(BigInt &a, int x)
{
	BigInt res(a.len + 1);
	for (int i = 0; i < a.len; ++i) {
		LL tmp = a[i] * x + res[i];
		res[i] = tmp % BASE;
		res[i + 1] += tmp / BASE;
	}
	res.maintain(); return res;
}
BigInt operator/(BigInt &a, int x)
{
	BigInt res(a.len);
	LL tmp = 0;
	for (int i = a.len - 1; i >= 0; --i) {
		tmp += a[i];
		res[i] = tmp / x;
		tmp = (tmp % x) * BASE;
	}
	res.maintain(); return res;
}

BigInt gcd(BigInt a, BigInt b)
{
	int cnt = 0;
	while (b.len) {
		if (a < b) { swap(a, b); continue; }
		if ((a[0] & 1) && (b[0] & 1)) a = a - b;
		else if (a[0] & 1) b = b / 2;
		else if (b[0] & 1) a = a / 2;
		else a = a / 2, b = b / 2, ++cnt;
	}
	while (cnt--) a = a * 2;
	return a;
}

int main(void)
{
	BigInt a, b;
	a.read(), b.read();
	BigInt c = gcd(a, b);
	c.print();
	return 0;
}