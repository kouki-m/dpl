#include <iostream>
#include <stdlib.h>
#include <string.h>
using namespace std;
char arr[100][11];

void swap(char **a, char **b){
	char *c;

	c = *a;
	*a = *b;
	*b = c;
}

void sort(int K){
	for (int i = 0; i < K; i++){
		for (int j = i + 1; j < K; j++){
			if (strcmp(arr[i], arr[j]) > 0) swap(arr[i], arr[j]);
		}
	}
}

int main(void){
	int N, K;

	cin >> N >> K;
	for (int i = 0; i < K; i++){
		cin >> arr[i];
	}
	sort(K);
	for (int i = 0; i < K; i++){
		cout << arr[i] << endl;
	}
	return 0;
}