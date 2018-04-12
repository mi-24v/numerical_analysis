#include <stdio.h>

int main(void){
 double x,y;
 int n;
 x = y = 0.0;
 y += 1.0;
 for(n=1; n<=200000; n++){
  x += 1.0e-17;//adding too small data
  y += 1.0e-17; 
 }
 x += 1.0;
 printf("x=%.15e\ny=%.15e\n", x, y);
}

