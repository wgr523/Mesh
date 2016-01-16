/*
 * Duo.cpp
 *
 *  Created on: 2016年1月11日
 *      Author: Gary
 */
#include "Duo.h"
Duo::Duo(int a0, int a1, double c0)
{
    v0=a0;v1=a1;cost=c0;//prime=p0;
    if (v1<v0) {int t;t=v0;v0=v1;v1=t;}
}
bool Duo::operator < (const Duo & g) const
{
//    Matr4 tmp = Q[v0]+Q[v1];
//    float x[4];
//    Matr4 fang =tmp.inducePrime().LU();
//    fang.SolveSP(x);
//    SimpleOBJ::Vec3f xx(x[0],x[1],x[2]);
//    float cost=tmp.inner(xx, xx);
//    
//    tmp = Q[v0]+Q[v1];
//    fang =tmp.inducePrime().LU();
//    if (fang.diagProd()>1e-6)
//        fang.SolveSP(x);
//    else
//    {
//        x[0]=x[1]=x[2]=0;
//    }
//    xx[0]=x[0];xx[1]=x[1];xx[2]=x[2];
//    float gcost=tmp.inner(xx, xx);
    if (cost==g.cost)
    {
        if (v0==g.v0)
            return v1<g.v1;
        return v0<g.v1;
    }
    return cost<g.cost;
}
//	bool operator == (const Duo & g) const
//	{
//		return v0==g.v0 && v1==g.v1;
//	}


