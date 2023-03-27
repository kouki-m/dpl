#include "bptree.h"
#include <vector>
#include <sys/time.h>
#define DATA_SIZE 100000000

NODE *find_leaf(NODE *node, int key){
	int i;

	if (node->isLeaf) {
		return node;
	} else {
		for (i = 0; i < node->nkey; i++){
			if (node->key[i] > key) {
				break ;
			}
		}
		return find_leaf(node->chi[i], key);
	}
}

bool search_tree(NODE *node, int key){
	node = find_leaf(node, key);
	for (int i = 0; i < node->nkey; i++){
		if (node->key[i] == key){
			return true;
		}
	}
	return false;
}

void print_tree_core(NODE *n){
	printf("["); 
	for (int i = 0; i < n->nkey; i++) {
		if (!n->isLeaf) print_tree_core(n->chi[i]); 
		printf("%d", n->key[i]); 
		if (i != n->nkey-1 && n->isLeaf) putchar(' ');
	}
	if (!n->isLeaf) print_tree_core(n->chi[n->nkey]);
	printf("]");
}

void print_tree(NODE *node){
	print_tree_core(node);
	printf("\n"); fflush(stdout);
}

NODE *alloc_parent(NODE *parent){
	NODE *node;

	if (!(node = (NODE *)calloc(1, sizeof(NODE)))) ERR;
	node->isLeaf = false;
	node->nkey = 0;
	node->parent = parent;
	return node;
}

NODE *alloc_leaf(NODE *parent){
	NODE *node;

	if (!(node = (NODE *)calloc(1, sizeof(NODE)))) ERR;
	node->isLeaf = true;
	node->nkey = 0;
	node->parent = parent;
	return node;
}

TEMP *alloc_temp(void){
	TEMP *temp;

	if (!(temp = (TEMP *)calloc(1, sizeof(TEMP)))) ERR;
	temp->nkey = N-1;
	return temp;
}

void insert_in_temp(TEMP *node_main, int key, NODE *node_sub, DATA *data){
	int i;

	for (i = node_main->nkey; i > 0; i--){
		if (node_main->key[i - 1] > key){
			node_main->key[i] = node_main->key[i - 1];
			node_main->data[i] = node_main->data[i - 1];
			node_main->chi[i + 1] = node_main->chi[i];
		} else {
			break ;
		}
	}
	node_main->key[i] = key;
	node_main->data[i] = data;
	node_main->chi[i+1] = node_sub;
	node_main->nkey++;
}

void insert_in_parent(NODE *node_main, int key, NODE *node_sub){
	NODE *new_root, *parent, *new_parent;
	TEMP *temp;
	int i;

	if (Root == node_main){
		new_root = alloc_parent(NULL);
		new_root->chi[0] = node_main;
		new_root->chi[1] = node_sub;
		new_root->key[0] = key;
		node_main->parent = new_root;
		node_sub->parent = new_root;
		new_root->nkey++;
		Root = new_root;
		return ;
	}
	parent = node_main->parent;
	if (parent->nkey < N-1){
		for (i = parent->nkey; i > 0; i--){
			if (parent->key[i-1] > key){
				parent->key[i] = parent->key[i-1];
				parent->chi[i+1] = parent->chi[i];
			} else {
				break ;
			}
		}
		parent->key[i] = key;
		parent->chi[i+1] = node_sub;
		node_sub->parent = parent;
		parent->nkey++;
	} else {
		temp = alloc_temp();
		for (i = 0; i < N-1; i++){
			temp->key[i] = parent->key[i];
			temp->chi[i] = parent->chi[i];
		}
		temp->chi[i] = parent->chi[i];
		insert_in_temp(temp, key, node_sub, NULL);
		for (i = 0; i < N-1; i++){
			parent->key[i] = 0;
			parent->chi[i] = NULL;
		}
		parent->nkey = 0;
		parent->chi[i] = NULL;
		new_parent = alloc_parent(NULL);
		for (i = 0; i < N/2; i++){
			parent->key[i] = temp->key[i];
			parent->chi[i] = temp->chi[i];
			parent->chi[i]->parent = parent;
			parent->nkey++;
		}
		parent->chi[i] = temp->chi[i];
		parent->chi[i]->parent = parent;
		for (i = 0; i < (N-1)/2; i++){
			new_parent->key[i] = temp->key[i + 1 + N/2];
			new_parent->chi[i] = temp->chi[i + 1 + N/2];
			new_parent->chi[i]->parent = new_parent;
			new_parent->nkey++;
		}
		new_parent->chi[i] = temp->chi[i + 1 + N/2];
		new_parent->chi[i]->parent = new_parent;
		insert_in_parent(parent, temp->key[N/2], new_parent);
		free(temp);
	}
}

void insert_in_leaf(NODE *node_main, int key, DATA *data){
	int i;

	for (i = node_main->nkey; i > 0; i--){
		if (node_main->key[i - 1] > key){
			node_main->key[i] = node_main->key[i - 1];
			node_main->data[i] = node_main->data[i - 1];
		} else {
			break ;
		}
	}
	node_main->key[i] = key;
	node_main->data[i] = data;
	node_main->nkey++;
}

void insert(int key, DATA *data){
	NODE *node_main, *node_sub;
	TEMP *temp;

	if (Root == NULL){
		node_main = alloc_leaf(NULL);
		Root = node_main;
	} else {
		node_main = find_leaf(Root, key);
		for (int i = 0; i < node_main->nkey; i++){
			if (node_main->key[i] == key){
				//printf("This key already exists.\n");
				return ;
			}
		}
	}
	if (node_main->nkey < N-1){
		insert_in_leaf(node_main, key, data);
	} else {
		node_sub = alloc_leaf(NULL);
		temp = alloc_temp();
		for (int i = 0; i < N-1; i++){
			temp->key[i] = node_main->key[i];
			temp->data[i] = node_main->data[i];
		}
		insert_in_temp(temp, key, NULL, data);
		node_sub->chi[N-1] = node_main->chi[N-1];
		node_main->chi[N-1] = node_sub;
		node_main->nkey = 0;
		node_sub->nkey = 0;
		for (int i = 0; i < N-1; i++){
			node_main->key[i] = 0;
			node_main->data[i] = NULL;
		}
		for (int i = 0; i < (N+1)/2; i++){
			node_main->key[i] = temp->key[i];
			node_main->data[i] = temp->data[i];
			node_main->nkey++;
		}
		for (int i = 0; i < N/2; i++){
			node_sub->key[i] = temp->key[i + (N+1)/2];
			node_sub->data[i] = temp->data[i + (N+1)/2];
			node_sub->nkey++;
		}
		insert_in_parent(node_main, node_sub->key[0], node_sub);
		free(temp);
	}
}

void init_root(void){
	Root = NULL;
}

int interactive(){
	int key;

	std::cout << "Key: ";
	std::cin >> key;

	return key;
}

int main(int argc, char *argv[]){
	int *arr;

	if (!(arr = (int *)malloc(sizeof(int) * DATA_SIZE))) ERR;
	init_root();
	for (int i = 0; i < DATA_SIZE; i++){
		arr[i] = DATA_SIZE - i;
		insert(arr[i], NULL);
	}
	/*for (int i = 0; i < DATA_SIZE; i++){
		arr[i] = i+1;
		insert(arr[i], NULL);
	}*/
	//print_tree(Root);
	for (int i = 0; i < DATA_SIZE; i++){
		if (!search_tree(Root, arr[i])){
			printf("Not found.\n");
		}
	}
	printf("Completed.\n");
	free(arr);
	return 0;
}