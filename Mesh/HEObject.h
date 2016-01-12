//
//  HEObject.h
//  Mesh
//
//  Created by Gary Wang on 16/1/13.
//  Copyright © 2016年 Gary Wang. All rights reserved.
//
/*
 * TrivialObject.h
 *
 *  Created on: 2016年1月11日
 *      Author: Gary
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <utility>

#include "SimpleObject.h"
#include "Matr4.h"
#include "HalfEdge.cpp"
#include "Duo.cpp"
#define THETA (100)
namespace SimpleOBJ
{
    class HEObject : public CSimpleObject
    {
    public:
        void initHE();
        void showallHE();
        //	void initQ();
        void initPair();
        //	void updateQ(int triangle);
        //	void deupdateQ(int triangle);
        bool MergeOnePair();
        void DelVertex(int v1, int v0);
        //	void HeBing();
        
        //	Matr4 *Q;
    protected:
        int* m_pVertexToEdge;
        HE_edge* m_pHalfEdgeList;
        bool* m_bBoundary;
        //	std::vector<Duo> st;
        std::set<Duo> ss;
    };
}
