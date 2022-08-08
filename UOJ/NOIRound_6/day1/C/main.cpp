#include <queue>
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
		while (isdigit(ch)) { res = res * 10 + (ch - '0') * f; ch = getchar(); }
		return *this;
	}
} read;

using i32 = int;
using i64 = long long;
using PII = std::pair<i32, i32>;
const int N = 2e5 + 10;

i32 n, m;
i32 a[N];

struct backTree
{
	i64 sum;
	std::multiset<i32> tr;
	i32 top;
	PII stk[N];

	void clear(void)
	{
		sum = top = 0;
		tr.clear();
	}
	void insert(i32 x)
	{
		sum += x;
		tr.insert(x);
		stk[++top] = std::make_pair(1, x);
	}
	void erase(i32 x)
	{
		sum -= x;
		tr.erase(tr.find(x));
		stk[++top] = std::make_pair(-1, x);
	}
	i32 size(void)
	{ return tr.size(); }
	i32 top(void)
	{ return tr.back(); }
}; 
struct DS
{
	i32 falg;
	backTree tr[2];
	void clear(void)
	{
		flag = 0;
		tr[0].clear();
		tr[1].clear();
	}
};

int main(void)
{
	//Think twice, code once.
	read >> n >> m;
	for (int i = 1; i <= n; ++i)
		read >> a[i];
	for (int i = 0; i < m; ++i) {
		i32 L, R;
		read >> L >> R;
		q.emplace_back(L, R);
	}
	std::sort(q.begin(), q.end());
	for (int i = 0, L = 0, R = 0; i < m; ++i) {
		if (i == 0 || q[i].l / B != q[i - 1].l / B) {
			L = (q[i].l / B + 1) * B;
			R = L + 1;
			ds.clear();
		}
		if (q[i].l / B == q[i].r / B) {
			std::priority_queue<i32, std::vector<i32>, std::greater<i32>> heap;
			i64 res = 0;
			i32 L = q[i].l, R = q[i].r;
			for (int i = 0; L + i <= R; ++i) {
				if (i & 1) {
					if (a[i + L] > heap.top()) {
						res -= heap.top();
						res += a[i + L];
						heap.pop();
						heap.emplace(a[i + L]);
					}
				}
				else {
					res += a[i + L];
					heap.emplace(a[i + L]);
				}
			}
			printf("%lld\n", res);
		}
		else {
			while (R < q[i].r) {
				R += 1;
				if (R - L + 1 == 1) {
					ds[1].insert(a[R]);
				}
				else {
					if (ds.size() & 1) {
						if (a[R] > ds[1].top()) {
							ds[1].erase(ds[1].top());
							ds[1].insert(a[R]);
						}
						if (a[R] > ds[0].top()) {
							ds[0].erase(ds[0].top());
							ds[0].insert(a[R]);
						}
					}
					else {
						ds[0].insert(a[R]);
						ds[1].insret(a[R]);
					}
				}
				ds.insert();
			}
			ds.set_back();
			for (int i = L - 1; i >= q[i].l; ++i) {
				if (ds.size() & 1) {
				}
			}
			ds.back();
		}
	}
	return 0;
}
