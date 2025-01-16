#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct node {
  int value;
  struct node* next;
};


struct node* insert(struct node* np, int data)
{

  // if the pointer is null then make a new one and return it so that it
  // is assigned to the pointer of the previous node.  
  if (np == NULL){
    struct node* nnp = malloc(sizeof(struct node));
    nnp->value = data;
    nnp->next = NULL;
    return nnp;
  }
  else {
    np->next = insert(np->next, data);
    return np;
  }

}

void print(struct node* np)
{

  printf("%d ", np->value);
  if (np->next!=NULL) print(np->next);
  
}

void demo1()
{
  struct node *head = NULL;
  int i,r;
  
  for(i=0;i<100;i++) {
    r = rand() % 10001;
    head = insert(head, r);
  }
  printf("\n\ninsert demo\n");
  print(head);

}


// Custom memory allocator.  No reallocation possible.
// -------------------------------------------------------------


static struct node memory[1000];
// static int memory_index = 0;
static int memory_count = 0;
static int memory_capacity = 1000;

struct node* alloc()
{
  memory_count += 1;
  return &memory[memory_count-1];
}

void insert2(struct node** npp, int data)
{
  
  if (*npp == NULL){
    struct node* nnp = alloc(); // malloc(sizeof(struct node));
    nnp->value = data;
    nnp->next = NULL;
    *npp = nnp;
  }
  else {
    struct node* np = *npp;
    insert2(&(np->next), data);
  }

}

void demo2()
{
  
  struct node *head = NULL;
  int i,r;
  
  for(i=0;i<100;i++) {
    r = rand() % 10001;
    insert2(&head, r);
  }
  printf("\n\ninsert2 demo\n");
  print(head);
  
}


int main(){
  srand(time(NULL));
  demo1();
  demo2();
  
  return 0;
}


