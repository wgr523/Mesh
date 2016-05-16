//
//  HEObject.h
//  Mesh
//
//  Created by Gary Wang on 16/1/13.
//  Copyright © 2016年 Gary Wang. All rights reserved.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <utility>

#include "TrivialObject.h"
//#include "Matr4.h"
#include "HalfEdge.cpp"
//#include "Duo.h"
namespace SimpleOBJ
{
    class HEObject : public TrivialObject
    {
    public:
//        void checkSelfEdge();
        void Destroy();
        void initHE();
        void initPair();
//        void showallHE();
        bool MergeOnePair();
        void DelVertex(int v1, int v0);
    private:
        int* m_pVertexToEdge;
        HE_edge* m_pHalfEdgeList;
        bool* m_bBoundary;
    protected:
        std::set<Duo> ss;
    };
}
