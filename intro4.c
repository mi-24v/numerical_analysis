#include <stdio.h>
#include <math.h>

void root(double* answers, double factor2, double factor1, double factorc){
 double discriminant = factor1 * factor1 - 4 * factor2 * factorc;
 if(discriminant < 0){
  printf("no real solution.\n");
  return;
 }else if(discriminant > 0){
  printf("real solution exists.\n");
  if(factor1 > 0){//supress gap loss
   answers[0] = (-factor1 + sqrt(discriminant))/(2 * factor2);
   answers[1] = factorc / (factor2 * answers[0]);
  }else{
   answers[0] = (-factor1 - sqrt(discriminant))/(2 * factor2);
   answers[1] = factorc / (factor2 * answers[0]);
  }
 }
}

int main(void){
 double a=0,b=0,c=0;
 double answers[2] = {};
 printf("type second order term's factor:");
 scanf("%lf", &a);
 printf("type first order term's factor:");
 scanf("%lf", &b);
 printf("type constant term:");
 scanf("%lf", &c);
 root(answers, a, b, c);
 printf("answers\nans1=%.16e\nans2=%.16e", answers[0], answers[1]);
}

