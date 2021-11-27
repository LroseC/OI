#include <cstdio>
#include <cstdlib>

using namespace std;

const int T = 25;
const char name[] = "test";
const int Subtask[] = {5, 10, 15, 25};
const int n[] = {10, 100, 1, 13};
const int m[] = {1, 2, 3, 4};

int main(void)
{
	system("g++ std.cpp -o std -O2");
	system("g++ rand.cpp -o rand -O2");
	fprintf(stderr, "compile end.\n\n");
	for (int i = 1, sub = 0; i <= T; ++i) {
		FILE* tmp = fopen(".tmp.tmp", "w");

		fprintf(stderr, "case %02d: begin.\n", i);

		char rd[1024], std[1024];
		if (i > Subtask[sub]) ++sub;
		fprintf(tmp, "%d\n", n[sub]);
		fclose(tmp);
		sprintf(rd, "./rand > %s%02d.in < .tmp.tmp", name, i);
		if (system(rd)) {
			fprintf(stderr, "\ncase%02d: rand.cpp error.\n", i);
			return -1;
		}
		fprintf(stderr, "case %02d: input file finished.\n", i);

		sprintf(std, "./std < %s%02d.in > %s%02d.ans", name, i, name, i);
		if (system(std)) {
			fprintf(stderr, "\ncase%02d: std.cpp error.\n", i);
			return -1;
		}
		fprintf(stderr, "case %02d: output file finished.\n", i);

		fprintf(stderr, "\n");
	}
	remove(".tmp.tmp");
	return 0;
}