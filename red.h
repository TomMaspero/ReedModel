#ifndef RED_H
#define RED_H
#include "vector.h"
#define SUS 0
#define INF 1
#define REC 2

typedef struct node{
	int n_vecinos;
    int *vecinos;
    float w;
    int n_vecinos_conectados;
    int fallas;
    int status;
    int t_inf;
} node;

typedef struct network{
    int n_nodos;
    int max_vecinos;
    int n_inf;
    int n_sus;
    int n_rec;
    int n_conexiones;
    int n_links_desconectados;
    int *links;
    int *infectados;
    int dia;
    int tr;
    float W; //W es el parámetro de cuarentena
    node *nodos;
} network;

//sortea 100 números al azar para evitar que se elijan siempre los mismos números
void set_rand();

//genera números aleatorios entre 1 y n
int krand(int n);

//genera un float aleatorio entre 0 y 1
float frand();

//genera un int según la distribución de Poisson
int prand(float expectedValue, int kMin, int kMax);

//genera la red con n nodos y le pasa memoria al pointer de nodos
void create_network(network *red, int n, int max_vecinos, int tr, float W);

//determina el número de conexiones que tendrá cada nodo y chequea si el número de conexiones totales es un número par
void set_conexiones(network *red, float lambda, int min_vecinos, int max_vecinos);

//usando el vector links, asigna las conexiones entre los vecinos
int set_vecinos(network *red);

//conecta la red
int connect_network(network *red, float lambda, int min_vecinos, int max_vecinos);

//chequea si la red tiene conexiones redundantes
int check_redundancy(network *red, int v_rand1, int v_rand2);

//chequea si quedan nodos sin conectar
int check_vecinos(network *red);

//setea todos los enteros a cero y libera la memoria de los pointers
void fdesconexiones(network *red);

//printea la red en la consola
void print_red(network *red, int counter);

//printea la red a un txt
void fprintf_red(network *red);

//usando la funcion infectar desarrolla toda una infeccion hasta que hayan 0 cero nodos infectados
int infeccion(network *red, float beta);

void free_network(network *red);

#endif

