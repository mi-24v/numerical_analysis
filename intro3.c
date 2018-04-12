#include <stdio.h>
#include <limits.h>

int main(void){
 char m;
 int n;
 m = SCHAR_MAX;
 n = INT_MAX;
 printf("m=%d, n=%d\n", m, n);
 m++;
 n++;
 printf("m=%d, n=%d\n", m, n);
}
