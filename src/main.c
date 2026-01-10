#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <math.h>

#define FIB_ITERATE_LIMIT 4000000
// i am writing this during new years 2025
// ok so this comment from when i was writing bubble sort but i gave up


int main(int argc, char *argv[]) {
  if (argc < 1) {
    printf("You must specify the limit for finding odd square sums");
    return -1;
  }
  unsigned long long int odd_square_sum = 0;
  printf("Now finding odd square sums below %u\n", atoi(argv[1]));

  for (unsigned long long int i = 1; i <= (unsigned long long) atoi(argv[1]); i++) {
    if ((i * i & 1) == 0) {
      continue;
    }
    odd_square_sum = odd_square_sum + (i * i);
  }

  printf("%llu", odd_square_sum);
  
  
}
