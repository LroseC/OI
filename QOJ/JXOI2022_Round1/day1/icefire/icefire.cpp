#include <vector>
#include <cctype>
#include <cstdio>
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

using i64 = long long;

const int N = 2e6 + 10;
inline int lowbit(int x) { return x & -x; }

struct Change
{
	int op;
	int type, tem, v;
	int k;

	Change(void) {}
	Change(int _op, int _t, int _tem, int _v)
	{
		op = _op, type = _t, tem = _tem, v = _v;
	}
	Change(int _op, int _k)
	{
		op = _op, k = _k;
	}
};

int m;
std::vector<int> nums;
int tr[2][N];
Change cg[N];

void add(int type, int x, int v)
{
	x += 2;
	if (type == 0)
		for (int i = x; i < N; i += lowbit(i))
			tr[type][i] += v;
	else
		for (int i = x; i; i -= lowbit(i))
			tr[type][i] += v;
}
int query(int type, int x)
{
	x += 2;
	int res = 0;
	if (type == 0)
		for (int i = x; i; i -= lowbit(i))
			res += tr[type][i];
	else
		for (int i = x; i < N; i += lowbit(i))
			res += tr[type][i];
	return res;
}
int getAns(int pos) { return std::min(query(0, pos), query(1, pos)) * 2; }
std::pair<int, int> calc(void)
{
	int l = 0, r = nums.size() - 1;
	while (l < r) {
		int mid = l + r + 1 >> 1;
		if (query(0, mid) <= query(1, mid)) l = mid;
		else r = mid - 1;
	}
	int left = l;
	int maxans = getAns(l);
	l = 0, r = nums.size() - 1;
	while (l < r) {
		int mid = l + r >> 1;
		if (query(0, mid) > query(1, mid)) r = mid;
		else l = mid + 1;
	}
	maxans = std::max(maxans, getAns(l));
	l = left, r = nums.size() - 1;
	while (l < r) {
		int mid = l + r + 1 >> 1;
		if (getAns(mid) >= maxans) l = mid;
		else r = mid - 1;
	}
	return std::make_pair(l, getAns(l));
}

int main(void)
{
//	freopen("icefire.in", "r", stdin);
//	freopen("icefire.out", "w", stdout);
	read >> m;
	for (int tim = 1; tim <= m; ++tim) {
		int op; read >> op;
		if (op == 1) {
			int type, tem, v;
			read >> type >> tem >> v;
			nums.emplace_back(tem);
			cg[tim] = Change(op, type, tem, v);
		}
		else {
			int k;
			read >> k;
			cg[tim] = Change(op, k);
		}
	}
	std::sort(nums.begin(), nums.end());
	nums.erase(std::unique(nums.begin(), nums.end()), nums.end());

	for (int tim = 1; tim <= m; ++tim) {
		if (cg[tim].op == 1) {
			cg[tim].tem = std::lower_bound(nums.begin(), nums.end(), cg[tim].tem) - nums.begin();
			add(cg[tim].type, cg[tim].tem, cg[tim].v);
		}
		else {
			int k = cg[tim].k;
			add(cg[k].type, cg[k].tem, -cg[k].v);
		}
		auto res = calc();
		if (res.second == 0)
			puts("Peace");
		else
			printf("%d %d\n", nums[res.first], res.second);
	}
	return 0;
}
