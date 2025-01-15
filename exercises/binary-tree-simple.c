#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct node {
  int value;
  struct node *left;
  struct node *right;
} Node;


Node* insert(Node* np, int data){

  if (np == NULL){
    Node* nnp = malloc(sizeof(Node));
    nnp->value = data;
    nnp->left = NULL;
    nnp->right = NULL;
    return nnp;
  }

  if (data < np->value) {
    np->left = insert(np->left, data);
  }
  else if (data > np->value) {
    np->right = insert(np->right, data);
  }

  return np;
}

void printtree(Node *np) {

  if (np->left!=NULL) printtree(np->left);
  printf("%d ", np->value);
  if (np->right!=NULL) printtree(np->right);
}

int main(){

  Node *np = NULL;
  int i,r;
  
  for(i=0;i<100;i++) {
    r = rand() % 10001;
    np = insert(np, r);
  }

  printtree(np);
  
  return 0;
}


