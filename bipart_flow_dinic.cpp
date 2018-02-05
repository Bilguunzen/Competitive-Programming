#include <bits/stdc++.h>
 
using namespace std;
 
const int N = 600010;
const int M = 100010;

struct graph {
  int u, v, c, nxt;
} edge[N];

int source, target;

int n, m, e;

int cnt;
int last[M];

void add_edge(int u, int v, int c) {
  edge[cnt] = {u, v, c, last[u]};
  last[u] = cnt++;
}

int flows;
int par[M];
int vis[M];

void augment(int u, int c) {
  if  (c == 0 || u == source) {
    flows = c; 
    return;
  }
  augment(edge[par[u]].u, min(c, edge[par[u]].c));
  edge[par[u] ^ 1].c += flows;
  edge[par[u]].c -= flows;
}

bool flow_dinic(int &res) {
  while (1) {
    memset(par, -1, sizeof par);
    memset(vis, -1, sizeof vis);
    queue<int> q;
    q.push(source);
    vis[source] = 1;
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      for (int i = last[u]; i != -1; i = edge[i].nxt) {
        int v = edge[i].v;
        int c = edge[i].c;
        if (vis[v] == -1 && c > 0) {
          q.push(v);
          vis[v] = 1;
          par[v] = i;
        }
      }
    }
    if (vis[target] == -1) return 0;
    for (int i = last[target]; i != -1; i = edge[i].nxt) {
      int u = edge[i].v;
      int c = edge[i ^ 1].c;
      if (vis[u] == 1 && c > 0) {
        augment(u, c);
        edge[i].c += flows;
        edge[i ^ 1].c -= flows;
        res += flows;
      }
    }
    return true;
  }
}

void init() {
  source = 0;
  target = n + m + 1;
  for (int i = 1; i <= n; i++) {
    add_edge(source, i, 1);
    add_edge(i, source, 0);
  }
  for (int i = 1; i <= m; i++) {
    add_edge(i + n, target, 1);
    add_edge(target, n + i, 0);
  }
}

int main() {
  ios_base::sync_with_stdio(0);
  memset(last, -1, sizeof last);
  cin >> n >> m >> e;
  for (int i = 0; i < e; i++) {
    int u, v;
    cin >> u >> v;
    add_edge(u, v + n, 1);
    add_edge(v + n, u, 0);
  }
  init();
  int res = 0;
  while (flow_dinic(res));
  cout << res << "\n";
  return 0;
} 