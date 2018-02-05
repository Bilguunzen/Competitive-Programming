#include <bits/stdc++.h>
 
using namespace std;
 
typedef complex<double> base;
 
const double pi = acos(-1.0);
 
int rev(int num, int lg_n) {
  int res = 0;
  for (int i = 0; i < lg_n; ++i)
    if (num & (1 << i))
      res |= 1 << (lg_n - 1 - i);
  return res;
}
 
void fft(vector<base> &a, bool invert) {
  int n = (int) a.size();
  int lg_n = 0;
  while ((1 << lg_n) < n)  ++lg_n;
  for (int i = 0; i < n; i++) {
    int rr = rev(i, lg_n);
    if (i < rr) {
      swap(a[i], a[rr]);
    }
  }
  for (int len = 2; len <= n; len <<= 1) {
    double ang = 2 * pi / len * (invert ? -1 : 1);
    base wlen (cos(ang), sin(ang));
    for (int i = 0; i < n; i += len) {
      base w(1);
      for (int j = 0; j < len / 2; j++) {
        base u = a[i + j],  v = a[i + j + len / 2] * w;
        a[i + j] = u + v;
        a[i + j + len / 2] = u - v;
        w *= wlen;
      }
    }
  }
  if (invert) {
    for (int i = 0; i < n; i++) {
      a[i] /= n;
    }
  }
}  
 
void pluss(vector<int> &a, vector<int> &b, vector<int> &res) {
  vector<base> fa(a.begin(), a.end());
  vector<base> fb(b.begin(), b.end());
  int n = 1;
  while (n < max(fa.size(), fb.size())) {
    n <<= 1;
  }
  n <<= 1;
  fa.resize(n);
  fb.resize(n);
  fft(fa, 0);
  fft(fb, 0);
  for (int i = 0; i < n; i++) {
    fa[i] *= fb[i];
  }
  fft(fa, 1);
  res.assign(n, 0);
  for (int i = 0; i < n; i++) {
    res[i] = (int) (fa[i].real() + 0.5);
  }
}

//A={1, 2 , 3, 4}; B={2, 3, 100}=> C={3, 4, 5, 6, 7, 101, 102, 103, 104}
 
int main() {
  int tt;
  cin >> tt;
  while (tt--) {
    int n, m;
    cin >> n;
    vector<int> a, b;
    a.assign(n, 0);
    int mxa = 0, mxb = 0;
    for (int i = 0; i < n; i++) {
      cin >> a[i]; 
      mxa = max(mxa, a[i]);
    }
    cin >> m;
    b.assign(m, 0);
    for (int i = 0; i < m; i++) {
      cin >> b[i];
      mxb = max(mxb, b[i]);
    }
    vector<int> aa, bb;
    aa.assign(mxa + 1, 0);
    bb.assign(mxb + 1, 0);
    for (int i = 0; i < n; i++) {
      aa[a[i]] = 1;
    }
    for (int i = 0; i < m; i++) {
      bb[b[i]] = 1;
    }
    vector<int> res;
    pluss(aa, bb, res);
    for (int i = 0; i < res.size(); i++) {
      if (res[i]) cout << i << "\n";
    }
  }
  return 0;
} 