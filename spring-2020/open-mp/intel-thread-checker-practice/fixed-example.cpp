#include <stdio.h>

#ifdef _OPENMP
#include <omp.h>
#endif

#include <math.h>

#define N 11

double a[N];
double y,x;

int main(void){

  int i;
  // Change n. 1: Declaring shared resourced via private(...). It'd ...
  // ... prevent race condition while calculation shared argument (see change n.2).
  #pragma omp parallel for private(x, y, i)
  for (i = 0; i < N; i++)
  {
    // Change n. 2: Calculating shared argument for trigonometric functions.
    const int sharedArg = i/N*3.14;
    y = i*sin(sharedArg);
    x = i*cos(sharedArg);
    a[i] = y+x;
  }

  return 0;
}

