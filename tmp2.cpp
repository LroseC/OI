#include <cstdio>
#include <algorithm>

using namespace std;

struct node
{
	int val, dep;
	node *l, *r;
	node() { l = r = NULL; }
	node(int val) : val(val), dep(0), l(NULL), r(NULL) {}
};
node* merge(node *a, node *b)
{
	if (!a || !b) { return a + b; }
	if (a->val < b->val) swap(a, b);
	a->r = merge(a->r, b);
	if (a->r->dep > a->l->dep) swap(a->l, a->r);
	a->dep = a->r->dep + 1;
	return a;
}
int top(node *p) { return p->val; }
int second(node *p) { return max(p->l->val, p->r->val); }
node* pop(node *p)
{
	node *t = merge(p->l, p->r);
	delete p;
	return t;
}

int main(void)
{
	int T; scanf("%d", &T);
	while (T--) {
	}
}