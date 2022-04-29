#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "vector.h"

#ifndef VECTOR_C
#define VECTOR_C

vector vv(double x, double y){
    vector vv={x,y};
    return vv;
}

vector add(vector v1, vector v2){
    vector add={v1.x + v2.x, v1.y + v2.y};
    return add;
}

vector dif(vector v1, vector v2){
    vector dif={v1.x - v2.x, v1.y - v2.y};
    return dif;
}

vector esc(vector v, double k){
    vector esc = {v.x * k, v.y *k};
    return esc;
}

double dot(vector v1, vector v2){
    double dot = v1.x * v2.x + v1.y * v2.y;
    return dot;
}

double cross(vector v1, vector v2){
    double cross = v1.x * v2.y - v1.y * v2.x;
    return cross;
}

double norm(vector v){
    double norm = sqrt(pow(v.x,2)+pow(v.y,2));
    return norm;
}

double norm2(vector v){
    double norm2 = pow(v.x,2)+pow(v.y,2);
    return norm2;
}

#endif
