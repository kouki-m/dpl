#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define HASHSIZE 12

typedef struct NODE{
	int key;
	struct NODE *next;
} NODE;

typedef struct attribute{
	struct NODE *head;
	struct NODE *tail;
} attribute;

void insert(int key, attribute *table){
	NODE *insert;
	int index;

	insert = malloc(sizeof(NODE));
	insert->key = key;
	insert->next = NULL;
	index = key % HASHSIZE;
	if (table[index].head != NULL){
		table[index].tail->next = insert;
		table[index].tail = insert;
	} else {
		table[index].head = insert;
		table[index].tail = insert;
	}
}

NODE *search(int key, attribute *table){
	NODE *tmp;
	int index;

	index = key % HASHSIZE;
	tmp = table[index].head;
	while (tmp != NULL){
		if (tmp->key != key){
			tmp = tmp->next;
		} else {
			break;
		}
	}
	return tmp;
}

int main(void){
	attribute table[HASHSIZE];

	for (int i = 0; i < HASHSIZE; i++){
		table[i].head = NULL;
		table[i].tail = NULL;
	}
	for (int i = 0; i < 10000; i++){
		insert(i, table);
		printf("%d, ", i);
	}
	for (int i = 0; i < 10000; i++){
		printf("%d; ", i);
		if (search(i, table) == NULL){
			printf("error\n");
			exit(1);
		}
	}
	printf("success\n");
	return 0;
}