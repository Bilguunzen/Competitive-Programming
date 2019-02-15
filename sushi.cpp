#include <bits/stdc++.h>

using namespace std;

const int N = 310;
const int M = 110;

double dp[N][N][N];
bool f[N][N][N];
int n, cnt[4];
//https://atcoder.jp/contests/dp - sushi expected value problem
double solve(int x, int y, int z) {
  if (x == 0 && y == 0 && z == 0) return 0;
  if (f[x][y][z]) return dp[x][y][z];
  dp[x][y][z] = 1.0;
  if (x > 0) dp[x][y][z] += (1.0 * x / n) * solve(x - 1, y, z);
  if (y > 0) dp[x][y][z] += (1.0 * y / n) * solve(x + 1, y - 1, z);
  if (z > 0) dp[x][y][z] += (1.0 * z / n) * solve(x, y + 1, z - 1);
  dp[x][y][z] *= (1.0 * n / (x + y + z));
  f[x][y][z] = true;
  return dp[x][y][z];
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cin >> n;
  for (int i = 0; i < n; i++) {
    int x; 
    cin >> x;
    cnt[x]++;
  }
  memset(f, false, sizeof f);
  cout << fixed << setprecision(10) << solve(cnt[1], cnt[2], cnt[3]) << "\n";
  return 0;
}
