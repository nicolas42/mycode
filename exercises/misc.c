#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include "stdint_shortcuts.h"

void randseed(){
   srand(time(NULL));
}

double randf(){
  return (double)rand() / (double)RAND_MAX; // randf
}

int randn(int n){
  return rand() % (n+1); // randn
}


