#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <bits/stdc++.h>
 
using namespace __gnu_pbds;
using namespace std;
 
typedef
tree<
  pair<int,int>,
  null_type,
  greater<pair<int,int>>,
  rb_tree_tag,
  tree_order_statistics_node_update>
order_set;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  /*
  ordered_set os;
  
  os.insert(val);

  os.find_by_order(index);
  end(os) == os.find_by_order(out of index);
  
  os.order_of_key(val); that works as 'lower_bound()'

  */ 
  return 0;
}
