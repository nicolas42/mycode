// Currently realloc will break this code since it'll invalidate the pointers.
// Recode using pointer offsets instead of pointers.

// clang -fsanitize=address -Wall -Wpedantic -Wno-strict-prototypes binary-tree.c

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//#define DYNAMIC_ARRAY_IMPLEMENTATION
//#include "dynamic-array.h"

// Binary Tree Demo
// ---------------------------------------------------------
//
// 

// Binary tree node
typedef struct node {
  double value;
  struct node *left;
  struct node *right;
} Node;

typedef struct {
  Node *items;
  size_t count;
  size_t capacity;
} Node_Array;

void append_node(Node_Array *xs, Node *x) {
    if (xs->count == xs->capacity) { 
        if (xs->capacity == 0) xs->capacity = 256; 
        else xs->capacity *= 2; 
        xs->items = realloc(xs->items, xs->capacity * sizeof(*xs->items));    } 
    xs->items[xs->count++] = *x; 
}


Node* insert_node(Node* np, double data, Node_Array *node_array){

  if (np==NULL){
    // create and return new node pointer
    Node nnp = { .value=data, .left=NULL, .right=NULL };
    append_node(node_array, &nnp); 
    return &(node_array->items[node_array->count-1]);
  }

  if (data < np->value) {
    np->left = insert_node(np->left, data, node_array);
  }
  else if (data > np->value) {
    np->right = insert_node(np->right, data, node_array);
  }

  return np;
}

void print_tree(Node *np) {

  if (np->left!=NULL) print_tree(np->left);
  printf("%f ", np->value);
  if (np->right!=NULL) print_tree(np->right);
}



// rand() returns an integer up to RAND_MAX
//  srand((unsigned int)time(NULL)); // Seed with current time
// time() returns current time as a long integer

double randf() {
  return (double)rand() / (double)RAND_MAX;
}

  
int main(){
  srand((unsigned int)time(NULL));

  Node_Array na = {0};

  Node *np = NULL;
  int i;
  double r;
  for(i=0;i<200;i++){
    r = randf();
    np = insert_node(np, r, &na);
  }


  print_tree(np);
    
  return 0;
}


