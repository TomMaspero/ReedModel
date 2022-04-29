#include <stdio.h>
#include <stdlib.h>
#include "red.h"
#include "vector.h"
#ifndef RED_C
#define RED_C

void set_rand(){
    srand(time(NULL));
    for(int i=0; i<100; i++){rand();}
}

float frand()
{
    float k=1.0*rand()/RAND_MAX;
    while(k==1)
        k=1.0*rand()/RAND_MAX;
    return k;
}

int krand(int n)
{
    int k=rand()%(n)+1; //le sumo 1 para que siempre exista una conexion como minimo
    return k;
}

int prand(float expectedValue, int kMin, int kMax){
    int k=0; //counter of iteration
    float limit;
    float x; //pseudo random number
    limit = exp(-expectedValue);
    x=1.0;
    while(x > limit){
        k++;
        x *= frand();
    }
    k--;
    if( k>= kMin && k <= kMax){
        return k;
    }
    else {return prand(expectedValue, kMin, kMax);}
}

void create_network(network *red, int n, int max_vecinos, int tr, float W){
    red->n_nodos = n;
    red->n_conexiones=0;
    red->max_vecinos = max_vecinos;
    red->tr = tr;
    red->W = W;

    red->nodos = (node*) calloc(red->n_nodos, sizeof(node));
    if(red->nodos==NULL){
        printf("error al asignar memoria a red\n");
        exit(117);
    }

    for(int i=0; i<red->n_nodos; i++){
        red->nodos[i].vecinos = (int*) calloc(max_vecinos, sizeof(int));
        if(red->nodos[i].vecinos==NULL){printf("error al asignar memoria a red.nodos en el vecino %d\n",i); exit(117);}
        red->nodos[i].w = frand();
    }

    red->infectados = (int*) calloc(red->n_nodos, sizeof(int));
    if(red->infectados==NULL){
        printf("error al asignar memoria a infectados\n");
        exit(117);
    }

    red->links = (int*) calloc (red->n_nodos * max_vecinos, sizeof(int));
    if(red->links==NULL){
        printf("error al asignar memoria a links\n");
        exit(117);
    }
}

void set_conexiones(network *red, float lambda, int min_vecinos, int max_vecinos){
    red->n_sus = red->n_nodos;
    red->n_inf = 0;
    red->n_rec = 0;
    red->dia = 0;
    red->n_conexiones=0;
    for(int i=0; i<red->n_nodos; i++){
        if(red->nodos[i].w <= red->W){
            red->nodos[i].n_vecinos = 0;
        }
        else{
            red->nodos[i].n_vecinos = prand(lambda, min_vecinos, max_vecinos);
        }
        red->nodos[i].status = SUS;
        red->nodos[i].t_inf = 0;

        for(int j=0; j<red->max_vecinos; j++){red->nodos[i].vecinos[j] = -1;}

        red->n_conexiones += red->nodos[i].n_vecinos;
    }
    red->n_links_desconectados = red->n_conexiones;
    if(red->n_links_desconectados%2 != 0){
        fdesconexiones(red);
        set_conexiones(red, lambda, min_vecinos, max_vecinos);
    }
}

int set_vecinos(network *red){
    int flag = 1;
    int k=0;
    for(int i=0; i<red->n_nodos; i++){
        for(int j=0; j<red->nodos[i].n_vecinos; j++){
            red->links[k] = i;
            k++;
        }
    }
    while(red->n_links_desconectados != 0){
        int v_rand1 = 0, v_rand2=0, k1=0, k2=0, contador=0, flag = 1, flagR=0; //v_rand para acortar vecino_random

            k1 = rand()%(red->n_links_desconectados);
            k2 = rand()%(red->n_links_desconectados);

            v_rand1 = red->links[k1];
            v_rand2 = red->links[k2];

            flagR = check_redundancy(red, v_rand1, v_rand2);
        contador=0;
        while(v_rand1 == v_rand2 || flagR == 0){
            k2 = rand()%(red->n_links_desconectados);
            v_rand2 = red->links[k2];
            flagR = check_redundancy(red, v_rand1, v_rand2);
            contador++;
            if(contador == 50){
                k1 = rand()%(red->n_links_desconectados);
                v_rand1 = red->links[k1];
                flagR = check_redundancy(red, v_rand1, v_rand2);
            }
            if(contador == 500){
                return flag = 0;
            }
        }

        red->nodos[v_rand1].vecinos[red->nodos[v_rand1].n_vecinos_conectados] = v_rand2;
        red->nodos[v_rand2].vecinos[red->nodos[v_rand2].n_vecinos_conectados] = v_rand1;

        red->nodos[v_rand1].n_vecinos_conectados++;
        red->nodos[v_rand2].n_vecinos_conectados++;

        red->links[k1] = red->links[(red->n_links_desconectados)-1]; //los pongo al final del vector links y acorto el vector links en 2 para que no se vuelvan a sortear
        red->links[k2] = red->links[(red->n_links_desconectados)-2];
        red->n_links_desconectados -= 2;
    }
    return flag = 1;
}

int connect_network(network *red, float lambda, int min_vecinos, int max_vecinos){
    int flag = 0, flag2 = 0, counter = 0;
    while(flag == 0 || flag2 == 0){
        if(counter > 0){fdesconexiones(red);}
        set_conexiones(red, lambda, min_vecinos, max_vecinos);
        flag2 = set_vecinos(red);
        flag = check_vecinos(red);
        counter++;
        printf("\b\b\b\b\b%d", counter);
    }
    printf("\n");
    fprintf_red(red);
    return flag;
}

int check_redundancy(network *red, int v_rand1, int v_rand2){
    int flagR = 1;
    for(int j=0; j<red->nodos[v_rand1].n_vecinos_conectados; j++){
        if(red->nodos[v_rand1].vecinos[j] == v_rand2){
            flagR = 0;
        }
    }
    return flagR;
}

int check_vecinos(network *red){
    int flag2 = 1;
    for(int i=0; i<red->n_nodos; i++){
        for(int j=0; j<red->nodos[i].n_vecinos; j++){
            if(red->nodos[i].vecinos[j] == -1){
                flag2 = 0;
            }
        }
    }
    return flag2;
}

void fdesconexiones(network *red){
    for(int i=0; i<red->n_nodos; i++){
        red->nodos[i].n_vecinos = 0;
        red->nodos[i].n_vecinos_conectados = 0;
    }
    red->n_conexiones = 0;
    red->n_links_desconectados = 0;
}

void print_red(network *red, int counter){
    for(int i=0; i<red->n_nodos; i++){
        printf("%d\t",i);
        for(int j=0; j<red->nodos[i].n_vecinos; j++){
            printf("%d, ",red->nodos[i].vecinos[j]);
        }
        printf("\n");
    }
    printf("numero de intentos %d\n", counter);
}

void fprintf_red(network *red){
    FILE *datos_red;
    datos_red=fopen("datos_red.txt","w");

    for(int i=0; i<red->n_nodos; i++){
        fprintf(datos_red,"%d\t",i);
        for(int j=0; j<red->nodos[i].n_vecinos; j++){
            fprintf(datos_red,"%d\t",red->nodos[i].vecinos[j]);
        }
        fprintf(datos_red,"\n");
    }
}

void primer_infectado(network *red){
    red->dia = 0;
    red->n_inf = 1;
    red->n_rec = 0;
    red->n_sus = red->n_nodos - 1;
    for(int i=0; i<red->n_nodos; i++){
        red->nodos[i].status = SUS;
        red->infectados[i] = 0;
    }
    int k=rand()%red->n_nodos;
    red->nodos[k].status = INF;
    red->infectados[0] = k;
}

int infeccion(network *red, float beta){

    int flag2 = 0, aux_inf = 0, aux_vecino_inf = 0, aux_ninf = 0;

    while(flag2 == 0){
        float p=0;
        if(red->n_inf == 0){flag2 = 1;}
        red->dia++;
        aux_ninf = red->n_inf;

        for(int i=0; i<aux_ninf; i++){
            aux_inf = red->infectados[i];
            for(int j=0; j<red->nodos[aux_inf].n_vecinos; j++){
                aux_vecino_inf = red->nodos[aux_inf].vecinos[j];
                p=frand();
                if(red->nodos[aux_vecino_inf].status == SUS && p <= beta){
                    red->nodos[aux_vecino_inf].status = INF;
                    red->n_inf++;
                    red->n_sus--;
                    red->infectados[red->n_inf - 1] = aux_vecino_inf;
                }
            }
            red->nodos[aux_inf].t_inf++;
        }
        for(int i=0; i<red->n_inf; i++){
            aux_inf = red->infectados[i];
            if(red->nodos[aux_inf].t_inf == red->tr){
                red->nodos[aux_inf].status = REC;
                red->n_rec++;
                red->nodos[aux_inf].t_inf = 0;
                red->infectados[i] = red->infectados[red->n_inf - 1]; //copio el del ultimo lugar y acorto la lista
                if(i != red->n_inf-1){
                    red->infectados[i] = red->infectados[red->n_inf-1];
                    i--;
                }
                red->n_inf--;
            }
        }
    }
    return red->n_rec;
}


void free_network(network *red){
    for(int i=0; i<red->n_nodos; i++){
        free(red->nodos[i].vecinos);
    }
    free(red->nodos);
    free(red->infectados);
    free(red->links);
}

#endif
