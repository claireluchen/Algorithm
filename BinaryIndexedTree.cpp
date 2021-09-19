/*
Binary Indexed Tree / Fenwick Tree
The following code supports three operations:
C x v changes the x-th element of the array to v (1-based index).
S l r outputs the sum of all the elements from the l-th to the r-th index, inclusive.
Q v outputs the number of elements that are less than or equal to v in the array.
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e5+2;
int N, M, a[maxn]; ll bit[maxn], freq[maxn]; 
char op;

void update(ll bit[], int idx, int val){ //adds val to the value at index idx and updates the rest of tree accordingly in O(logn)
    for(int i = idx; i < maxn; i += i & -i)
        bit[i] += val;
}
ll query(ll bit[], int idx){ //gets the sum from 0th to idx-th element in O(logn)
    ll sum = 0;
    for(int i = idx; i > 0; i -= i & -i)
        sum += bit[i];
    return sum;
}
int main(){
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N >> M;
    for(int i = 1; i <= N; i++){
        cin >> a[i];
        update(bit, i, a[i]); //updates the number stored at the i-th position in the bit tree
        update(freq, a[i], 1); //updates the frequency bit tree (increases the frequency of the element by 1)
    }
    for(int i = 1, x, y; i <= M; i++){
        cin >> op;
        if(op == 'C') {
            cin >> x >> y;
            update(bit, x, y - a[x]); //increases the value at x-th position by y - a[x] (target value - current value)
            update(freq, a[x], -1); //since the "current" value is updated, decrease the frequency of the "current" value by 1
            update(freq, y, 1); //increase the frequency of the new value by 1
            a[x] = y; //assign the new value to the array
        }else if(op == 'S') {
            cin >> x >> y;
            cout << query(bit, y) - query(bit, x - 1) << "\n"; //sum between x-th and y-th element = sum [0 to y] - sum[0 to x - 1]
        }else if(op == 'Q'){
            cin >> x;
            cout << query(freq, x) << "\n"; //sum of frequecy of number less than or equal to x
        }
    }
}
