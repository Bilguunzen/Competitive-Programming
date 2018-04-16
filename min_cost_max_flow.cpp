#include <bits/stdc++.h> 
 
using namespace std;

const int N = 310;
const int M = 1e5 + 10;
const int inf = 1e9 + 10;

const int source = 0;
const int target = N - 10;

int edge_cnt;
int last[M];

struct {
  int u, v, c, f, nxt;
} edge[M];

void add_edge(int u, int v, int c, int f) {
  edge[edge_cnt] = {u, v, c, f, last[u]};
  last[u] = edge_cnt++;
  edge[edge_cnt] = {v, u, -c, 0, last[v]};
  last[v] = edge_cnt++;
}

int dist[N];
int par[N];
int inq[N];

bool min_cost_max_flow(int &add, bool maxFlow) {

  fill(dist, dist + N, inf);
  memset(par, -1, sizeof par);
  memset(inq, -1, sizeof inq);
  queue<int> q;
  q.push(source);
  inq[source] = 1;
  dist[source] = 0;
  while (!q.empty()) {
    int u = q.front(); q.pop();
    inq[u] = -1;
    for (int i = last[u]; i != -1; i = edge[i].nxt) {
      int v = edge[i].v;
      int c = edge[i].c;
      int f = edge[i].f;
      if (f > 0 && dist[u] + c < dist[v]) {
        dist[v] = dist[u] + c;
        par[v] = i;
        if (inq[v] == -1) {
          inq[v] = 1;
          q.push(v);
        }
      }
    }
  }
  int u = target;
  add = dist[u];
  if (maxFlow && add == inf) return 0;
  if (!maxFlow && add >= 0) return 0;
  while (par[u] != -1) {
    edge[par[u]].f--;
    edge[par[u] ^ 1].f++;
    u = edge[par[u]].u;
  }
  return 1;
}

int n, m;
string t[N];
int a[N], b[N];

int ka() {
  memset(last, -1, sizeof last);
  edge_cnt = 0;
  if (n > m) return 0;
  for (int i = 1; i <= m; i++) {
    add_edge(source, i, 0, 1);
    add_edge(i + m, target, 0, 1);
    for (int j = 1; j <= m; j++) {
      if (j <= n) {
        if (t[j] == "ATK" && b[i] >= a[j]) {
          add_edge(i, j + m, -(b[i] - a[j]), 1);
        }
        if (t[j] == "DEF" && b[i] > a[j]) {
          add_edge(i, j + m, 0, 1);
        }
      }
      else {
        add_edge(i, j + m, -b[i], 1);
      } 
    }
  }
  int flow = 0;
  int add;
  int cost = 0;
  while (min_cost_max_flow(add, true)) {
    flow++;
    cost += add;
  }
  if (flow == m) return -cost;
  return 0;
}

int ko() {
  memset(last, -1, sizeof last);
  edge_cnt = 0;
  for (int i = 1; i <= m; i++) {
    add_edge(source, i, 0, 1);
  }
  for (int i = 1; i <= n; i++) {
    add_edge(i + m, target, 0, 1);
  }
  for (int i = 1; i <= m; i++) {
    for (int j = 1; j <= n; j++) {
      if (t[j] == "ATK" && b[i] > a[j]) {
        add_edge(i, j + m, -(b[i] - a[j]), 1);
      }
    }
  }
  int cost = 0;
  int add;
  while (min_cost_max_flow(add, false)) {
    cost += add;
  }
  return -cost;
}

int main() {
  ios_base::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> t[i] >> a[i];
  }
  for (int i = 1; i <= m; i++) {
    cin >> b[i];
  }
  cout << max(ka(), ko()) << "\n";
  return 0;
}