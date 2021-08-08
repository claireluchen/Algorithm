//given n elements connected in a circle, find the maximum continuous subarray with width at most k
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int maxn = 1e5 + 5;

int n, k;
ll arr[2 * maxn], psa[2 * maxn], ans;
deque<int> q;

int main() {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); cout.tie(0);

  cin >> n >> k;
  for (int i = 1; i <= n; i++){ 
    cin >> arr[i];
    arr[i + n] = arr[i]; //since the end is connected to the beginning, simply extend the array at the end
  }
  q.push_back(0);
  for (int i = 1; i <= 2 * n; i++){
    psa[i] = psa[i - 1] + arr[i];
    while (!q.empty() && psa[q.back()] > psa[i]) q.pop_back(); //q stores psa values in non decreasing order, the first element is always the minimum
    while (!q.empty() && q.front() < i - k) q.pop_front(); //pop values that can no longer be used (comes before the leftmost bound of the subarray window)
    q.push_back(i);
    ans = max(ans, psa[i] - psa[q.front()]); //calculate the maximum possible value with i being the right bound
  }
  cout << ans << endl;

  return 0;
}
