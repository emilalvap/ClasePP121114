#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define LIMIT 10000000 /* espacio de busqueda */

int main(){
    unsigned long long int i,j,limit;
    int *primes;
    int z = 1;
    
    limit = LIMIT;   
    primes = malloc(sizeof(int)*LIMIT);

    for (i=2;i<limit;i++)
        primes[i]=1;

    for (i=2;i<limit;i++)
        if (primes[i])
#pragma omp parallel for schedule(dynamic)
            for (j=i;i*j<limit;j++)
                primes[i*j]=0;

    for (i=2;i<limit;i++)
        if (primes[i])
            printf("%d-esimo primo = %lld\n",z++,i);

return 0;
}
