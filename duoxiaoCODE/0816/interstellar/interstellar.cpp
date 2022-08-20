#include <set>
#include <vector>
#include <cctype>
#include <cstdio>
#include <algorithm>
#include <functional>

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
using PII = std::pair<i32, i32>;
const int N = 1e5 + 10, mod = 998244353;
inline i32 Mod(i32 x) { return x >= mod ? x - mod : x; }

struct Number
{
	i32 tag;
	std::set<i64, std::greater<i64>> S;
	void insert(i64 x)
	{
		if (S.count(x - tag)) {
			S.erase(x - tag);
			insert(x + 1);
		}
		else {
			S.insert(x - tag);
		}
	}
	void merge(const Number &other)
	{
		for (auto v : other.S) {
			auto val = v + other.tag;
			insert(val);
		}
	}
	void clear()
	{
		tag = 0;
		S.clear();
	}
	void addtag(void)
	{ tag += 1; }
};

i32 n;
i32 sz[N], son[N], maxson[N];
Number num[N];
std::vector<std::pair<i32, i64>> G[N];

void getSz(i32 u)
{
	sz[u] = 1;
	for (auto e : G[u]) {
		i32 v = e.first;
		getSz(v);
		sz[u] += sz[v];
		if (sz[v] > sz[son[u]])
			son[u] = v;
	}
}
void getNum(i32 u, i32 tag, Number &num)
{
	for (auto e : G[u]) {
		i32 v = e.first;
		if (v != maxson[u]) {
			num.insert(e.second + tag);
			getNum(v, tag, num);
		}
		else {
			num.insert(e.second + tag + 1);
			getNum(v, tag + 1, num);
		}
	}
}
bool cmp(i32 u, i32 v)
{
	auto &a = num[u];
	auto &b = num[v];
	auto it = a.S.begin();
	auto jt = b.S.begin();
	while (true) {
		if (it == a.S.end()) return 0;
		if (jt == b.S.end()) return 1;
		if (*it + a.tag > *jt + b.tag) {
			return 1;
		}
		if (*it + a.tag < *jt + b.tag)
			return 0;
		++it, ++jt;
	}
	return 0;
}
void calc(i32 u, i32 type)
{
	for (auto e : G[u])
		if (e.first != son[u]) calc(e.first, 0);
	if (son[u]) calc(son[u], 1);
	maxson[u] = son[u];
	for (auto e : G[u]) {
		i32 v = e.first;
		if (v != son[u]) {
			getNum(v, 0, num[v]);
		}
		num[v].insert(e.second);
	}
	for (auto e : G[u]) {
		i32 v = e.first;
		if (v != son[u]) {
			if (cmp(v, maxson[u])) {
				maxson[u] = v;
			}
		}
	}
//	if (u == 1) {
//	for (auto e : G[u]) {
//		i32 v = e.first;
//		printf("num[%d]:\n", v);
//		for (auto val : num[v].S)
//			printf("%ld ", val + num[v].tag);
//		puts("");
//	}
//	}
	if (type == 1) {
		std::swap(num[u], num[son[u]]);
		if (son[u] == maxson[u]) {
			num[u].addtag();
		}
		for (auto e : G[u]) {
			i32 v = e.first;
			if (son[u] != v) {
				if (maxson[u] == v)
					num[v].addtag();
				num[u].merge(num[v]);
				num[v].clear();
			}
		}
	}
	else {
		for (auto e : G[u])
			num[e.first].clear();
	}
}
inline i32 qpow(i32 base, i64 k)
{
	i32 res = 1;
	while (k) {
		if (k & 1) res = 1ll * res * base % mod;
		k >>= 1;
		base = 1ll * base * base % mod;
	}
	return res;
}
i32 getAns(i32 u, i32 tag)
{
	i32 res = 0;
	for (auto e : G[u]) {
		i32 v = e.first;
		i64 w = e.second;
		if (v != maxson[u]) {
			res = Mod(res + qpow(2, w + tag));
			res = Mod(res + getAns(v, tag));
		}
		else {
			res = Mod(res + qpow(2, w + tag + 1));
			res = Mod(res + getAns(v, tag + 1));
		}
	}
	return res;
}

int main(void)
{
#ifndef DEBUG
	freopen("interstellar.in", "r", stdin);
	freopen("interstellar.out", "w", stdout);
#endif
	//Think twice, code once.
	read >> n;
	for (int i = 2; i <= n; ++i) {
		i32 u;
		i64 w;
		read >> u >> w;
		G[u].emplace_back(i, w);
	}
	getSz(1);
	calc(1, 1);
//	for (int i = 1; i <= n; ++i) {
//		printf("%d ", maxson[i]);
//	}
//	puts("");
	printf("%d\n", getAns(1, 0));
	return 0;
}
/*
   好像又只会一个 2log 做法, 无语.
   如果用 2log 做法, 大概我又会被卡常了把?
   链表好像也不大行, 这怎么搞?
   只能相信这个做法的常数了.
   输麻了, 每天 T1 都要挂分.
   我超, 我不会 dsu on tree 了? 怎么回事呢??????
   总算过拍随机树了...
   今天真别再挂分了...
*/
