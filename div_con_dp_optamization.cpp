#include <bits/stdc++.h> 

using namespace std;

const int N = 4e3 + 10;
const int K = 8e2 + 10;
const int inf = 1e9 + 10;
int dp[K][N];
int sum[N][N];
int n, k;
char in[N * 2];

int get(int i, int j) {
  if (i == 0) return sum[j][j];
  return sum[j][j] - sum[i - 1][j] - sum[j][i - 1] + sum[i - 1][i - 1];
}

void solve(int i, int l, int r, int L, int R) {
  int m = (l + r) / 2;
  if (l > r) return;
  dp[i][m] = inf;
  int M = -1;
  for (int z = L; z <= R; z++) {
    if (dp[i][m] > dp[i - 1][z] + get(z + 1, m)) {
      dp[i][m] = dp[i - 1][z] + get(z + 1, m);
      M = z;
    } 
  }
  solve(i, l, m - 1, L, M);
  solve(i, m + 1, r, M, R);
}

int main() {
  scanf("%d %d", &n, &k);
  getchar();
  for (int i = 0; i < n; i++) {
    gets(in);
    for (int j = 0; j < n; j++) {
      sum[i][j] = in[j * 2] - '0' + ((j == 0) ? 0 : sum[i][j - 1]);      
    }
  }
  for (int i = 1; i < n; i++) {
    for (int j = 0; j < n; j++) {
      sum[i][j] += sum[i - 1][j];
    }
  }
  for (int i = 0; i < n; i++) {
    dp[0][i] = get(0, i);
  }
  for (int i = 1; i < k; i++) {
    solve(i, 0, n - 1, 0, n - 1);
  }
  printf("%d\n", dp[k - 1][n - 1] / 2);
  return 0;
}
