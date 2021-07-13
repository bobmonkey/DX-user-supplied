#include <Rcpp.h>
#include <stdio.h>
#include <stdlib.h>
#include <R_ext/Random.h>
using namespace Rcpp;

#define K_MAX	3500
#define PP 2147483647  //2^31-1
#define B_X1 536869888 
#define K_X1 47
#define T_X1 1

unsigned long MODP(unsigned long z) {return ((((z)&PP)+((z)>>31)) &PP);}

static int I_X, K_X, T_X, B_X;

static Int32 XX[47];
static Int32 seed_in;
static Int32 seed[3];
static double res;
static int nseed = 3;

void DX_Init(Int32 seed_in)
{
  int i;
  T_X=T_X1;
  srand(seed_in);
  
  K_X=seed[1];
  B_X=seed[2];
  for (i=0; i<K_X; i++) XX[i] = rand() & PP;
  I_X=K_X-1;
  
  seed[0]=0;
}

double * user_unif_rand()
{
  if(seed[1] == 0 || seed[2] == 0){
    seed[1]=47; seed[2]=536869888;
  }
  if(seed[0] != 0){
    DX_Init((unsigned int)seed[0]);
  }
  
  int II0 = I_X;
  if(++I_X >= K_X)  I_X = 0;     
  XX[I_X] = MODP(B_X * XX[I_X] + XX[II0]);
  res = (double) XX[I_X] /(double) PP;
  return &res;
}

void  user_unif_init(Int32 seed_in) {
  seed[0] = seed_in;
}

int * user_unif_nseed() { return &nseed; }
int * user_unif_seedloc() { return (int *) &seed; }

