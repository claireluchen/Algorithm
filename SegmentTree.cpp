/*
x has children 2 * x and 2 * x + 1
note that 2 * x = x << 1 and 2 * x + 1 = x << 1 | 1
    1
   / \
  2   3
 / \ / \
4  5 6  7

now putting 3, 1, 9, 2 into a seg tree
   l=1 r=4
    15
   /  \
 1-2  3-4
  4    11
 / \  / \
3  1  9  2
sum of elements from ll = 1 to rr = 2 is 3 + 1 = 4, sum of ll=1 to rr = 3 is 4 + 9 = 13
the 4 represents the sum of elements from pos 1 to 2
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e5 + 5;
const int mod = 1e9 + 7;

int sum[maxn], a[maxn], add[maxn]; //maxn = 3n or 4n

//add the value of v to all elements with index from ll to rr
//it takes too long to directly modify the end nodes and update the whole tree
//instead, mark "x" and add the total changed value to the sum so that when query, several operations can be carried out at the same time (when "up" and "down" is called)
void addOne(int x, int ll, int rr, int v){ 
  add[x] += v;
  sum[x] += v * (rr - ll + 1);
}

void up(int x){ //update the father according to the children
  sum[x]=sum[x<<1]+sum[x<<1|1];
}

void down(int x, int l, int r){ //transfer the changes applied to parent to the children
  if (add[x]){
    int mid = (l + r) / 2;
    addOne(x << 1, l, mid, add[x]);
    addOne(x << 1 | 1, mid + 1, r, add[x]);
    add[x] = 0;
  }
}

void build(int x,int l,int r){ //build the seg tree
 if (l==r) { //reached the bottom of the tree
  sum[x] = a[l];
  return;
 }
 int mid=(l+r)>>1;
 build(x<<1,l,mid);
 build(x<<1|1,mid+1,r);
 up(x);
}

//get the sum of all values from ll to rr (inclusive)
//ex: a = {1, 2, 3, 4, 5, 6}, getsum(1, 1, n, 2, 5) means summing all elements between pos 2 and 5
//result = 14
int getsum(int x,int l,int r,int ll,int rr){ 
 if (l>=ll&&r<=rr){
  return sum[x];
 }
 down(x, l, r);
 int mid=(l+r)>>1;
 int lsum=0,rsum=0;
 if (ll<=mid) lsum= getsum(x<<1,l,mid,ll,rr);
 if (rr>mid) rsum= getsum(x<<1|1,mid+1,r,ll,rr);
 return lsum+rsum;
}

//add v to all elements from position ll to rr (inclusive) 
//ex: a = {1, 2, 3, 4, 5, 6}, update(1, 1, n, 4, 6, 2) means adding 2 to all elements between pos 4 and 6
//result: a = {1, 2, 3, 6, 7, 8} and the tree and its characteristics are all updated
void update(int x, int l, int r, int ll, int rr, int v){ 
  if (l >= ll && r <= rr){
    addOne(x, l, r, v);
    return;
  }
  down(x, l, r);
  int mid = (l + r) / 2;
  if (ll<=mid) update(x<<1,l,mid,ll,rr, v);
  if (rr>mid) update(x<<1|1,mid+1,r,ll,rr, v);
  up(x);
}

int main() {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); cout.tie(0);
  
  int n, m; //n nodes, m operations
  cin >> n >> m;
  for (int i = 1; i <= n; i++){
    cin >> a[i];
  }
  build(1, 1, n);

  while (m--){
    int op, x, y;
    cin >> op >> x >> y;
    if (op == 0){ //add v to all elements from position x to y 
      int v; cin >> v;
      update(1, 1, n, x, y, v);
    }else{ //get the sum of elements from position x to y
      cout << getsum(1, 1, n, x, y) << endl;
    }
  }
  
  return 0;
}
