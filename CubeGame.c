
#include <stdio.h>
#include <stdlib.h>

#define M 5
#define K1 3
#define K2 2
#define True 1
#define False 0


typedef struct node{
	int id; 
	int red;
	int green;
	int min;
	int max;
	int fs;
	int parent;
	int val;
	int num_child;
	int move;
	int child[4];
}Node;

Node *tree;
int size_of_tree;

void initiate_root(){
	tree[0].red = M;
	tree[0].green = M;
	tree[0].min = False;
	tree[0].max = True;
	tree[0].fs = False;
	tree[0].id = 0;
	tree[0].parent = -1;
	tree[0].val = 0;
	tree[0].num_child;
	size_of_tree++;
}


void minimax(){
	int i;
	for(i=size_of_tree-1; i>0; i--){
		if(tree[tree[i].parent].val == 0){
			tree[tree[i].parent].val = tree[i].val;
		}	
		else{
			if(tree[tree[i].parent].min == True){
				if(tree[tree[i].parent].val > tree[i].val){
					tree[tree[i].parent].val = tree[i].val;
				}
			}else{
				if(tree[tree[i].parent].val < tree[i].val){
					tree[tree[i].parent].val = tree[i].val;
				}
			}
		}
	}
}


void create_tree(Node *nd){
	int children = 0,i;
	for(i=0; i<4; i++){
		nd->child[i]=-1;
	}
	if (nd->red>=K1){
		children++;
		size_of_tree++;
		tree[size_of_tree-1].move = 1;
		tree[size_of_tree-1].id = size_of_tree - 1;
		tree[size_of_tree-1].red = nd->red-K1;
		tree[size_of_tree-1].green = nd->green;
		if (nd->min==True){
			tree[size_of_tree-1].min = False;
			tree[size_of_tree-1].max = True;
		}else{
			tree[size_of_tree-1].min = True;
			tree[size_of_tree-1].max = False;
		}
		if(tree[size_of_tree-1].red + tree[size_of_tree-1].green == 0){ 
			tree[size_of_tree-1].fs = True;
			if (nd->max == True){
				tree[size_of_tree-1].val = 1;
			}else{
				tree[size_of_tree-1].val = -1;
			}
		}
		tree[size_of_tree-1].parent = nd->id;
		nd->child[0] = size_of_tree-1;
		if(tree[size_of_tree-1].val == 0){
			create_tree(&(tree[size_of_tree-1]));
		}
	}
	
	if (nd->green>=K2){
		children++;
		size_of_tree++;
		tree[size_of_tree-1].move = 2;
		tree[size_of_tree-1].id = size_of_tree - 1;
		tree[size_of_tree-1].red = nd->red;
		tree[size_of_tree-1].green = nd->green-K2;
		if (nd->min==True){
			tree[size_of_tree-1].min = False;
			tree[size_of_tree-1].max = True;
		}else{
			tree[size_of_tree-1].min = True;
			tree[size_of_tree-1].max = False;
		}
		if(tree[size_of_tree-1].red + tree[size_of_tree-1].green == 0){ 
			tree[size_of_tree-1].fs = True;
			if (nd->max == True){
				tree[size_of_tree-1].val = 1;
			}else{
				tree[size_of_tree-1].val = -1;
			}
		}
		tree[size_of_tree-1].parent = nd->id;
		nd->child[1] = size_of_tree-1;
		if(tree[size_of_tree-1].val == 0){
			create_tree(&(tree[size_of_tree-1]));
		}
	}
	if (nd->red>=1){
		children++;
		size_of_tree++;
		tree[size_of_tree-1].move = 3;
		tree[size_of_tree-1].id = size_of_tree - 1;
		tree[size_of_tree-1].red = nd->red -1;
		tree[size_of_tree-1].green = nd->green;
		if (nd->min==True){
			tree[size_of_tree-1].min = False;
			tree[size_of_tree-1].max = True;
		}else{
			tree[size_of_tree-1].min = True;
			tree[size_of_tree-1].max = False;
		}
		if(tree[size_of_tree-1].red + tree[size_of_tree-1].green == 0){ 
			tree[size_of_tree-1].fs = True;
			if (nd->max == True){
				tree[size_of_tree-1].val = 1;
			}else{
				tree[size_of_tree-1].val = -1;
			}
		}
		tree[size_of_tree-1].parent = nd->id;
		nd->child[2] = size_of_tree-1;
		if(tree[size_of_tree-1].val == 0){
			create_tree(&(tree[size_of_tree-1]));
		}
	}
	if (nd->green>=1){
		children++;
		size_of_tree++;
		tree[size_of_tree-1].move = 4;
		tree[size_of_tree-1].id = size_of_tree - 1;
		tree[size_of_tree-1].red = nd->red;
		tree[size_of_tree-1].green = nd->green-1;
		if (nd->min==True){
			tree[size_of_tree-1].min = False;
			tree[size_of_tree-1].max = True;
		}else{
			tree[size_of_tree-1].min = True;
			tree[size_of_tree-1].max = False;
		}
		if(tree[size_of_tree-1].red + tree[size_of_tree-1].green == 0){ 
			tree[size_of_tree-1].fs = True;
			if (nd->max == True){
				tree[size_of_tree-1].val = 1;
			}else{
				tree[size_of_tree-1].val = -1;
			}
		}
		tree[size_of_tree-1].parent = nd->id;
		nd->child[3] = size_of_tree-1;
		if(tree[size_of_tree-1].val == 0){
			create_tree(&(tree[size_of_tree-1]));
		}
	}
	nd->num_child = children;
}	


void game(){
	int choice,i;
	int turn = True;
	int position = 0; 
	while(1){
		printf("----------------------------------------------------------------------------------------------\n");
		printf("Remain %d green cubes and %d red cubes!\n",tree[position].green,tree[position].red);
		if(turn){
			printf("Computer's turn!\n");
			for(i=0; i<4; i++){
				if(tree[tree[position].child[i]].val==1){
					position = tree[position].child[i];
					if(tree[position].move == 1){
						printf("Removed %d red cubes!\n",K1);
					}else if(tree[position].move == 2){
						printf("Removed %d green cubes!\n",K2);
					}else if(tree[position].move == 3){
						printf("Removed 1 red cube!\n");
					}else{
						printf("Removed 1 green cube!\n");
					}	
					break;
				}
			}
			turn = False;
		}else{
			printf("Your turn!\n");
			printf("Choices: \n1. %d red\n2. %d green\n3. 1 red\n4. 1 green\n",K1,K2);
			scanf("%d",&choice);
			if(choice == 1){
				if(tree[position].red<K1){
					printf("Invalid choice. Play again!\n");
					continue;
				}else{
					position = tree[position].child[choice-1];
					printf("Removed %d red cubes!\n",K1);
				}
			}else if(choice == 2){
				if(tree[position].green<K2){
					printf("Invalid choice. Play again!\n");
					continue;
				}else{
					position = tree[position].child[choice-1];
					printf("Removed %d green cubes!\n",K2);
				}
			}else if(choice == 3){
				if(tree[position].red<1){
					printf("Invalid choice. Play again!\n");
					continue;
				}else{
					position = tree[position].child[choice-1];
					printf("Removed 1 red cube!\n");
				}
			}else{
				if(tree[position].green<1){
					printf("Invalid choice. Play again!\n");
					continue;
				}else{
					position = tree[position].child[choice-1];
					printf("Removed 1 green cube!\n");
				}
			}
			turn = True;
		}
		if(tree[position].green + tree[position].red == 0){
			printf("Game over!\n");
			if(turn==False){
				printf("Computer wins!\n");
			}else{
				printf("You won!\n");
			}
			break;
		}
	}
	
}


int main(){
	int i;
	tree = (Node*) malloc(50000*sizeof(Node));
	if (tree == NULL){
		printf("malloc error");
		exit(1);
	}
	initiate_root();
	create_tree(&(tree[0]));
	printf("\n");
	minimax();
	game();
	free(tree);
	return 0;
}
	

