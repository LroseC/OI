#include <cstdio>
#include <cstdlib>

int main(void)
{
	bool fail = 0;
	fail |= system("g++ tree.cpp -O2 -o main -DDEBUG");
	fail |= system("g++ brute.cpp -O2 -o brute -DDEBUG");
	fail |= system("g++ rand.cpp -O2 -o rand");
	if (fail) {
		fprintf(stderr, "compile error.\n");
		return -1;
	}
	for (int i = 1; i <= 100; ++i) {
		fprintf(stderr, "Test #%d\n", i);
		system("./rand > tree.in");
		system("./main < tree.in > tree.out");
		system("./brute < tree.in > tree.ans");
		if (system("diff tree.out tree.ans")) {
			fprintf(stderr, "WA on #%d\n", i);
			system("rm main brute rand");
			return -1;
		}
		else {
			fprintf(stderr, "Accepted.\n");
		}
	}
	system("rm main brute rand");
	return 0;
}
