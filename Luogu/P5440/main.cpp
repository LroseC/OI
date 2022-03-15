#include <vector>
#include <iostream>

using namespace std;

int T;
vector<int> a, nums;
char str[110];
int prime[] = {0, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
int d[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

bool is_prime(int x)
{
	for (int i = 2; i * i <= x; ++i)
		if (!(x % i))
			return 0;
	return 1;
}

int main(void)
{
	ios::sync_with_stdio(0);
	for (int i = 1; i <= 12; ++i)
		for (int j = 1; prime[j] <= d[i]; ++j)
			if (is_prime(i * 100 + prime[j]))
				a.emplace_back(i * 100 + prime[j]);
	for (int i = 4; i < 1e4; i += 4)
		if ((i % 100) || !(i % 400))
			if (is_prime(i * 1e4 + 229))
				nums.emplace_back(i * 1e4 + 229);
	for (int i = 1; i < 1e4; ++i)
		for (auto x : a)
			if (is_prime(i * 1e4 + x))
				nums.emplace_back(i * 1e4 + x);
	
	cin >> T;
	while (T--) {
		int ans = 0;
		cin >> str + 1;
		for (auto x : nums) {
			bool flag = 0;
			for (int i = 8; i; --i, x /= 10)
				if (str[i] - '0' != (x % 10) && str[i] != '-') {
					flag = 1;
					break;
				}
			if (flag) continue;
			++ans;
		}
		cout << ans << '\n';
	}
	return 0;
}