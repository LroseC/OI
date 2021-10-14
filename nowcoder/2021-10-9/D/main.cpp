#include <cctype>
#include <cstdio>
#include <algorithm>

using namespace std;

inline int read(void)
{
	int res = 0, f = 1; char ch = getchar();
	while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
	while (isdigit(ch)) { res = res * 10 + ch - '0'; ch = getchar(); }
	return res * f;
}
template<typename T>
inline void write(T x, char end = '\n')
{
	static char buf[50]; int p = -1;
	if (x == 0) putchar('0');
	if (x < 0) { putchar('-'); x = -x; }
	while (x) { buf[++p] = x % 10; x /= 10; }
	while (~p) { putchar(buf[p] + '0'); --p; } putchar(end);
}
inline int opc2n(char ch)
{
	if (ch == 'S') return 4;
	if (ch == 'H') return 3;
	if (ch == 'C') return 2;
	if (ch == 'D') return 1;
	return -1;
}
inline int valc2n(char ch)
{
	if (ch >= '2' && ch <= '9') return ch - '0';
	if (ch == 'T') return 10;
	if (ch == 'J') return 11;
	if (ch == 'Q') return 12;
	if (ch == 'K') return 13;
	if (ch == 'A') return 14;
	return -1;
}
char _opn2c[10] = {0, 'D', 'C', 'H', 'S'};
inline char opn2c(int num)
{
	return _opn2c[num];
}
char _valn2c[100] = {0, 0, '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A'};
inline char valn2c(int num)
{
	return _valn2c[num];
}

struct Shoupai
{
	struct pai
	{
		int op, val;
		bool operator<(const pai &b) const
		{
			if (val != b.val) return val < b.val;
			return op < b.op;
		}
		pai(void)
		{
			op = val = -1;
		}
		pai(char str[])
		{
			op = opc2n(str[1]);
			val = valc2n(str[2]);
		}
	};

	int op;
	pai v[5];
	
	bool operator>(const Shoupai &b) const
	{
		if (op != b.op)
			return op < b.op;
		for (int i = 0; i < 5; ++i)
			if (v[i].val != b.v[i].val)
				return v[i].val > b.v[i].val;
		return 0;
	}
};

/*
 * 思路: 大模拟
 * 写一个类，表示一个人的手牌
 */
char pai[10][10];
Shoupai A, B;
Shoupai tA, tB;

inline bool cmp_output(const Shoupai::pai &a, const Shoupai::pai &b)
{
	if (a.val != b.val) return a.val < b.val;
	return a.op > b.op;
}

inline bool Check3(Shoupai x)
{
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < i; ++j)
			if (x.v[i].val == x.v[j].val)
				return 1;
	return 0;
}
inline bool Check5(Shoupai x)
{
	return x.v[0].op == x.v[1].op && x.v[1].op == x.v[2].op;
}
inline bool Check6(Shoupai x)
{
	return x.v[2].val - x.v[0].val <= 5;
}
inline bool Check2(Shoupai x)
{
	return Check5(x) && Check6(x);
}
inline Shoupai Get3(Shoupai x)
{
	if (x.v[0].val == x.v[1].val && x.v[1].val == x.v[2].val) {
		Shoupai res;
		res.op = 3;
		res.v[0].val = res.v[1].val = res.v[2].val = res.v[3].val = x.v[0].val;
		res.v[0].op = 1, res.v[1].op = 2, res.v[2].op = 3, res.v[3].op = 4;
		if (x.v[0].val == 2) {
			res.v[4].val = 3;
			res.v[4].op = 1;
		}
		else {
			res.v[4].val = 2;
			res.v[4].op = 1;
		}
		sort(res.v, res.v + 5, cmp_output);
		return res;
	}
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < i; ++j)
			if (x.v[i].val == x.v[j].val) {
				Shoupai res;
				res.op = 3;
				res.v[0].val = res.v[1].val = res.v[2].val = res.v[3].val = x.v[i].val;
				res.v[0].op = 1, res.v[1].op = 2, res.v[2].op = 3, res.v[3].op = 4;
				for (int k = 0; k < 3; ++k)
					if (k != i && k != j)
						res.v[4] = x.v[k];
				sort(res.v, res.v + 5, cmp_output);
				return res;
			}
	return x;
}
inline Shoupai Get2(Shoupai x)
{
	Shoupai res;
	res.op = 2;
	int b = min(10, x.v[0].val);
	for (int i = b, j = 0; j < 5; ++i, ++j) {
		res.v[j].op = x.v[0].op;
		res.v[j].val = i;
	}
	sort(res.v, res.v + 5);
	return res;
}
inline Shoupai Get5(Shoupai x)
{
	int k = 3;
	for (int e = 14; e >= 2; --e) {
		bool fail = 0;
		for (int i = 0; i < 3; ++i)
			if (x.v[i].val == e) {
				fail = 1;
				break;
			}
		if (fail) continue;
		x.v[k].op = x.v[0].op;
		x.v[k].val = e; ++k;
		if (k == 5) break;
	}
	sort(x.v, x.v + 5, cmp_output);
	return x;
}
inline void Print(Shoupai x)
{
	for (int i = 0; i < 5; ++i) {
		putchar(opn2c(x.v[i].op));
		putchar(valn2c(x.v[i].val));
		putchar(' ');
	}
}

inline void Init(void)
{
}
inline void Work(void)
{
	for (int i = 1; i <= 6; ++i) scanf("%s", pai[i] + 1);
	A.op = B.op = -1;
	for (int i = 0; i < 3; ++i) A.v[i] = pai[i + 1];
	for (int i = 0; i < 3; ++i) B.v[i] = pai[i + 4];
	if (B.v[0].val == B.v[1].val && B.v[1].val == B.v[2].val) {
		if (Check3(A) && A.v[0].val > B.v[0].val) {
			tA = Get3(A);
			Print(tA);
			puts("");
			return;
		}
		else if (Check2(A)) {
			int b = A.v[2].val;
			b = max(b, 6);
			for (int i = b, j = 0; j < 5; ++j, --i) {
				tA.v[j].op = A.v[0].op;
				tA.v[j].val = i;
			}
			sort(tA.v, tA.v + 5, cmp_output);
			Print(tA);
			puts("");
			return;
		}
		else {
			puts("-1");
			return;
		}
	}
	else if (B.v[0].op == B.v[1].op && B.v[1].op == B.v[2].op) {
		if (Check2(B)) {
			tB = Get2(B);
			if (!Check2(A)) {
				puts("-1");
				return;
			}
			tA = Get2(A);
			if (tA.v[4].val > tB.v[4].val) {
				int e = max(tB.v[4].val + 1, A.v[2].val);
				for (int i = e, j = 0; j < 5; ++j, --i) {
					tA.v[j].op = A.v[0].op;
					tA.v[j].val = i;
				}
				sort(tA.v, tA.v + 5, cmp_output);
				Print(tA);
				puts("");
				return;
			}
			puts("-1");
			return;
		}
		else {
			tB = Get5(B);
			tA = Get5(A);
			bool Abig = 0;
			for (int i = 4; i >= 0; --i)
				if (tA.v[i].val != tB.v[i].val) {
					Abig = tA.v[i].val > tB.v[i].val;
					break;
				}
			if (!Abig) {
				puts("-1");
				return;
			}
			else {
				tA = A;
				tA.op = 5;
				if (A.v[2].val > tB.v[4].val) {
					int k = 3;
					for (int i = 2; i <= 14; ++i) {
						bool fail = 0;
						for (int j = 0; j < 3; ++j)
							if (A.v[j].val == i) {
								fail = 1;
								break;
							}
						if (fail) continue;
						tA.v[k].op = A.v[0].op;
						tA.v[k].val = i;
						++k;
						if (k == 5) break;
					}
					sort(tA.v, tA.v + 5, cmp_output);
					Print(tA); puts("");
					return;
				}
				return;
			}
		}
	}
	else {
/*
		tA.op = -1;
		tB = GetBiggest(B);
		if (Check2(A)) tA = Get2(A);
		if (B.op == 2) {
			if (tA.op == -1 || tA.v[1].val <= tB.v[1].val) {
				puts("-1");
				return;
			}
			int b = max(A.v[3], tB.v[1] + 1);
			for (int i = b, j = 0; j < 5; ++j, --i) {
				putchar(opn2c(A.v[0].op));
				putchar(valn2c(i));
				putchar(' ');
			}
			puts("");
			return;
		}
		if (Check3(A)) tA.Get3(A);
		if (B.op == 3) {
		}
*/
	}
}

int main(void)
{
	int T = read();
	while (T--) {
		Init();
		Work();
	}
	return 0;
}
