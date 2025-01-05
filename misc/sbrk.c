#include <stdio.h>
#include <unistd.h>
#include <errno.h>

int main() {

    // Get the current program break
    void *initial_brk = sbrk(0);
    if (initial_brk == (void *)-1) {
        perror("sbrk failed");
        return 1;
    }
    printf("Initial program break: %p\n", initial_brk);

    // Allocate 4 KB of memory
    void *new_brk = sbrk(1*1024*1024);
    if (new_brk == (void *)-1) {
      printf("[ERROR] %s %d\n ", __FILE__, __LINE__);
      perror("zomg");
        return 1;
    }
    printf("Program break after allocation: %p\n", sbrk(0));

    // Deallocate 4 KB of memory
    if (sbrk(-1*1024*1024) == (void *)-1) {
        perror("sbrk failed to deallocate memory");
        return 1;
    }
    printf("Program break after deallocation: %p\n", sbrk(0));

    return 0;
}
