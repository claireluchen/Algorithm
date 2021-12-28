/*
x has children 2 * x and 2 * x + 1
note that 2 * x = x << 1 and 2 * x + 1 = x << 1 | 1
    1
   / \
  2   3
 / \ / \
4  5 6  7

now putting 3, 1, 9, 2 into a seg tree, where n = 4
    1-4
    15
   /  \
 1-2  3-4
  4    11
 / \  / \
3  1  9  2
mid = (1 + 4) / 2 = 2, so 4 represents the range of 1 to mid and 11 is mid + 1 to n
sum of elements from ll = 1 to rr = 2 is 3 + 1 = 4, sum of ll = 1 to rr = 3 is (sum of 1 to 2) + 3 = 4 + 9 = 13
the 4 represents the sum of elements from pos 1 to 2, the 11 represents the sum of elements from pos 3 to 4
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e5 + 5;

//a stores the numbers we built the seg tree for (live at the bottom of the tree)
//sum keeps track of the sum of all children nodes
//add is a "marker", storing the value to be added to all its children when update happens
int a[maxn], sum[maxn], add[maxn]; //maxn = 3n or 4n since the size of the tree is greater than size of a

//add the value of v to all elements with index from ll to rr
//it takes too long to directly modify the end nodes and update the whole tree
//instead, mark "x" and add the total changed value to the sum so that when query, several operations can be carried out at the same time (when "up" and "down" is called)
void addOne(int x, int ll, int rr, int v){ 
  add[x] += v; //keep track of the amount to add for each child
  sum[x] += v * (rr - ll + 1); //add the total change in sum to the current node
}

void up(int x){ //update the father according to the children
  sum[x]=sum[x<<1]+sum[x<<1|1]; //the father is the sum of its children
}

void down(int x, int l, int r){ //transfer the changes applied to parent to the children
  if (add[x]){ //if we have marked values to add for the children
    int mid = (l + r) / 2; //find the point where the branches split
    addOne(x << 1, l, mid, add[x]); //update the left half, from l to mid
    addOne(x << 1 | 1, mid + 1, r, add[x]); //update the right half, from mid + 1 to r
    add[x] = 0; //mark that we have done the operations and there is nothing more to add
  }
}

void build(int x,int l,int r){ //build the seg tree top to bottom
 if (l==r) { //reached the bottom of the tree
  sum[x] = a[l]; //the sum of the single element is its value in a[]
  return;
 }
 int mid=(l+r) / 2; //find the midpoint
 build(x<<1,l,mid); //build the left half
 build(x<<1|1,mid+1,r); //build the right half
 up(x);
}

//get the sum of all values from ll to rr (inclusive)
//ex: a = {1, 2, 3, 4, 5, 6}, getsum(1, 1, n, 2, 5) means summing all elements between pos 2 and 5
//result = 14
int getsum(int x,int l,int r,int ll,int rr){ 
 if (l>=ll&&r<=rr){ //the interval we're currently exploring is included in the interval we're trying to find
  return sum[x]; //this sum should be returned and included
 }
 down(x, l, r); //can be omitted if no changes is happening
 int mid=(l+r)>>1; //find midpoint
 int lsum=0,rsum=0;
 if (ll<=mid) lsum= getsum(x<<1,l,mid,ll,rr); //get the sum of the left half
 if (rr>mid) rsum= getsum(x<<1|1,mid+1,r,ll,rr); //get the sum of the right half
 return lsum+rsum; //add the left and right sum together
}

//add v to all elements from position ll to rr (inclusive) 
//ex: a = {1, 2, 3, 4, 5, 6}, update(1, 1, n, 4, 6, 2) means adding 2 to all elements between pos 4 and 6
//result: a = {1, 2, 3, 6, 7, 8} and the tree and its characteristics are all updated
void update(int x, int l, int r, int ll, int rr, int v){ 
  if (l >= ll && r <= rr){ //the interval we're currently exploring is part of the interval we want to update
    addOne(x, l, r, v); //update all elements inside the current interval
    return;
  }
  down(x, l, r); //modify all its children if changes happen to the current element
  int mid = (l + r) / 2;
  if (ll<=mid) update(x<<1,l,mid,ll,rr, v);
  if (rr>mid) update(x<<1|1,mid+1,r,ll,rr, v);
  up(x); //modify its parent after changes happen to the current element
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
