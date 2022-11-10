#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct binary_object{
	int	key;
	struct binary_object *left;
	struct binary_object *right;
	struct binary_object *p;
} binary_object;

typedef struct root{
	binary_object *root;
} root;

void inorder_tree_walk(binary_object *x);
binary_object *iterative_tree_serarch(binary_object *x, int k);
binary_object *tree_minimum(binary_object *x);
binary_object *tree_maximum(binary_object *x);
binary_object *tree_successor(binary_object *x);
binary_object *tree_predecessor(binary_object *x);
void tree_insert(root *T, int new_key);
void tree_delete(root *T, binary_object *z);
void transplant(root *T, binary_object *u, binary_object *v);



void inorder_tree_walk(binary_object *x){
	if (x != NULL){
		inorder_tree_walk(x->left);
		printf("%d, ", x->key);
		inorder_tree_walk(x->right);
	}
}

binary_object *iterative_tree_serarch(binary_object *x, int k){
	while (x != NULL && k != x->key){
		if (k < x->key){
			x = x->left;
		} else {
			x = x->right;
		}
	}
	return x;
}

binary_object *tree_minimum(binary_object *x){
	while (x->left != NULL){
		x = x->left;
	}
	return x;
}

binary_object *tree_maximum(binary_object *x){
	while (x->right != NULL){
		x = x->right;
	}
	return x;
}

binary_object *tree_successor(binary_object *x){
	binary_object *y;

	if (x->right != NULL){
		return tree_minimum(x->right);
	}
	y = x->p;
	while (y != NULL && x == y->right){
		x = y;
		y = y->p;
	}
	return y;
}

binary_object *tree_predecessor(binary_object *x){
	binary_object *y;

	if (x->left != NULL){
		return tree_maximum(x->left);
	}
	y = x->p;
	while (y != NULL && x == y->left){
		x = y;
		y = y->p;
	}
	return y;
}

void tree_insert(root *T, int new_key){
	binary_object *x, *y, *z;

	y = NULL;
	x = T->root;
	z = malloc(sizeof(binary_object));
	z->key = new_key;
	z->right = NULL;
	z->left = NULL;
	z->p = NULL;
	while (x != NULL){
		y = x;
		if (z->key < x->key){
			x = x->left;
		} else {
			x = x->right;
		}
	}
	z->p = y;
	if (y == NULL){
		T->root = z;
	} else if (z->key < y->key){
		y->left = z;
	} else {
		y->right = z;
	}
}

void tree_delete(root *T, binary_object *z){
	binary_object *y;

	if (z->left == NULL){
		transplant(T, z, z->right);
	} else if (z->right == NULL){
		transplant(T, z, z->left);
	} else {
		y = tree_minimum(z->right);
		if (y->p != z){
			transplant(T, y, y->right);
			y->right = z->right;
			y->right->p = y;
		}
		transplant(T, z, y);
		y->left = z->left;
		y->left->p = y;
	}
	free(z);
}

void transplant(root *T, binary_object *u, binary_object *v){
	if (u->p == NULL){
		T->root = v;
	} else if (u == u->p->left){
		u->p->left = v;
	} else {
		u->p->right = v;
	}
	if (v != NULL){
		v->p = u->p;
	}
}

int main(void){
	root *T;
	int	new_key;
	binary_object *max, *min;
	char ope;
	int	arr[1000000];

	max = malloc(sizeof(binary_object));
	min = malloc(sizeof(binary_object));
	T = malloc(sizeof(root));
	T->root = NULL;
	/*scanf("%c %d", &ope, &new_key);
	while (new_key != 0){
		if (ope == 'i'){
			tree_insert(T, new_key);
		} else {
			if (iterative_tree_serarch(T->root, new_key) != NULL){
				tree_delete(T, iterative_tree_serarch(T->root, new_key));
			}
		}
		//printf("max:%d\nmin:%d\n=========\n", tree_maximum(T->root)->key, tree_minimum(T->root)->key);
		inorder_tree_walk(T->root);
		printf("\n=========\n");
		rewind(stdin);
		scanf("%c %d", &ope, &new_key);
	}*/
	for (int i = 0; i < 1000000; i++){
		//arr[i] = rand() % 1000000;
		tree_insert(T, i);
		printf("%d, ", i);
	}
	printf("\n");
	for (int i = 0; i < 1000000; i++){
		if (iterative_tree_serarch(T->root, arr[i])->key != i){
			printf("error\n");
			exit(0);
		}
		printf("%d, ", i);
	}
	printf("success\n");
	//inorder_tree_walk(T->root);
	return 0;
}