// clang fibonacci.c && ./a.out > out.txt && head out.txt | wc

#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <stdlib.h>

#define u64 uint64_t
// fibonacci numbers.
// 1 1 2 3 5 ...

int will_overflow(uint64_t a, uint64_t b) {
    return a > UINT64_MAX - b;
}


int main()
{
  size_t fibcap = 1000000;
  u64* fib = malloc(fibcap*sizeof(u64)); // fibonacci numbers
  size_t fibcount = 2;
  fib[0]=1;
  fib[1]=1;

  int i;
  clock_t start, end;
  double time_computation, time_fileio;
  start = clock();
  
  for(i=0;i<(fibcap-2);i++) {
        if (will_overflow(fib[i+1], fib[i+0])) {
            int overflow = 1;
	    printf("%llu %llu\n", fib[i+1], fib[i+0]);
            printf("Overflow will occur on the next addition. %d\n", i);
            break;
        }

    fib[i+2] = fib[i+1] + fib[i+0];
    fibcount++;
    /* if ((clock() - start) > CLOCKS_PER_SEC) { break; } */
  }

  end = clock();
  time_computation = ((double) (end - start)) / CLOCKS_PER_SEC;


  if (1) {
    printf("time_computation, fibcount, %f %zu\n", time_computation, fibcount);
    /* Print fibonacci sequence */
    /* printf("1 1 "); */
    /* for(i=0;i<100;i++) printf("%llu ", f[i+2]); */
    /* printf("...\n"); */
  }

if (0){
  FILE* file;
  size_t numread, numwritten;
  int numtowrite = 1000000, numtoread = 1000000;
  u64 buf[1000000] = {0};


  file = fopen("out.txt", "w");
  numwritten = fwrite(fib, sizeof(u64), numtowrite, file);
  if (numwritten != numtowrite ) {
    perror("Failed to write to file");
    fclose(file);
    return 1;
  }
  fclose(file);


  file = fopen("out.txt", "r");
  numread = fread(buf, sizeof(u64), numtoread, file);
  if (numread != numtoread) {
    perror("Failed to read");
    fclose(file);
    return 1;
  }
  fclose(file);


  for(i=0;i<numread;i++) printf("%llu ", buf[i]);
}
  return 0;
}


struct settings {
  int fileio;
  int time;
  int print;
};


int main1()
{
  struct settings s;
  s.fileio = 0;
  s.time   = 1;
  s.print  = 0;

  size_t fcount = 100000000;
  u64* f = malloc(fcount*sizeof(u64)); // fibonacci numbers
  f[0]=1;
  f[1]=1;

  int i;
  clock_t start, end;
  double time_computation, time_fileio;
  start = clock();
  
  for(i=0;i<(fcount-2);i++) {
    f[i+2] = f[i+1] + f[i+0];
  }

  end = clock();
  time_computation = ((double) (end - start)) / CLOCKS_PER_SEC;


  start = clock();
  if (s.fileio) {
    FILE* file;
    file = fopen("out.txt", "w");
    if (file == NULL) {
      printf("Error opening file!\n");
      return 1;
    }
    fprintf(file, "1 1 ");
    for(i=0;i<fcount;i++) fprintf(file, "%llu ", f[i+2]);
    fclose(file);
  }

  end = clock();
  time_fileio = ((double) (end - start)) / CLOCKS_PER_SEC;


  if (s.print) {
    fprintf(stdout, "1 1 ");
    for(i=0;i<fcount;i++) fprintf(stdout, "%llu ", f[i+2]);
  }

  if (s.time) {
    printf("Settings s.fileio %d, s.time %d, s.print %d\n", s.fileio, s.time, s.print );
    printf("Calculation - Time taken: %f seconds\n", time_computation);
    printf("Fileio - Time taken: %f seconds\n", time_fileio);
  }
  
  return 0;
}



int time_main() {
    clock_t start, end;
    double cpu_time_used;

    start = clock();
    
    // Code to be timed goes here
    for (int i = 0; i < 100000000; i++) {
        // Some operation
    }

    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("Time taken: %f seconds\n", cpu_time_used);

    return 0;
}
