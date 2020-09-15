#include <omp.h>
#include <stdio.h>
#include <math.h>

#define N 200

double a[N];
double y,x;

int main(void){

  int i;
  #pragma omp parallel for private(x, y, i)
  for (i = 0; i < N; i++)
  {
    int common = i/N*3.14;
    y = i*sin(common);
    x = i*cos(common);
    a[i] = y+x;
  }

  return 0;
}

