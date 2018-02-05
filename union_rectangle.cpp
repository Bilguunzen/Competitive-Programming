#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10;

struct point {
  long long x, y;
  int ind;
  bool type;
};

bool ver(point a, point b) {
  return a.x < b.x;
}

bool hor(point a, point b) {
  return a.y < b.y;
}

point pv[N], ph[N];
bool inset[N];

int main() {
  ios_base::sync_with_stdio(0);
  long long n;
  cin >> n;
  // odd is lower left corner
  // even is upper right corner
  for (int i = 0; i < 2 * n; i++) {
    cin >> pv[i].x >> pv[i].y;
    pv[i].ind = i / 2;
    pv[i].type = (i & 1);
    ph[i] = pv[i];
  }
  sort(pv, pv + 2 * n, ver);
  sort(ph, ph + 2 * n, hor);
  
  inset[pv[0].ind] = 1; 
  long long ret = 0;
  for (int i = 1; i < 2 * n; i++) {
    long long xx = pv[i].x - pv[i - 1].x;
    if (xx == 0) {
      inset[pv[i].ind] = (pv[i].type == 0);
      continue;
    }
    long long by;
    long long cnt = 0;
    for (int i = 0; i < 2 * n; i++) {
      if (inset[ph[i].ind]) {
        if (ph[i].type == 0) {
          if (cnt == 0) by = ph[i].y;
          cnt++;
        }
        else {
          cnt--;
          if (cnt == 0) {
            long long yy = ph[i].y - by;
            ret += xx * yy;
          }
        }
      }
    }
    inset[pv[i].ind] = (pv[i].type == 0);
  }
  cout << ret;
  return 0; 
}