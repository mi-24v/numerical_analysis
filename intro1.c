#include <stdio.h>

void main(void){
 int i;
 float x=0.1f,sum=0.0f;
 double dx=0.1,dsum=0.0;

 for(i=1; i<10000; i++){
  sum += x;
  dsum += dx;
 }
 printf("float:%20.15f\ndouble:%20.15f\n",sum,dsum);
}
