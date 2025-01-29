// Binary Search Tree
// Uses dynamically sized memory using realloc.
// Tree Nodes are referenced by integer offsets so that the tree remains valid 

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct node {
  int value;
  int left; // -1 is null
  int right; // -1 is null
} Node;

typedef struct {
  Node* items;
  int count;
  int capacity;
  // int index;
} Node_Array;

void node_allocate(Node_Array* xs, Node x){            

  if (xs->count == xs->capacity) { 
    if (xs->capacity == 0) { xs->capacity = 10; }
    else { xs->capacity *= 2; }
    xs->items = realloc(xs->items, xs->capacity * sizeof(*xs->items)); 
  } 
  xs->items[xs->count++] = x; 
}


int tree_insert(Node_Array* na, int node_index, int data){

  if (node_index == -1){ 
    Node nnp = {.value=data, .left=-1, .right=-1};
    node_allocate(na, nnp);
    return na->count-1;
  }

  Node* np = &na->items[node_index];
  if (data < np->value) {
    np->left = tree_insert(na, np->left, data);
  }
  else if (data > np->value) {
    np->right = tree_insert(na, np->right, data);
  }

  return node_index;
}

void print_in_order(Node_Array* na, int node_index) {

  Node* np = &na->items[node_index];
  if (np->left!=-1) print_in_order(na, np->left);
  printf("%d ", np->value);
  //fprintf(stdout, "[ %d %d %d ] ", np->value, np->left, np->right); fflush(stdout);
  if (np->right!=-1) print_in_order(na, np->right);
}

void print_structs(Node_Array* na, int ni) {
  int i;
  for(i=0;i<na->count;i++) {
    printf("[%d %d %d] ", na->items[i].value, na->items[i].left, na->items[i].right);
  }
}

void print_recursive(Node_Array* na, int ni) {
  Node n = na->items[ni];
  printf("[");
  // print val
  printf("%d ", n.value);
  // if (left=-1){print[]} else { print_node(na, ni); }
  if (n.left==-1){printf("[] ");} else {print_recursive(na,n.left);}
  // if  (right=-1){print[]} else { print_node(na, ni); }
  if (n.right==-1){printf("[] ");} else {print_recursive(na,n.right);}  
  printf("] ");
}


int main(){

  Node_Array na = {0};
  int node_index = -1; // -1 is equivalent to NULL pointer.
  int i,r;
    
  for(i=0;i<20;i++) {
    r = rand() % 1001; // random integer from 0 to N
    printf("%d ", r);
    node_index = tree_insert(&na, node_index, r);
  }

  printf("\n\n\nprint in order\n");
  print_in_order(&na, 0);

  printf("\n\n\nPrint node structs\n");
  print_structs(&na,0);

  printf("\n\n\nprint recursive\n");
  print_recursive(&na, 0);
  
  return 0;
}



