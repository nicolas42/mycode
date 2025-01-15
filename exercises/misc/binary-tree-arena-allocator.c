// Binary search tree that uses an arena allocator.

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define ARENA_ALLOCATOR_IMPLEMENTATION
#include "arena_allocator.h"

Arena arena;

typedef struct node {
  int value;
  struct node *left;
  struct node *right;
} Node;

Node* tree_insert(Node* np, int data){

  if (np==NULL){
    // create and return new node pointer
    Node* nnp = (Node*)arena_alloc(&arena, sizeof(Node));o
    nnp->value = data;
    nnp->left = NULL;
    nnp->right = NULL;
    return nnp;
  }

  if (data < np->value) {
    np->left = tree_insert(np->left, data);
  }
  else if (data > np->value) {
    np->right = tree_insert(np->right, data);
  }

  return np;
}

void tree_print(Node *np) {

  if (np->left!=NULL) tree_print(np->left);
  printf("%d ", np->value);
  if (np->right!=NULL) tree_print(np->right);
  
}



int tree_demo(void){

  int ARENA_SIZE = 1000000;
  srand(time(NULL));
  arena_init(&arena, ARENA_SIZE*sizeof(Node));
  Node* np;
  
  np = (Node*)arena_alloc(&arena, sizeof(Node));
  np = NULL;

  int i, r;
  for(i=0;i<ARENA_SIZE;i++) {
    r = rand() % (ARENA_SIZE+1);
    np = tree_insert(np, r);
  }
  
  tree_print(np);

  arena_free(&arena);
  
  return 0;
}


int main(void){
  tree_demo();
  return 0;
}
