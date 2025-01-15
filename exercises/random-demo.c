#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

  int i;

  srand((unsigned int)time(NULL)); // Seed with current time

  printf("time: %ld\n", time(NULL));
  for(i=0;i<10;i++) { printf("%d ", rand()); }
  printf("\n");
  
  printf("0 to rand_max: %d\n", rand());
  printf("0..1: %f\n", (double)rand() / (double)RAND_MAX);
  printf("0..100: %d\n", rand() % (100+1));


  return 0;
}


