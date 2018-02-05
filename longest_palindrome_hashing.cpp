#include <bits/stdc++.h>
 
using namespace std;
 
const int md = 1e9 + 7;
const int rep = 257; // can change base prime
const int N = 2000000 + 10;
 
char in[N], tmp[N];
int n;
int pre_hash[N];
int suf_hash[N];
int rep_power[N];
 
int add(int a, int b) {
  a += b;
  if (a > md) a -= md;
  return a;
}
 
int mult(int a, int b) {
  return ((long long)a * b) % md;
}
 
int sub(int a, int b) {
  a -= b;
  if (a < 0) a += md;
  return a;
}
    
void hashing() {    
  rep_power[0] = 1;
  for (int i = 1; i <= n; i++) {
      rep_power[i] = mult(rep_power[i - 1], rep);
  }
  for (int i = 1; i <= n; i++) {
      pre_hash[i] = add(in[i], mult(pre_hash[i - 1], rep));
  }
  for (int i = n; i >= 1; i--) {
      suf_hash[i] = add(in[i], mult(suf_hash[i + 1], rep));
  }
}
 
int main() {
  cin >> n;
  scanf("%s", tmp);
  for (int i = 1; i <= n; i++) {
      in[i] = tmp[i - 1];
  }
  hashing();
  int res = 1;
  for (int i = 2; i < n; i++) {
    int lo = -1, hi = min(i - 1, n - i) + 1;
    while (lo + 1 < hi) {
      int mid = (lo + hi) / 2;
      int h1 = sub(pre_hash[i - 1], mult(pre_hash[i - mid - 1], rep_power[mid]));
      int h2 = sub(suf_hash[i + 1], mult(suf_hash[i + mid + 1], rep_power[mid]));
      if (h1 == h2) {
        lo = mid;
      }
      else {
        hi = mid;
      }
    }
    if (res < lo * 2 + 1) {
        res = lo * 2 + 1;
    }
  }
  for (int i = 1; i < n; i++) {
    int lo = -1, hi = min(i, n - i) + 1;
    while (lo + 1 < hi) {
      int mid = (lo + hi) / 2;
      int h1 = sub(pre_hash[i], mult(pre_hash[i - mid], rep_power[mid]));
      int h2 = sub(suf_hash[i + 1], mult(suf_hash[i + mid + 1], rep_power[mid]));
      if (h1 == h2) {
          lo = mid;
      }
      else {
          hi = mid;
      }
    }
    if (res < 2 * lo) {
      res = 2 * lo;
    }
  }
  printf("%d\n", res);
  return 0;
}  