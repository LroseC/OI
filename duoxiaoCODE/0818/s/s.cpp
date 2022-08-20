#include "s.hpp"
#include <vector>
#include <string>
#include <cctype>
#include <cstdio>
#include <cstdint>
#include <iostream>
#include <algorithm>

using i32 = int32_t;
using i64 = int64_t;
using PII = std::pair<i32, i32>;

std::vector<std::string> ans, v;

std::string operator-(const std::string &a, const std::string &b)
{
	std::string res = a;
	for (int i = 0; i < a.size(); ++i) {
		if (i < b.size()) res[i] -= b[i] - '0';
		if (res[i] < '0') {
			res[i] += 10;
			res[i + 1] -= 1;
		}
	}
	while (res.size() > 1 && res[res.size() - 1] == '0') res.pop_back();
	return res;
}
std::string operator*(const std::string &a, const std::string &b)
{
	std::vector<i32> res;
	res.resize(a.size() + b.size());
	for (int i = 0; i < a.size(); ++i) {
		for (int j = 0; j < b.size(); ++j)
			res[i + j] += (a[i] - '0') * (b[j] - '0');
		for (int j = 0; j < res.size(); ++j)
			if (res[j] > 10) {
				res[j + 1] += res[j] / 10;
				res[j] %= 10;
			}
	}
	while (res[res.size() - 1] == 0) res.pop_back();
	std::string ans;
	ans.resize(res.size());
	for (int i = 0; i < res.size(); ++i) ans[i] = res[i] + '0';
	return ans;
}

std::string Cut(i32 l, i32 r, const std::string &s)
{
	std::string res;
	for (int i = l; i < r; ++i) {
		if (i >= s.size())
			res.push_back('0');
		else
			res.push_back(s[i]);
	}
	return res;
}
std::string One(i32 x)
{
	std::string res;
	res.resize(x + 1);
	for (int i = 0; i < x; ++i) res[i] = '0';
	res[x] = '1';
	return res;
}
std::string revOne(i32 x)
{
	std::string res = One(x);
	std::reverse(res.begin(), res.end());
	return res;
}
void work(i32 n, i32 a, i32 b)
{
	v.resize(n);
	for (int id = 0, i = 0, last = 0; id < 7; ++id, i += 2, last += 8) {
		std::vector<std::string> t(n);
		for (int i = 0; i < n; ++i) t[i] = "0";
		if (last != 0) {
			t[i - 2] = "1";
		}
		t[i] = revOne(49);
		t[i + 1] = revOne(last);
		v[id] = prod(t);
		std::reverse(v[id].begin(), v[id].end());
	}
	for (int i = 14; i < 16; ++i) {
		std::vector<std::string> t(n);
		for (int j = 0; j < n; ++j) t[j] = "0";
		t[i] = "1";
		ans[i] = prod(t);
		std::reverse(ans[i].begin(), ans[i].end());
	}
	v[7] = ans[14];
	for (int id = 0, i = 0, last = 0; id < 7; ++id, i += 2, last += 8) {
		if (id != 0) v[id] = v[id] - ans[i - 2];
		auto t = v[id] - Cut(0, last + 8, v[id + 1]) * One(49);
		ans[i + 1] = Cut(last, last + 57, t);
		t = v[id] - ans[i + 1] * One(last);
		ans[i] = Cut(49, 49 + 57, t);
	}
	for (int i = 0; i < n; ++i) {
		while (ans[i].size() > 1 && ans[i][ans[i].size() - 1] == '0')
			ans[i].pop_back();
		std::reverse(ans[i].begin(), ans[i].end());
	}
	for (int i = 0; i < n; ++i) {
		std::cerr << ans[i] << '\n';
	}
}
std::vector<std::string> guess(int n, int a, int b, int t)
{
	ans.resize(n);
	if (n == 10) {
		for (int i = 0; i < n; ++i) {
			std::vector<std::string> tmp(n);
			for (int j = 0; j < n; ++j) {
				if (i == j) tmp[j] = "1";
				else tmp[j] = "0";
			}
			ans[i] = prod(tmp);
		}
		return ans;
	}
	else if (n == 25) {
		for (int i = 0; i < n; i += 5) {
			std::vector<std::string> q1(n), q2(n);
			for (int j = 0; j < n; ++j) {
				q1[j] = "0";
				q2[j] = "0";
			}
			q1[i] = "10000";
			q1[i + 1] = "100";
			q1[i + 2] = "1";
			q2[i + 3] = "1";
			q2[i + 4] = "100";
			auto t1 = prod(q1);
			auto t2 = prod(q2);
			for (int j = 0; j < 5; ++j)
				ans[i + j].resize(2);
			for (int j = 0; j < 2; ++j)
				ans[i + 2][j] = t1[t1.size() - 2 + j];
			for (int j = 0; j < 2; ++j)
				ans[i + 1][j] = t1[t1.size() - 4 + j];
			for (int j = 0; j < 2; ++j) {
				ans[i][j] =  i32(t1.size()) - 6 + j >= 0 ? t1[t1.size() - 6 + j] : '0';
			}
			for (int j = 0; j < 2; ++j)
				ans[i + 3][j] = t2[t2.size() - 2 + j];
			for (int j = 0; j < 2; ++j)
				ans[i + 4][j] = i32(t2.size()) - 4 + j < 0 ? '0' : t2[t2.size() - 4 + j];
		}
		for (int i = 0; i < n; ++i) {
			std::reverse(ans[i].begin(), ans[i].end());
			while (ans[i].size() > 1 && ans[i][ans[i].size() - 1] == '0')
				ans[i].pop_back();
			std::reverse(ans[i].begin(), ans[i].end());
		}
		return ans;
	}
	work(n, a, b);
	return ans;
}

/*
Sub4:
信息总量: 16 * 57 = 912 个十进制位.
单次查询可以获得的信息总量: 50 + 50 + 7 / 2 个十进制位.
10 次查询显然足够, 最多有 1570 个十进制位, 但是某些信息无法拆开.
8 次查询可以知道前 8 个数的前 50 位, 后 8 个数的后 50 位.
以及 8 组方程.
获得信息量不足.
考虑 4 次查询.
会了.
两两分组, 其中有 7 位未知, 我们强制让下个询问告诉我这 7 位的信息.
于是下个询问需要 14 位信息.
最后 3 个询问暴力回答, 刚好 10 次询问.
麻了, 好毒瘤.
今天不会寄了吧.
好像有老哥会 T1, 有老哥会 T3.
实在是太强了/bx
我只会打卡题 T2.
我菜死了/ll
猪脑过载了, 头好热...
*/
