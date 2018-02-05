#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10;
const int inf = 1e9 + 10;

struct point {
  double x, y;
  int ind;
  bool operator < (point o) const {
    return (y < o.y || (y == o.y && x <= o.x));
  }
};

bool cmp(point a, point b) {
  return a.x < b.x;
}

set<point> box;
set<point>::iterator it;
point p[N];

int main() {
  ios_base::sync_with_stdio(0);
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> p[i].x >> p[i].y;
    p[i].ind = i;
  }
  sort(p, p + n, cmp);
  double best = (double)inf;
  box.insert(p[0]);
  int left = 0;
  int f, s;
  for (int i = 1; i < n; i++) {
    while (left < i && p[i].x - p[left].x > best) box.erase(p[left++]);
    for (it = box.lower_bound({p[i].x - best, p[i].y - best}); it->y <= p[i].y + best && it != box.end(); it++) {
      double dis = hypot(p[i].x - it->x, p[i].y - it->y); 
      if (best > dis) {
        f = it->ind;
        s = p[i].ind;
        best = dis;
      }
    } 
    box.insert(p[i]);
  }   
  if (f > s) swap(f, s);
  cout << f << " " << s << " ";
  cout << fixed << setprecision(6) << best << "\n";
  return 0; 
}