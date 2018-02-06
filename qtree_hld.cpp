#include <bits/stdc++.h>
 
using namespace std;
 
const int N = 10010;
 
vector<pair<int, int> > adj[N];
pair<int, pair<int, int> > edge[N];
int chainHead[N];
int bitree[N][25];
int num[N];
int n;
int edgeCounted;
int currChain;
 
struct tree {
  int par;
  int depth;
  int size;
  int poseg;
  int chain;
} node[N];
 
struct seg {
  int arr[N];
  int st[N * 6];
} s;
 
void addEdge(int u, int v, int e, int idx) {
  adj[u].push_back(make_pair(v, idx));
  adj[v].push_back(make_pair(u, idx));
  edge[idx] = make_pair(e, make_pair(u, v));
}
 
void dfs(int u, int p, int d) {
  node[u].par = p;
  node[u].depth = d;
  node[u].size = 1;
  for (int i = 0; i < adj[u].size(); i++) {
    int v = adj[u][i].first;
    if (v == p) continue;
    dfs(v, u, d + 1);
    node[u].size += node[v].size;
  }
}
 
 
void hld(int u, int idx) {
  if (chainHead[currChain] == -1) {
    chainHead[currChain] = u;
  }
  node[u].chain = currChain;
  node[u].poseg = edgeCounted;
  num[idx] = edgeCounted;
  s.arr[edgeCounted++] = edge[idx].first;
  int schild = -1, sedge;
  for (int i = 0; i < adj[u].size(); i++) {
    int v = adj[u][i].first;
    if (v == node[u].par) continue;
    if (schild == -1 || node[schild].size < node[v].size) {
      schild = v;
      sedge = adj[u][i].second;
    }
  }
  if (schild != -1) {
    hld(schild, sedge);
  }
  for (int i = 0; i < adj[u].size(); i++) {
    int v = adj[u][i].first;
    if (v == node[u].par) continue;
    if (v == schild) continue;
    currChain++;
    hld(v, adj[u][i].second);
  }
}
 
void init(int p, int l, int r) {
  if (l == r) {
    s.st[p] = s.arr[l];
    return;
  }
  int mid = (l + r) / 2;
  init(p * 2, l, mid);
  init(p * 2 + 1, mid + 1, r);
  s.st[p] = max(s.st[p * 2], s.st[p * 2 + 1]);
}
 
void modify(int p, int l, int r, int x, int val) {
  if (x < l || r < x) {
    return;
  }
  if (x == l && x == r) {
    s.st[p] = val;
    return;
  }
  int mid = (l + r) / 2;
  modify(p * 2, l, mid, x, val);
  modify(p * 2 + 1, mid + 1, r, x, val);
  s.st[p] = max(s.st[p * 2], s.st[p * 2 + 1]);
}
 
int geto(int p, int l, int r, int L, int R) {
  if (R < l || r < L) return 0;
  if (L <= l && r <= R) return s.st[p];
  int mid = (l + r) / 2;
  int getl = geto(p * 2, l, mid, L, R);
  int getr = geto(p * 2 + 1, mid + 1, r, L, R);
  return max(getl, getr);
}
 
 
int lca(int u, int v) {
  if (node[u].depth < node[v].depth) {
    swap(u, v);
  }
  int diff = node[u].depth - node[v].depth;
  while (diff) {
    int lg = (int)log2(diff);
    u = bitree[u][lg];
    diff -= (1 << lg);
  }
  if (u == v) return u;
  for (int lg = 20; lg >= 0; lg--) {
    if (bitree[u][lg] != bitree[v][lg]) {
      u = bitree[u][lg];
      v = bitree[v][lg];
    }
  }
  return node[u].par;
}
 
int go(int u, int v) {
  int chu, chv = node[v].chain, ans = 0;
  while (1) {
    chu = node[u].chain;
    if (chu == chv) {
      if (u != v) {
        ans = max(ans, geto(1, 0, n - 1, node[v].poseg + 1, node[u].poseg));
      }
      break;
    }
    else {
      ans = max(ans, geto(1, 0, n - 1, node[chainHead[chu]].poseg, node[u].poseg));
      u = node[chainHead[chu]].par;
    }
  }
  return ans;
}
 
void maxEdge(int u, int v) {
  int ances = lca(u, v);
  cout << max(go(u, ances), go(v, ances)) << "\n";
}
 
int main() {
  int tt;
  scanf("%d", &tt);
  while (tt--) {
    edgeCounted = 0;
    currChain = 0;
    memset(chainHead, -1, sizeof chainHead);
    for (int i = 0; i < N; i++) {
      adj[i].clear();
    }
    cin >> n;
    edge[0].first = -1;
    for (int i = 0; i < n - 1; i++) {
      int u, v, e;
      scanf("%d %d %d", &u, &v, &e);
      addEdge(u, v, e, i + 1);
    }
    
    dfs(1, 0, 0);
    hld(1, 0);
    init(1, 0, n - 1);      
    for (int j = 0; j < 20; j++) {
      if (j == 0) {
        for (int i = 1; i <= n; i++) {
          bitree[i][j] = node[i].par;
        }
      }
      else {
        for (int i = 1; i <= n; i++) {
          bitree[i][j] = bitree[bitree[i][j - 1]][j - 1];
        }
      }
    }
    char qq[10];
    while (1) {
      scanf("%s", qq);
      if (qq[0] == 'D') {
        break;
      }
      else if (qq[0] == 'Q') {
        int u, v;
        scanf("%d %d", &u, &v);
        maxEdge(u,v); 
      }
      else {
        int e, val;
        scanf("%d %d", &e, & val);
        modify(1, 0, n - 1, num[e], val);
      }
    }
  }
  return 0;
} 