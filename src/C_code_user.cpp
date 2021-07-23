#include <Rcpp.h>
#include <stdio.h>
#include <stdlib.h>
#include <R_ext/Random.h>
using namespace Rcpp;

#define K_MAX	3500
#define PP 2147483647  //2^31-1
#define B_X1 536869888 
#define T_X1 1

unsigned long MODP(unsigned long z) {return ((((z)&PP)+((z)>>31)) &PP);}

static int I_X, K_X, T_X, B_X;
NumericVector K_X1;

static Int32 XX[47];
static Int32 seed_in;
static double res;
static Int32 seed[3];
static int nseed = 3;

void parameter(){
   Environment env = Environment::global_env();
   if(env["dx_k_value"]==R_NilValue) {K_X1=47;} else {K_X1=env["dx_k_value"];}
}

void DX_Init(Int32 seed_in)
{
  int i;
  T_X=T_X1;
  srand(seed_in);
  
  K_X=seed[1];
  B_X=seed[2];
  for (i=0; i<K_X; i++) XX[i] = rand() & PP;
  I_X=K_X-1;
}

double * user_unif_rand() {
  int II0 = I_X;
  if(++I_X >= K_X)  I_X = 0;     
  XX[I_X] = MODP(B_X * XX[I_X] + XX[II0]);
  res = (double) XX[I_X] /(double) PP;
  return &res;
}

void  user_unif_init(Int32 seed_in) {
  parameter();
  seed[0] = seed_in;
  seed[1]=K_X1[0]; 
  seed[2]=536869888;
  DX_Init((unsigned int)seed[0]);
}

int * user_unif_nseed() { return &nseed; }
int * user_unif_seedloc() { return (int *) &seed; }

