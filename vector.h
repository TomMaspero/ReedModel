#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifndef VECTOR_H
#define VECTOR_H

typedef struct vector{
    double x,y;
} vector;

vector vv(double x, double y);

vector add(vector v1, vector v2);

vector dif(vector v1, vector v2);

vector esc(vector v, double k);

double dot(vector v1, vector v2);

double cross(vector v1, vector v2);

double norm(vector v);

double norm2(vector v);

#endif
