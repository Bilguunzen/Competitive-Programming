#include <bits/stdc++.h> 
 
using namespace std;

const int inf = 1e9 + 10;
const int N = 1e5 + 10;

set<int> edge[N];
int n, m;

int dp[20][N];
int depth[N];

void add_edge(int a, int b) {
  edge[a].insert(b);
  edge[b].insert(a);
}

void dfs(int u, int p) {
  dp[0][u] = p;
  depth[u] = depth[p] + 1;
  for (auto v : edge[u]) {
    if (v == p) continue;
    dfs(v, u);
  }
} 

void build() {
  dfs(1, 0);
  for (int i = 0; i < 18; i++) {
    for (int j = 1; j <= n; j++) {
      dp[i + 1][j]= dp[i][dp[i][j]];
    }
  }
}

int lca(int a, int b) {
  if (depth[a] > depth[b]) {
    swap(a, b);
  }
  int d = depth[b] - depth[a];
  for (int i = 0; i < 20; i++) {
    if (d & (1 << i)) {
      b = dp[i][b];
    }
  }
  if (a == b) return a;
  for (int i = 19; i >= 0; i--) {
    if (dp[i][a] != dp[i][b]) {
      a = dp[i][a];
      b = dp[i][b];
    }
  }
  return dp[0][a];
}

int dist(int a, int b) {
  return depth[a] + depth[b] - 2 * depth[lca(a, b)];
}

int sz;
int sub[N];
int par[N];

void get_size(int u, int p) {
  sub[u] = 1;
  sz++;
  for (auto v : edge[u]) {
    if (p == v) continue;
    get_size(v, u);
    sub[u] += sub[v];
  }
}

int center(int u, int p) {
  for (auto v : edge[u]) {
    if (p == v) continue;
    if (sub[v] > sz / 2) return center(v, u);
  }
  return u;
}

void decompose(int u, int p) {
  sz = 0;
  get_size(u, 0);
  int centroid = center(u, 0);
  par[centroid] = p;
  for (auto v : edge[centroid]) {
    edge[v].erase(centroid);
    decompose(v, centroid);
  }
  edge[centroid].clear();
}

int ans[N];

void modify(int u) {
  int x = u;
  while (x) {
    ans[x] = min(ans[x], dist(x, u));
    x = par[x];
  }
}

int get(int u) {
  int x = u;
  int ret = inf;
  while (x) {
    ret = min(ret, ans[x] + dist(x, u));
    x = par[x];
  }
  return ret;
}

int main() {
  ios_base::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 0; i < n - 1; i++) {
    int a, b;
    cin >> a >> b;
    add_edge(a, b);
  }
  build();
  decompose(1, 0);
  for (int i = 0; i <= n; i++) {
    ans[i] = inf;
  }
  modify(1);
  while (m--) {
    int t, v;
    cin >> t >> v;
    if (t == 1) {
      modify(v);
    }
    else {
      cout << get(v) << "\n";
    }
  }
  return 0;
}