/*
 * Duo.h
 *
 *  Created on: 2016年1月11日
 *      Author: Gary
 */
#include "Matr4.h"

class Duo
{
public:
    int v0,v1;//v0 <= v1
    float cost;
//    Matr4 *Q;
    //	SimpleOBJ::Vec3f* prime;
    //public:
    Duo(int a0, int a1, double c0);
    bool operator < (const Duo & g) const;
};


