/*
 * Duo.cpp
 *
 *  Created on: 2016年1月11日
 *      Author: Gary
 */
#include "Vec3f.h"
class Duo
{
//	protected:
public:
	int v0,v1;//v0 <= v1
	float cost;
//	SimpleOBJ::Vec3f* prime;
//public:
	Duo(int a0, int a1, float c0)
    {
		v0=a0;v1=a1;cost=c0;//prime=p0;
		if (v1<v0) {int t;t=v0;v0=v1;v1=t;}
	}
	bool operator < (const Duo & g) const
	{
		return cost<g.cost;
	}
//	bool operator == (const Duo & g) const
//	{
//		return v0==g.v0 && v1==g.v1;
//	}
};


