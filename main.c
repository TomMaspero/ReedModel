#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "vector.h"
#include "red.h"

int main(int argc, char *argv[])
{
    set_rand();
    int max_vecinos = 20, min_vecinos = 1, flag = 0, flag2 = 0, counter = 1, n_nodos = 0, n_steps = 0, tr = 0, aux_resultado = 0;
    float lambda = 5, beta_min = 0, beta_max = 0, beta_steps = 0, W = 0;
    char *filename;
    FILE *output;

    if (argc < 8) {
        printf("missing argument\n");
        exit(117);
    }

    n_nodos = atoi(argv[1]);
    tr = atoi(argv[2]);
    beta_min = atof(argv[3]);
    beta_max = atof(argv[4]);
    n_steps = atoi(argv[5]);
    W = atof(argv[6]);
    filename = strdup(argv[7]);

    network red;

    int resultados[n_steps], vueltas[n_steps];
    for(int i=0; i<n_steps; i++){
        resultados[i]=0;
        vueltas[i]=0;
    }
    int raiz_n = (int)sqrt(n_nodos);
    beta_steps = (beta_max - beta_min)/(n_steps-1);

    create_network(&red, n_nodos, max_vecinos, tr, W);

    for(int i=0; i<50; i++){
        flag = connect_network(&red, lambda, min_vecinos, max_vecinos);
        if(flag == 1){
            int k=0;
            for(float beta=beta_min; beta<beta_max + beta_steps; beta+=beta_steps){
                primer_infectado(&red);
                aux_resultado = infeccion(&red, beta);
                if(aux_resultado >= raiz_n){
                    resultados[k] += aux_resultado;
                    vueltas[k]+=1;
                }
                k++;
            }
            printf("Vuelta %d\n",i+1);
            printf("\n");
        }
    }
    output=fopen(filename,"a");

    for(int i=0; i<n_steps; i++){
        if(vueltas[i] == 0){
            printf("error, vueltas[%d] = 0\n", i);
            fprintf(output, "0, ");
        }
        else{
            printf("vector vueltas %d %d\n", i, vueltas[i]);
            fprintf(output,"%f, ", ((float)(resultados[i]/vueltas[i])/(float)n_nodos));
        }
    }
    fprintf(output, "\n");
    int M=0;
    double T = 0;
    for(float beta=beta_min; beta<beta_max + beta_steps; beta+=beta_steps){
        T = (1 - pow((double)(1 - beta), tr));
        fprintf(output, "%f, ", T);
        M++;
    }
    fprintf(output, "\n");
    fclose(output);

    free_network(&red);

    return 0;
}
