#include <iostream>
#include <stdlib.h>
using namespace std;

int main(void){
	int N;
	long long a, b;

	cin >> N;
	for (int i = 0; i < N; i++){
		cin >> a >> b;
		cout << a+b << endl;
	}
	return 0;
}