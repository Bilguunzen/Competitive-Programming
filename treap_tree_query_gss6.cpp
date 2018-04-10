#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 10;

struct node {
  int cnt;
  int prio;
  int value;
  int sum;
  int pref;
  int suff;
  int maxs;
  node *l;
  node *r;
};

node treap[N];
node *root;
int t_cnt;
vector<int> rnd;
int n, m;

int in[N];

int cnt(node *p) {
  return p ? p->cnt : 0;
}

int sum(node *p) {
  return p ? p->sum : 0;
}

int maxs(node *p) {
  return p ? p->maxs : INT_MIN;
}

int pref(node *p) {
  return p ? p->pref : 0;
}

int suff(node *p) {
  return p ? p->suff : 0;
}

void update(node *p) {
  if(!p) return;
  p->cnt = 1 + cnt(p->l) + cnt(p->r);
  p->sum = p->value + sum(p->l) + sum(p->r);
  p->maxs = max(max(maxs(p->l), maxs(p->r)), max(0, suff(p->l)) + p->value + max(0, pref(p->r)));
  p->pref = max(pref(p->l), sum(p->l) + p->value + max(0, pref(p->r)));
  p->suff = max(suff(p->r), max(0, suff(p->l)) + p->value + sum(p->r));
}

void merge(node *&t, node *l, node *r) {
  if (!l || !r) {
    t = r ? r : l;
  }
  else if (l->prio < r->prio) {
    merge(l->r, l->r, r);
    t = l;
  }
  else {
    merge(r->l, l, r->l);
    t = r;
  }

  update(t);
}

void split(node *t, node *&l, node *&r, int key) {
  if (!t){
    l = r = NULL;
    return;
  }
  else if (key <= cnt(t->l)) {
    split(t->l, l, t->l, key);
    r = t;
  }
  else { 
    split(t->r, t->r, r, key - cnt(t->l) - 1);
    l = t;
  }
  update(t);
}

void add(node *&t, node *it, int index) {
  if (!t) {
    t = it;
  }
  else if (it->prio < t->prio) {
    split(t, it->l, it->r, index);
    t = it;
  }
  else {
    if (index <= cnt(t->l)) {
      add(t->l, it, index);
    }
    else {
      add(t->r, it, index - cnt(t->l) - 1);
    }
  }
  update(t);
}

void add(int index, int value) {
  node *it = &treap[t_cnt];
  it->value = value;
  it->prio = rnd[t_cnt];
  ++t_cnt;
  it->cnt = 1;
  add(root, it, index);
}

void remove(node *&t, int index) {
  if (index == cnt(t->l))
    merge(t, t->l, t->r);
  else 
    if (index < cnt(t->l))
      remove(t->l, index);
    else
      remove(t->r, index - cnt(t->l) - 1);
  update(t);
}

void modify(node *&t, int index, int value) {
  if (index == cnt(t->l))
    t->value = value;
  else
    if (index < cnt(t->l))
      modify(t->l, index, value);
    else
      modify(t->r, index - cnt(t->l) - 1, value);
  update(t);
}

int get(int a, int b) {
  node *l1, *r1;
  split(root, l1, r1, b + 1);
  node *l2, *r2;
  split(l1, l2, r2, a);
  int res = maxs(r2);
  node *t;
  merge(t, l2, r2);
  merge(root, t, r1);
  return res;
}

int main() {
  ios_base::sync_with_stdio(0);
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> in[i];
  }
  cin >> m;
  for (int i = 0; i < n + m; i++) {
    rnd.push_back(i);
  }
  random_shuffle(rnd.begin(), rnd.end());
  for (int i = 0; i < n; i++) {
    add(i, in[i]);
  }
  while (m--) {
    char ch;
    int a, b;
    cin >> ch >> a;
    if (ch == 'I') {
      cin >> b;
      add(a - 1, b);
    }
    if (ch == 'D') {
      remove(root, a - 1); 
    }
    if (ch == 'R') {
      cin >> b;
      modify(root, a - 1, b);
    }
    if (ch == 'Q') {
      cin >> b;
      cout << get(a - 1, b - 1) << "\n";
    }
  }
  return 0;
}