#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#define HASHSIZE 1000000

int hash_function(int k, int i);
int h1(int k);
int h2(int k);
int hash_insert(int *T, int k);
int hash_search(int *T, int k);


int hash_function(int k, int i){
	return (h1(k) + i * h2(k)) % HASHSIZE;
}

int h1(int k){
	return k % HASHSIZE;
}

int h2(int k){
	return 1 + (k % (HASHSIZE - 1));
}

int hash_insert(int *T, int k){
	int i, q;

	i = 0;
	while (i != HASHSIZE){
		q = hash_function(k, i);
		if (T[q] == 0){
			T[q] = k;
			return q;
		} else if (T[q] == k){
			return q;
		} else {
			i++;
		}
	}
	printf("Hash over flow\n");
	return -1;
}

int hash_delete(int *T, int k){
    int i, q, r;

    i = 0;
    while(i != HASHSIZE){
        q = hash_function(k, i);
        if (T[q] == k){
            T[q] = 0;
            break;
        }
        i++;
    }
    while(T[q]){

    }
}

int hash_search(int *T, int k){
	int i, q;

	i = 0;
	q = hash_function(k, i);
	while (T[q] != 0 && i != HASHSIZE){
		if (T[q] == k){
			return q;
		}
		i++;
		q = hash_function(k, i);
	}
	printf("not found\n");
	return -1;
}

int main(void){
	int *T;
	int *arr;
	int m;

	T = malloc(sizeof(int) * (HASHSIZE + 1));
	arr = malloc(sizeof(int) * (HASHSIZE + 1));
	for(int i = 0; i < HASHSIZE; i++){
		T[i] = 0;
	}
	for(int i = 0; i < HASHSIZE; i++){
		arr[i] = rand() % HASHSIZE + 1;
		if (hash_insert(T, arr[i]) == -1){
			return 0;
		}
	}
	clock_t start = clock();
	for(int i = 0; i < HASHSIZE; i++){
		m = hash_search(T, arr[i]);
		if (m == -1){
			return 0;
		}
		//printf("%d, ", T[m]);
	}
	clock_t end = clock();
	printf("%dmsec\n", end - start);
	printf("success\n");
	/*
	hash_insert(T, 2);
	hash_insert(T, 5);
	hash_insert(T, 35);
	hash_insert(T, 76);
	hash_insert(T, 32);
	hash_insert(T, 75);
	hash_insert(T, 86);
	printf("%d, ", T[hash_search(T, 2)]);
	printf("%d, ", T[hash_search(T, 5)]);
	printf("%d, ", T[hash_search(T, 35)]);
	printf("%d, ", T[hash_search(T, 76)]);
	printf("%d, ", T[hash_search(T, 32)]);
	printf("%d, ", T[hash_search(T, 75)]);
	printf("%d, ", T[hash_search(T, 86)]);
	printf("%d, ", hash_search(T, 2));
	printf("%d, ", hash_search(T, 5));
	printf("%d, ", hash_search(T, 35));
	printf("%d, ", hash_search(T, 76));
	printf("%d, ", hash_search(T, 32));
	printf("%d, ", hash_search(T, 75));
	printf("%d, ", hash_search(T, 86));
	*/
	return 0;
}