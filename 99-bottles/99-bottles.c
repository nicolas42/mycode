#include <stdio.h>

int main(void)
{       
  int b;
  
  for (b = 99; b >= 3; b=b-1) {
    printf("%d bottles of beer on the wall, %d bottles of beer.\n", b, b);      
    printf("Take one down and pass it around, %d bottles of beer on the wall.\n\n", b - 1);
  }

  printf("2 bottles of beer on the wall, 2 bottles of beer.\n");
  printf("Take one down and pass it around, 1 bottle of beer on the wall\n\n");
  b=b-1;

  printf("1 bottle of beer on the wall, 1 bottle of beer.\n");
  printf("Take one down and pass it around, no more bottles of beer on the wall\n\n");
  b=b-1;
  
  printf("No more bottles of beer on the wall, no more bottles of beer.\n");
  printf("Go to the store and buy some more, 99 bottles of beer on the wall.\n\n");

  
  return 0;
}
