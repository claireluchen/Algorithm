#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 5;

int n, target;
int arr[maxn];

int binarySearch(int low, int high){
  if (low == high) return low;
  if (low + 1 == high){
    if (arr[low] < target) return high;
    else return low;
  }
  int mid = (low + high) / 2;
  if (arr[mid] < target) return binarySearch(mid + 1, high);
  else return binarySearch(low, mid);  
}

int main() {  
  cin >> n >> target;
  for (int i = 0; i < n; i++){
    cin >> arr[i];
  }

  sort(arr, arr + n);
  cout << binarySearch(0, n - 1) << "\n"; //prints the index of the element in the given, sorted array

  return 0;
}
