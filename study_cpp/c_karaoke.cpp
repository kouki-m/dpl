#include <iostream>
#include <stdlib.h>
using namespace std;
int score[101][101];

int max(int A, int B){
	if (A >= B) return A;
	return B;
}

unsigned long check_high_score(int N, int M){
	unsigned long temp, result;

	result = 0;
	for (int i = 0; i < M; i++){
		for (int j = i + 1; j < M; j++){
			temp = 0;
			for (int k = 0; k < N; k++){
				temp += max(score[k][i], score[k][j]);
			}
			result = max(result, temp);
		}
	}
	return result;
}

int main(void){
	int N, M;

	cin >> N >> M;
	for (int i = 0; i < N; i++){
		for (int j = 0; j < M; j++){
			cin >> score[i][j];
		}
	}
	cout << check_high_score(N, M) << endl;
	return 0;
}