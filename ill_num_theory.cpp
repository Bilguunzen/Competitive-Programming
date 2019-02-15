#include <bits/stdc++.h>

#define int long long

using namespace std;

const int md = 998244353;
const int N = 110;
const int g = 3;
int k, n, m;

struct matrix {
  int mat[N][N];
  matrix() {
    memset(mat, 0, sizeof mat);
  }
  matrix operator * (const matrix other) const {
    matrix res;
    for (int r = 0; r < k; r++) {
      for (int c = 0; c < k; c++) {
        int cur_res = 0;
        for (int i = 0; i < k; i++) {
          cur_res = ((mat[r][i] * other.mat[i][c]) % (md - 1) + cur_res) % (md - 1);
        }
        res.mat[r][c] = cur_res;
      }
    }
    return res;
  }
};

matrix fpow_mat(matrix a, int b) {
  matrix res;
  for (int i = 0; i < k; i++) {
    res.mat[i][i] = 1;
  }
  while (b > 0) {
    if (b & 1) {
      res = res * a;
    }
    a = a * a;
    b /= 2;
  }

  return res;
}

int add(int a, int b) {
  return (a + b + md) % md;
}

int mul(int a, int b) {
  return (a * b) % md;
}

int fpow(int a, int b) {
  int res = 1;
  while (b > 0) {
    if (b & 1) {
      res = mul(a, res);
    }
    a = mul(a, a);
    b /= 2;
  }
  return res;
}

int discrete_log(int a, int b) {
  int n = ceil(sqrt(md));
  unordered_map<int, int> ump;
  for (int j = 0; j <= n; j++) {
    ump[mul(fpow(a, j), b)] = j;
  }
  for (int i = 1; i <= n; i++) {
    int cur = fpow(a, i * n);
    if (ump.find(cur) != ump.end()) {
      return i * n - ump[cur]; 
    }
  }
  return -1;
}

int gcd(int a, int b) {
  if (b == 0) return a;
  return gcd(b, a % b);
}

void ext_gcd(int a, int b, int &x, int &y){
  if (b == 0) {
    x = 1; y = 0;
    return;
  }
  ext_gcd(b, a % b, y, x);
  y -= a / b * x;
}

int solve(int a, int b, int c) {
  if (c == 0) return 0;
  int gg = gcd(a, b);
  if (c % gg != 0) return -1;
  a /= gg; 
  b /= gg;
  c /= gg;
  int x, y;
  ext_gcd(a, b, x, y);
  x = (x * c);
  while (x < 0) x += b;
  return x;
}

signed main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cin >> k;
  vector<int> b(k);
  for (int i = 0; i < k; i++) {
    cin >> b[i];
  }
  cin >> n >> m;  
  matrix res_mat;
  for (int i = 0; i < k; i++) {
    res_mat.mat[0][i] = b[i];
    if (i < k - 1) {
      res_mat.mat[i + 1][i] = 1;
    }
  }
  res_mat = fpow_mat(res_mat, n - k); 
  int ans = solve(res_mat.mat[0][0], md - 1, discrete_log(g, m)); 
  if (ans >= 0) {
    cout << fpow(g, ans) << "\n";
  }
  else {
    cout << -1 << "\n";
  }
  return 0;
}
