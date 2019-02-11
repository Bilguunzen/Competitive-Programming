#include <bits/stdc++.h>

using namespace std;

mt19937 rng((int) std::chrono::steady_clock::now().time_since_epoch().count());

const int N = 1e9;

pair<int, int> get_max() {
  int left = -1, right = N + 1;
  int q = 0;
  while (left + 1 < right) {
    int mid = (left + right) / 2;
    cout << "> " << mid << "\n";
    cout << flush;
    int ans; cin >> ans;
    cout << flush;
    if (ans == 1) {
      left = mid;
    }
    else {
      right = mid;
    }
    q++;
  }
  return {right, q};
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  pair<int, int> res_max = get_max();
  vector<int> a;
  for (int i = 0; i < n; i++) {
    a.push_back(i + 1);
  }
  shuffle(a.begin(), a.end(), rng);
  vector<int> a_ans;
  for (int i = 0; i < min(60 - res_max.second, (int) a.size()); i++) {
    cout << "? " << a[i] << "\n";
    cout << flush;
    int ans; cin >> ans;
    a_ans.push_back(ans);
  }
  sort(a_ans.begin(), a_ans.end());
  int d = 0;
  for (int i = 0; i < a_ans.size() - 1; i++) {
    d = __gcd(d, a_ans[i + 1] - a_ans[i]);
  }
  cout << "! " << res_max.first - (n - 1) * d << " " << d << "\n";  
  cout << flush;
  return 0;
}
