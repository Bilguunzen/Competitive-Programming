#include <bits/stdc++.h>

using namespace std;

const int N = 1e3 + 10;

struct point {
  double x, y;
};

point p[N];
double dist[N][N];

int main() {
  ios_base::sync_with_stdio(0);
  int n;
  double r;
  cin >> n >> r;
  if (n == 0) {
    cout << 0 << "\n";
    return 0;
  }
  for (int i = 0; i < n; i++) {
    cin >> p[i].x >> p[i].y;
  } 
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      dist[i][j] = hypot(p[i].x - p[j].x, p[i].y - p[j].y);
    }
  }
  int result = 1;
  for (int i = 0; i < n; i++) {
    vector<pair<double, bool>> angles;
    for (int j = 0; j < n; j++) {
      if (i == j) continue;
      if (dist[i][j] <= 2.0 * r) {
        double A = atan2(p[j].y - p[i].y, p[j].x - p[i].x);
        double B = acos(dist[i][j] / (2.0 * r));
        double alpha = A - B;
        double beta = A + B;
        angles.emplace_back(alpha, false); //in point
        angles.emplace_back(beta, true); // out point
      }
    }
  
    sort(angles.begin(), angles.end());
    int cur = 1;
    for (auto angle : angles) {
      cur += (angle.second == false) ? 1 : -1;
      result = max(result, cur); 
    }
  }
  cout << result << "\n";   
  return 0;
}
