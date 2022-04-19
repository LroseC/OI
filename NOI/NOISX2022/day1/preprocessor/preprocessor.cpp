#include <set>
#include <map>
#include <vector>
#include <string>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <iostream>

const int MAXLEN = 110;

int n, top;
char line[110][MAXLEN];
std::set<std::string> inEx;
std::map<std::string, std::string> M;
std::string stk[1010];

void remove(int len, char str[])
{
	std::string s;
	for (int i = 7; i < len; ++i)
		s.push_back(str[i]);
	M.erase(s);
}
void insert(int len, char str[])
{
	int i;
	std::string a, b;
	for (i = 8; i < len && str[i] != ' '; ++i)
		a.push_back(str[i]);
	for (++i; i < len; ++i)
		b.push_back(str[i]);
	M[a] = b;
}
std::string expand(int len, std::string &str)
{
//	std::cout << str << std::endl;
	std::vector<std::string> tmp;
	std::string t, res;
	for (int i = 0; i < str[i]; ++i) {
		if (isalpha(str[i]) || isdigit(str[i]) || str[i] == '_')
			t.push_back(str[i]);
		else {
			tmp.emplace_back(t);
			t.clear();
			t.push_back(str[i]);
			tmp.emplace_back(t);
			t.clear();
		}
	}
	tmp.emplace_back(t);
	t.clear();
//	for (auto &t : tmp)
//		std::cout << "\"" << t << "\"" << ' ';
//	std::cout << '\n';
	int bktop = top;
	for (auto &t : tmp) {
		if (!M.count(t) || inEx.count(t))
			res = res + t;
		else {
			inEx.insert(t);
			auto a = M[t];
			auto b = expand(a.size(), a);
			res = res + b;
			inEx.erase(t);
		}
	}
	return res;
}

int main(void)
{
	freopen("preprocessor.in", "r", stdin);
	freopen("preprocessor.out", "w", stdout);
	scanf("%d", &n);
	fgets(line[0], MAXLEN, stdin);
	for (int i = 1; i <= n; ++i) {
		fgets(line[i], MAXLEN, stdin);
		int len = strlen(line[i]) - 1;
		if (line[i][0] == '#') {
			if (line[i][1] == 'u')
				remove(len, line[i]);
			else
				insert(len, line[i]);
		}
		else {
			std::string tmp;
			for (int j = 0; j < len; ++j)
				tmp.push_back(line[i][j]);
			auto t = expand(len, tmp);
			std::cout << t;
		}
		puts("");
	}
	return 0;
}
