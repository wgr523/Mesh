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
//#include "Matr4.h"
//#include "HalfEdge.cpp"
#include "Duo.h"
#define THETA (100)
namespace SimpleOBJ
{
    class TrivialObject : public CSimpleObject
    {
    public:
        void initPair();
        bool MergeOnePair();
        void DelVertex(int v1, int v0);
        void DelTriangle(int n);
    protected:
        bool* m_bBoundary;
        std::set<int> * m_pVertexToFace;
        std::set<Duo> ss;
    };
}
