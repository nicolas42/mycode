#include <stdio.h>

// https://x.com/VicVijayakumar/status/1873089734521831852

int fizzbuzz_v1();
int fizzbuzz_v2();
  
int main(){
  fizzbuzz_v1();
  fizzbuzz_v2();
  return 0;
}

int fizzbuzz_v2(){
  // Version 2: Unecessary complications
  
  // Write a short program that prints each number from 1 to 100 on a new line. 
  //For each multiple of 3, print "Fizz" instead of the number. 
  //For each multiple of 5, print "Buzz" instead of the number.
  //For numbers which are multiples of both 3 and 5, print "FizzBuzz" instead of the number.
  int i;
  int fb; // have we printed fizz or buzz?
  for(i=1;i<=100;i+=1){
    fb=0;
    if (i%3==0) { printf("Fizz"); fb=1;}
    if (i%5==0) { printf("Buzz"); fb=1;}
    if(!fb) { printf("%d",i); }
    printf("\n");
  }

  return 0;
}


int fizzbuzz_v1(){

  int i=0;
  for(i=1;i<=100;i+=1){
    if (i%3==0 && i%5==0) { printf("FizzBuzz\n"); }
    else if (i%3==0) { printf("Fizz\n"); }
    else if (i%5==0) { printf("Buzz\n"); }
    else { printf("%d\n",i); }
  }
  return 0;
}
