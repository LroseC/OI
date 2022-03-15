#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 1010;

inline int read(void)
{
	int res = 0, f = 1;
	char ch = getchar();
	while (!isdigit(ch)) {
		if (ch == '-') f = -1;
		ch = getchar();
	}
	while (isdigit(ch)) {
		res = res * 10 + (ch ^ '0');
		ch = getchar();
	}
	return res * f;
}
inline char readc(void)
{
	char ch;
	do ch = getchar();
	while (ch == ' ' || ch == '\n');
	return ch;
}
inline void readstr(char str[])
{
	int p = -1;
	str[++p] = getchar();
	while (str[p] == ' ' || str[p] == '\n')
		str[p] = getchar();
	do str[++p] = getchar();
	while (str[p] != ' ' && str[p] != '\n');
	str[p] = 0;
}
inline int to_num(char str[])
{
	int res = 0;
	for (int i = 0; str[i]; ++i)
		if (isdigit(str[i])) res = res * 10 + (str[i] ^ '0');
	return res;
}
inline void write(int x)
{
	static char buf[32];
	int p = -1;
	while (x) {
		buf[++p] = x % 10 ^ '0';
		x /= 10;
	}
	while (p--) putchar(buf[p]);
	return;
}

int T;
int top, cnt;
char stk[N];
int stktype[N];
char tmp1[20], tmp2[20];

int main(void)
{
	T = read();
	for (int i = 1; i <= T; ++i) {
		top = cnt = 0;
		memset(stktype, 0, sizeof stktype);
		memset(stk, 0, sizeof stk);
		memset(tmp1, 0, sizeof tmp1);
		memset(tmp2, 0, sizeof tmp2);
		int ans = 0;
		int line = read(); char ch;
		do ch = getchar();
		while (ch != '(');
		ch = getchar();

		int type = 0; int num;
		bool flag = 0;
		if (ch == 'n') {
			type = 1;
			num = read();
		}
		else ch = getchar();
		int WF = 0;
		for (int i = 1; i <= line; ++i) {
			ch = readc();
			if (ch == 'F') {
				ch = readc();
				readstr(tmp1 + 1);
				readstr(tmp2 + 1);
				for (int i = 1; i <= top; ++i)
					if (stk[i] == ch)
						flag = 1;
				stk[++top] = ch;

				bool OMG = 1;
				if (tmp1[1] == 'n' && tmp1[2] == 0) {
					if (tmp2[1] == 'n' && tmp2[2] == 0) OMG = 0;
					else ++WF, stktype[top] = 2;
				}
				if (tmp2[1] == 'n' && tmp2[2] == 0 && OMG && !WF) {
					++cnt;
					ans = max(ans, cnt);
					stktype[top] = 1;
				}
				if (isdigit(tmp1[1]) && isdigit(tmp2[1]))
					if (to_num(tmp1 + 1) > to_num(tmp2 + 1))
						++WF, stktype[top] = 2;
			}
			else {
				if (!top) {
					flag = 1;
					continue;
				}
				if (stktype[top] == 1) --cnt;
				if (stktype[top] == 2) --WF;
				stktype[top] = 0;
				--top;
			}
		}
		if (top || flag) puts("ERR");
		else {
			if (type == 1) {
				if (ans == num) puts("Yes");
				else puts("No");
			}
			else {
				if (ans == 0) puts("Yes");
				else puts("No");
			}
		}
	}
	return 0;
}