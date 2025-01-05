#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
  int *items;
  size_t count;
  size_t capacity;
} Int_Array;

// Binary tree node
typedef struct node {
  int value;
  struct node *left;
  struct node *right;
} Node;

typedef struct {
  Node *items;
  size_t count;
  size_t capacity;
} Node_Array;



// # Append in C.  dynamic array in C
// -------------------------------------------------
// macro from https://x.com/chessMan786/status/1872911193742164461

#define da_append(xs, x)			\
do { \
    if (xs.count == xs.capacity) { \
        if (xs.capacity == 0) xs.capacity = 256; \
        else xs.capacity *= 2; \
        xs.items = realloc(xs.items, xs.capacity * sizeof(*xs.items)); \
    } \
    xs.items[xs.count++] = x; \
} while (0)

int da_append_demo(void) {

  Int_Array xs = {0};
  for (int x = 0; x < 10; ++x) da_append(xs,x);
  for (int i = 0; i < xs.count; ++i) printf("%i\n", xs.items[i]);
  return 0;
}


  /*
  // append demo
  
  int i,random_number;
  Int_Array int_array = {0};

  for(i=0;i<10;i++) {
    random_number = rand() % 101; // rand 0..100
    da_append(int_array,random_number);
  }
  for(i=0;i<10;i++) { printf("%d ", int_array.items[i]); }
  printf("\n");
  */


// # Binary Tree
// -------------------------------------------

Node* insert(Node* node, int data){

  if (node==NULL){
    // create and return node
    Node* np = (Node*)malloc(sizeof(Node));
    np->value = data;
    np->left = NULL;
    np->right = NULL;    
  }

  if (data < node->left) {
    node->left = insert(node->left, data);
  }
  else if (data > node->right) {
    node->right = insert(node->right, data);
  }
  // else do nothing and just return the same node as below.
  
  return node;
}

int main(){  
  int int_array[] = {234,23,42,34,23,53,45,345,345,234,12,312,3,345,345,46,576,4567,346,354243};
  int len = sizeof(int_array) / sizeof(int);
  printf("%d\n", len);

  // Insert stuff into binary tree.
  // A binary tree works by putting things that are lower on the left side and things that are higher on the right side.
  // Where are we going to put everything? I don't know.  I guess in some memory.
  // To create a binary tree, you have to insert things into a binary tree.  To create, first

  Node node_array[1000] = {0};


  Node *np = NULL;

  
  return 0;
}






// # Learning about rand() and related stuff 
// ---------------------------------------------------------

double n_random() {
  // random() collides with something in macos :(
  return (double)rand() / (double)RAND_MAX;
}

int demo_rand() {
  // rand() needs to be seeded often with    srand(time(NULL)).  after that it'll output zero to rand_max.
  // random float from zero to one:          (double)rand() / (double)rand_max
  // integers from zero to n inclusive:      rand() % (n+1).  

  srand(time(NULL)); // Seed with current time

  int i;
  printf("time: %ld\n", time(NULL));
  for(i=0;i<10;i++) { printf("%d ", rand()); }
  printf("\n");
  
  printf("0 to rand_max: %d\n", rand());
  printf("0..1: %f\n", (double)rand() / (double)RAND_MAX);
  printf("0..100: %d\n", rand() % (100+1));


  return 0;
}


