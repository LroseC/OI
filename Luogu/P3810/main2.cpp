#include <vector>
#include <cctype>
#include <cstdio>
#include <cstdint>
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

using i32 = int32_t;
using i64 = int64_t;
using u32 = uint32_t;
using u64 = uint64_t;
using vi32 = std::vector<i32>;
using PII = std::pair<i32, i32>;
const int N = 2e5 + 10;
inline i32 lowbit(i32 x) { return x & -x; }

struct Operation
{
	i32 x, y, z, id;
	Operation(void) {}
	Operation(i32 _x, i32 _y, i32 _z, i32 _id)
	{ x = _x, y = _y, z = _z, id = _id; }
	bool operator<(const Operation &other) const
	{ return x == other.x ? id < other.id : x < other.x; }
};
struct BIT
{
	i32 n, tick;
	std::vector<i32> tr;
	std::vector<i32> tim;
	void init(i32 _n)
	{
		n = _n;
		tr.resize(n + 1);
		tim.resize(n + 1);
	}
	void add(i32 x, i32 v)
	{
		for (int i = x; i <= n; i += lowbit(i)) {
			if (tim[i] != tick) {
				tr[i] = 0;
				tim[i] = tick;
			}
			tr[i] += v;
		}
	}
	i32 query(i32 x)
	{
		i32 res = 0;
		for (int i = x; i; i -= lowbit(i)) {
			if (tim[i] != tick) {
				tr[i] = 0;
				tim[i] = tick;
			}
			res += tr[i];
		}
		return res;
	}
	void clear(void) { tick += 1; }
};

i32 n, K;
BIT bit;
i32 res[N], ans[N];
std::vector<Operation> op, t;

void CDQ(i32 l, i32 r)
{
	if (l == r) return;
	i32 mid = l + r >> 1;
	CDQ(l, mid);
	CDQ(mid + 1, r);
	// printf("l = %d, r = %d\n", l, r);
	// puts("left:");
	// for (int i = l; i <= mid; ++i) {
	// 	printf("(%d %d %d) %d\n", op[i].x, op[i].y, op[i].z, op[i].id);
	// }
	// puts("right:");
	// for (int i = mid + 1; i <= r; ++i) {
	// 	printf("(%d %d %d) %d\n", op[i].x, op[i].y, op[i].z, op[i].id);
	// }
	i32 i = l, j = mid + 1, k = l;
	while (i <= mid && j <= r) {
		if (op[i].y <= op[j].y) {
			if (op[i].id == 0) bit.add(op[i].z, 1);
			t[k++] = op[i++];
		}
		else {
			if (op[j].id != 0) res[op[j].id] += bit.query(op[j].z);
			t[k++] = op[j++];
		}
	}
	while (i <= mid) t[k++] = op[i++];
	while (j <= r) {
		if (op[j].id != 0) res[op[j].id] += bit.query(op[j].z);
		t[k++] = op[j++];
	}
	for (int i = l; i <= r; ++i) op[i] = t[i];
	bit.clear();
}

int main(void)
{
	//Think twice, code once.
	read >> n >> K;
	bit.init(K);
	for (int i = 1; i <= n; ++i) {
		i32 x, y, z;
		read >> x >> y >> z;
		op.emplace_back(x, y, z, 0);
		op.emplace_back(x, y, z, i);
	}
	std::sort(op.begin(), op.end());
	t.resize(op.size());
	CDQ(0, op.size() - 1);
	for (int i = 1; i <= n; ++i) {
		ans[res[i]] += 1;
	}
	for (int i = 1; i <= n; ++i) {
		printf("%d\n", ans[i]);
	}
	return 0;
}
