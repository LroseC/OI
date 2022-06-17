#include <set>
#include <cctype>
#include <cstdio>
#include <unordered_map>

struct FSI
{
	template<typename T>
	FSI& operator>>(T &res)
	{
		res = 0; T f = 1; char ch = getchar();
		while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
		while (isdigit(ch)) { res = res * 10 + (ch - '0') * f; ch = getchar(); }
		return *this;
	}
} read;

using i64 = long long;

int n, mod;
std::multiset<int> num, res;
std::unordered_map<int, int> pr;

int getAns(int x)
{
	auto it = num.lower_bound(mod - x);
	if (it == num.begin()) return -1;
	--it;
	if (*it == x && num.count(x) == 1) {
		if (it == num.begin()) return -1;
		return *(--it);
	}
	return *it;
}
void insert(int x)
{
	num.insert(x);
	int y = getAns(x), z = getAns(y), w = getAns(z);
	if (y == -1) return;
	if (z < x) {
		if (w == y && z != -1)
			res.erase(res.find(y + z));
		res.insert(x + y);
	}
}
void erase(int x)
{
	int y = getAns(x), z = getAns(y), w = getAns(z);
	if (y == -1) return;
	if (z < x) {
		res.erase(res.find(x + y));
		if (w == y && z != -1)
			res.insert(y + z);
	}
}
int query(void)
{
	auto it = num.end();
	int ans = 0;
	for (int i = 0; i < 2; ++i)
		ans += *(--it);
	ans %= mod;
	auto jt = res.end();
	if (jt != res.begin())
		ans = std::max(ans, *(--jt));
	return ans;
}

int main(void)
{
	read >> n >> mod;
	for (int T = 1, lastans = 0; T <= n; ++T) {
		int op, x;
		read >> op >> x;
		x ^= lastans;
		if (op == 1) {
			insert(x % mod);
		}
		else {
			erase(x % mod);
		}
		if (num.size() < 2) {
			puts("EE");
			lastans = 0;
		}
		else {
			printf("%d\n", lastans = query());
		}
	}
	return 0;
}
