#include <vector>
#include <cctype>
#include <cstdio>
#include <utility>
#include <algorithm>

struct FSI
{
	template<typename T>
	FSI& operator>>(T &res)
	{
		res = 0; T f = 1; char ch = getchar();
		while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
		while (isdigit(ch)) { res = res * 10 + ch - '0'; ch = getchar(); }
		res = res * f; return *this;
	}
} read;

const int N = 2e5 + 10, mod = 1e9 + 7;
inline int lowbit(int x) { return x & -x; }
inline int Mod(int x) { return x >= mod ? x - mod : x; }

int n;
std::vector< std::pair<int, int> > person, line;
int L[N], R[N];
int tr[N + 10];

void add(int x, int val)
{
	x += 5;
	for (int i = x; i < N + 10; i += lowbit(i))
		tr[i] = Mod(tr[i] + val);
}
int query(int x)
{
	int res = 0; x += 5;
	for (int i = x; i; i -= lowbit(i))
		res = Mod(res + tr[i]);
	return res;
}

int main(void)
{
	read >> n;
	person.resize(n);
	std::vector<int> nums(n);
	for (int i = 0; i < n; ++i) {
		read >> person[i].first >> person[i].second;
		nums[i] = person[i].second;
	}
	std::sort(nums.begin(), nums.end());
	std::sort(person.begin(), person.end());
	nums.erase(std::unique(nums.begin(), nums.end()), nums.end());
	for (int i = 0; i < n; ++i)
		person[i].second = std::lower_bound(nums.begin(), nums.end(), person[i].second) - nums.begin();
	int tmp = 0;
	for (int i = 0; i < n; ++i) {
		tmp = std::max(tmp, person[i].second); R[i] = tmp;
	}
	tmp = n;
	for (int i = n - 1; i >= 0; --i) {
		tmp = std::min(tmp, person[i].second); L[i] = tmp;
	}
	line.resize(n);
	for (int i = 0; i < n; ++i)
		line[i] = std::make_pair(L[i] + 1, R[i] + 1);
	add(0, 1);
	for (int i = 0, j = 0; i < n; ++i) {
		int l = line[i].first, r = line[i].second;
		add(r, Mod(query(r) - query(l - 2) + mod));
	}
	printf("%d\n", Mod(query(n) - query(n - 1) + mod));
	return 0;
}
