#include "subway.h"
int solve(int l) {
    if (check(l)) merge(l), undo();
    return l;
}