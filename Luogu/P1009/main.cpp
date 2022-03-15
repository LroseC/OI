#include <vector>
#include <iostream>

using namespace std;

int n;

struct bigint
{
	int sz;
	vector<int> a;
	void init(int x)
	{
		sz = 1;
		a.emplace_back(x);
	}
	void print(void)
	{
		for (int i = a.size() - 1; i >= 0; --i) cout << a[i];
		cout << endl;
	}
};
bigint operator*(int x, const bigint &sec)
{
	bigint ans = sec;
	ans.sz += 3;
	ans.a.resize(ans.sz);
	for (auto &y : ans.a) y *= x;
	for (int i = 0; i < ans.sz - 1; ++i) {
		ans.a[i + 1] += ans.a[i] / 10;
		ans.a[i] %= 10;
	}
	while (!ans.a[ans.sz - 1]) --ans.sz;
	ans.a.resize(ans.sz);
	return ans;
}
bigint operator+(const bigint &fir, const bigint &sec)
{
	bigint ans = fir;
	auto &a = ans.a;
	auto &sz = ans.sz;
	sz = max(fir.sz, sec.sz) + 1;
	a.resize(sz);
	for (int i = 0; i < min(sz, sec.sz); ++i)
		a[i] += sec.a[i];
	for (int i = 0; i < sz - 1; ++i) {
		a[i + 1] += a[i] / 10;
		a[i] %= 10;
	}
	while (!a[sz - 1]) --sz;
	a.resize(sz);
	return ans;
}

bigint a, b;

int main(void)
{
	ios::sync_with_stdio(0);
	cin >> n;
	a.init(0);
	b.init(1);
	for (int i = 1; i <= n; ++i) {
		b = i * b;
		a = a + b;
	}
	a.print();
	return 0;
}