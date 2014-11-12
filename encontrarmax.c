#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define SIZE 100000000

int array[SIZE];



int maximo_critical(int argc, char **argv){
  //es muy lento
  int maximo = 0;    
  int i;
    //inicializar array A
 
  for(i=0;i<SIZE;i++){
    array[i]=i;
    }
#pragma omp parallel for
    for(i=0; i < SIZE; i++){
#pragma omp critical (maxlock)
        if (array[i] > maximo) maximo = array[i];
    }
    printf("el maximo es %d",maximo);
    
    return 0;
}
int main(int argc, char **argv){
  int maximo = 0;    
  int i;
  int maximos[8];
    //inicializar array A
 
  for(i=0;i<SIZE;i++){
    array[i]=i;
    }

#pragma omp parallel for private(maximo)
    for(i=0; i < SIZE; i++){
      if (array[i] > maximo){
	maximo = array[i];
	maximos[omp_get_thread_num()]=maximo;
      }
    }
    for(i=0;i<8;i++){
      if (maximos[i] > maximo){
	printf("indice %d maximo %d\n",i,maximos[i]);
	maximo = maximos[i];
      }
    }
    printf("el maximo es %d\n",maximo);
    
    return 0;
}
