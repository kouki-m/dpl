#include <bits/stdc++.h>
using namespace std;
 
int main(void){
  int N, res, div;
  res = 0;
  cin >> N;
  for (int i = 1; i <= N; i += 2){
    div = 0;
    for (int j = 1; j <= i; j++){
      if (i % j == 0) div++;
    }
    if (div == 8) res++;
  }
  cout << res << endl;
}