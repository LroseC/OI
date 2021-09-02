#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 20;

int n, m;
int old[N], man[N];

bool goal;
int num = 1000;

int string2int(string x)
{
	if (x == "A") return 1;
	else if (x == "2") return 2;
	else if (x == "3") return 3;
	else if (x == "4") return 4;
	else if (x == "5") return 5;
	else if (x == "6") return 6;
	else if (x == "7") return 7;
	else if (x == "8") return 8;
	else if (x == "9") return 9;
	else if (x == "10") return 10;
	else if (x == "J") return 11;
	else if (x == "Q") return 12;
	else if (x == "K") return 13;
}
int cmp(int a, int b)
{
	if (a == b) return 0;
	if (a <= 2 && a > 0) a += 13;
	if (b <= 2 && b > 0) b += 13;
	if (a < b) return 0;
	else return 1;
}

void calc(int cnt, int val);
void dfs(int cnt, int val);

void single(int val)
{
	for (int i = 1; i <= 13; ++i)
		if (old[i] && cmp(i, val)) {
			--old[i];
			--n;
			calc(1, i);
			++old[i];
			++n;
		}
}
void couple(int val)
{
	for (int i = 1; i <= 13; ++i)
		if (old[i] >= 2 && cmp(i, val)) {
			old[i] -= 2;
			n -= 2;
			calc(2, i);
			old[i] += 2;
			n += 2;
		}
}
void triple(int val)
{
	for (int i = 1; i <= 13; ++i)
		if (old[i] >= 3 && cmp(i, val)) {
			old[i] -= 3;
			n -= 3;
			calc(3, i);
			old[i] += 3;
			n += 3;
		}
}
void TNT(int val)
{
	for (int i = 1; i <= 13; ++i)
		if (old[i] >= 4 && cmp(i, val)) {
			old[i] -= 4;
			n -= 4;
			calc(4, i);
			old[i] += 4;
			n += 4;
		}
}
void shun(int val)
{
	if (n < 5) return;
	for (int i = 1; i <= 13; ++i)
		if (old[i]) {
			for (int j = i + 1; j <= i + 4; ++j)
				if (!old[j])
					return;
			n -= 5;
			calc(5, i);
			n += 5;
		}
}
void pass(void)
{
	calc(-1, -1);
}
bool single2(int val)
{
	for (int i = 3; i <= 13; ++i)
		if (man[i] && cmp(i, val)) {
			--man[i];
			--m;
			dfs(1, i);
			++man[i];
			++m;
			return 1;
		}
	for (int i = 1; i <= 2; ++i)
		if (man[i] && cmp(i, val)) {
			--man[i];
			--m;
			dfs(1, i);
			++man[i];
			++m;
			return 1;
		}
	return 0;
}
bool couple2(int val)
{
	for (int i = 3; i <= 13; ++i)
		if (man[i] >= 2 && cmp(i, val)) {
			man[i] -= 2;
			m -= 2;
			dfs(2, i);
			man[i] += 2;
			m += 2;
			return 1;
		}
	for (int i = 1; i <= 2; ++i)
		if (man[i] >= 2 && cmp(i, val)) {
			man[i] -= 2;
			m -= 2;
			dfs(2, i);
			man[i] += 2;
			m += 2;
			return 1;
		}
	return 0;
}
bool triple2(int val)
{
	for (int i = 3; i <= 13; ++i)
		if (man[i] >= 3 && cmp(i, val)) {
			man[i] -= 3;
			m -= 3;
			dfs(3, i);
			man[i] += 3;
			m += 3;
			return 1;
		}
	for (int i = 1; i <= 2; ++i)
		if (man[i] >= 3 && cmp(i, val)) {
			man[i] -= 3;
			m -= 3;
			dfs(3, i);
			man[i] += 3;
			m += 3;
			return 1;
		}
	return 0;
}
bool TNT2(int val)
{
	for (int i = 3; i <= 13; ++i)
		if (man[i] >= 4 && cmp(i, val)) {
			man[i] -= 4;
			m -= 4;
			dfs(4, i);
			man[i] += 4;
			m += 4;
			return 1;
		}
	for (int i = 1; i <= 2; ++i)
		if (man[i] >= 4 && cmp(i, val)) {
			man[i] -= 4;
			m -= 4;
			dfs(4, i);
			man[i] += 4;
			m += 4;
			return 1;
		}
	return 0;
}
bool shun2(int val)
{
	if (m < 5) return 0;
	for (int i = 1; i <= 13; ++i)
		if (man[i]) {
			for (int j = i + 1; j <= i + 4; ++j)
				if (!man[j])
					return 0;
			m -= 5;
			dfs(5, i);
			m += 5;
			return 1;
		}
	return 0;
}
bool pass2(void)
{
	dfs(-1, -1);
	return 1;
}
void calc(int cnt, int val)
{
	if (n == 0) {
		if (!goal) {
			goal = 1;
			num = m;
		}
		else num = max(num, m);
		return;
	}
	if (cnt == -1) {
		if (shun2(-1)) return;
		if (TNT2(-1)) return;
		if (triple2(-1)) return;
		if (couple2(-1)) return;
		if (single2(-1)) return;
	}
	if (cnt == 1) {
		if (TNT2(-1)) return;
		if (single2(val)) return;
		pass2();
	}
	if (cnt == 2) {
		if (TNT2(-1)) return;
		if (couple2(val)) return;
		pass2();
	}
	if (cnt == 3) {
		if (TNT2(-1)) return;
		if (triple2(val)) return;
		pass2();
	}
	if (cnt == 4) {
		if (TNT2(val)) return;
		pass2();
	}
	if (cnt == 5) {
		if (shun2(val)) return;
		if (TNT2(-1)) return;
		pass2();
	}
}

void dfs(int cnt, int val)
{
	if (m == 0) {
		if (goal) return;
		else {
			num = min(num, n);
		}
		return;
	}
	if (cnt == -1) {
		single(-1);
		couple(-1);
		triple(-1);
		TNT(-1);
		shun(-1);
	}
	if (cnt == 1) {
		single(val);
		TNT(-1);
		pass();
	}
	if (cnt == 2) {
		couple(val);
		TNT(-1);
		pass();
	}
	if (cnt == 3) {
		triple(val);
		TNT(-1);
		pass();
	}
	if (cnt == 4) {
		TNT(val);
		pass();
	}
	if (cnt >= 5) {
		TNT(-1);
		shun(val);
		pass();
	}
}

void Work(void)
{
	goal = 0, num = 1000;
	memset(old, 0, sizeof old);
	memset(man, 0, sizeof man);
	for (int i = 1; i <= n; ++i) {
		string tmp; cin >> tmp;
		++old[string2int(tmp)];
	}
	for (int i = 1; i <= m; ++i) {
		string tmp; cin >> tmp;
		++man[string2int(tmp)];
	}
	dfs(-1, -1);
	if (goal) cout << "Lose" << '\n' << num << '\n';
	else cout << "Win" << '\n' << num << '\n';
}

int main(void)
{
	while (cin >> n >> m, n || m) Work();
	return 0;
}