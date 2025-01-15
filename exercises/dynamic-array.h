#ifdef DYNAMIC_ARRAY_IMPLEMENTATION

// # Append in C.  dynamic array in C
// -------------------------------------------------
// macro from https://x.com/chessMan786/status/1872911193742164461
// Need to define array type with items, count, and capacity
// and then initialize.  

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
  int *items;
  size_t count;
  size_t capacity;
} Int_Array;

#define da_append(xs, x)            \
do { \
    if (xs.count == xs.capacity) { \
        if (xs.capacity == 0) xs.capacity = 256; \
        else xs.capacity *= 2; \
        xs.items = realloc(xs.items, xs.capacity * sizeof(*xs.items)); \
    } \
    xs.items[xs.count++] = x; \
} while (0)


int da_append_demo(void) {

  int x;
  size_t i;
  Int_Array xs = {0};

  for ( x = 0; x < 10; ++x) da_append(xs,x);
  for ( i = 0; i < xs.count; ++i) printf("%i\n", xs.items[i]);
  return 0;
}

int da_append_demo2() {
  int i,random_number;
  Int_Array int_array = {0};

  for(i=0;i<10;i++) {
    random_number = rand() % 101; // rand 0..100
    da_append(int_array,random_number);
  }
  for(i=0;i<10;i++) { printf("%d ", int_array.items[i]); }
  printf("\n");
  return 0;
}


#endif // DYNAMIC_ARRAY_IMPLEMENTATION
