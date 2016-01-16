//
//  QObject.hpp
//  Mesh
//
//  Created by Gary Wang on 16/1/14.
//  Copyright © 2016年 Gary Wang. All rights reserved.
//

#ifndef QObject_hpp
#define QObject_hpp

#include "SimpleObject.h"
#include "Duo.h"
//#include "Matr4.h"
#include <iostream>
#include <set>
#define THETA (5)
#endif /* QObject_hpp */

namespace SimpleOBJ {
    class QObject : public CSimpleObject
    {
    public:
        void initQ();
        void updateQ(int triangle);
        void deupdateQ(int triangle);
        void initPair();
        bool MergeOnePair();
        void DelVertex(int v1, int v0);
    private:
        Matr4 *Q;
        std::set<Duo> ss;
    };
}
