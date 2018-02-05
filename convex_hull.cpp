#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10;

struct point {
  double x, y;
};

point ps[N], hs[N * 2];

bool cmp(point a, point b) {
  return a.x < b.x || (a.x == b.y && a.y < b.y);
}

double ccw(point a, point b, point c) {
  return (a.x * b.y - a.y * b.x) + (b.x * c.y - b.y * c.x) + (c.x * a.y - c.y * a.x) <= 0;
}

int main() {
  ios_base::sync_with_stdio(0);
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> ps[i].x >> ps[i].y;
  }
  sort(ps, ps + n, cmp);
  int k = 0;
  for (int i = 0; i < n; i++) {
    while (k >= 2 && ccw(hs[k - 2], hs[k - 1], ps[i])) k--;
    hs[k++] = ps[i];
  }
  for (int i = n - 2, t = k + 1; i >= 0; i--) {
    while (k >= t && ccw(hs[k - 2], hs[k - 1], ps[i])) k--;
    hs[k++] = ps[i];
  }
  
  return 0; 
}