////
////  QObject.cpp
////  Mesh
////
////  Created by Gary Wang on 16/1/14.
////  Copyright © 2016年 Gary Wang. All rights reserved.
////
//
//#include "QObject.hpp"
//namespace SimpleOBJ {
//    void QObject::updateQ(int triangle)
//    {
//        //            int v0=m_pTriangleList[triangle][c],v1=m_pTriangleList[triangle][(c+1)%3],v2=m_pTriangleList[triangle][(c+2)%3];
//        int v0=m_pTriangleList[triangle][0],v1=m_pTriangleList[triangle][1],v2=m_pTriangleList[triangle][2];
//        Vec3f e1,e2;
//        e1=m_pVertexList[v1]-m_pVertexList[v0];e2=m_pVertexList[v2]-m_pVertexList[v0];
//        Vec3f norm(
//                   e1.z*e2.y-e1.y*e2.z,
//                   e2.x*e1.z-e2.z*e1.x,
//                   e1.x*e2.y-e1.y*e2.x
//                   );
//        norm.Normalize();
//        Vec3f tmp = norm*m_pVertexList[v0];
//        float d=-(tmp.x+tmp.y+tmp.z);
//        Matr4 up(norm,d);
//        for (int c=0;c<3;c++)
//        {
//            Q[m_pTriangleList[triangle][c] ]+= up;
//        }
//    }
//    void QObject::deupdateQ(int triangle)
//    {
//        //            int v0=m_pTriangleList[triangle][c],v1=m_pTriangleList[triangle][(c+1)%3],v2=m_pTriangleList[triangle][(c+2)%3];
//        int v0=m_pTriangleList[triangle][0],v1=m_pTriangleList[triangle][1],v2=m_pTriangleList[triangle][2];
//        Vec3f e1,e2;
//        e1=m_pVertexList[v1]-m_pVertexList[v0];e2=m_pVertexList[v2]-m_pVertexList[v0];
//        Vec3f norm(
//                   e1.z*e2.y-e1.y*e2.z,
//                   e2.x*e1.z-e2.z*e1.x,
//                   e1.x*e2.y-e1.y*e2.x
//                   );
//        norm.Normalize();
//        Vec3f tmp = norm*m_pVertexList[v0];
//        float d=-(tmp.x+tmp.y+tmp.z);
//        Matr4 up(norm,d);
//        for (int c=0;c<3;c++)
//        {
//            Q[m_pTriangleList[triangle][c] ]-= up;
//        }
//    }
//    
//    void QObject::initQ()
//    {
//        Q = new Matr4 [m_nVertices];
//        for (int i=0;i<m_nTriangles;i++)
//        {
//            updateQ(i);
//        }
//        std::cout<<"init Q ok!\n";
//    }
//    void QObject::initPair()
//    {
//        std::set<std::pair<int,int> > record;
//        ss.clear();
//        for (int i=0;i<m_nTriangles;i++)
//        {
//            int v[3];
//            v[0]=m_pTriangleList[i][0]; v[1]=m_pTriangleList[i][1]; v[2]=m_pTriangleList[i][2];
//            for (int c=0;c<3;c++)
//            {
//                if (record.find(std::make_pair(v[c],v[(c+1)%3]) )==record.end() )
//                {
//                    record.insert(std::make_pair(v[c],v[(c+1)%3]));
//                    record.insert(std::make_pair(v[(c+1)%3],v[c]));
//                    float distan=(m_pVertexList[v[c]]-m_pVertexList[v[(c+1)%3]]).L2Norm_Sqr();
//                    if ( distan < THETA )
//                    {
//                        Duo duo(v[c],v[(c+1)%3],Q);
//                        ss.insert(duo);
//                    }
//                }
//            }
//        }
//        std::cout<<"init Pair ok!\n";
//    }
//    bool QObject::MergeOnePair()
//    {
//        std::set<Duo>::iterator it;
//        while (!ss.empty())
//        {
//            it=ss.begin();
//            int v0=it->v0,v1=it->v1;
//            ss.erase(it);
//            if (m_bVertexDel[v0] || m_bVertexDel[v1]) continue;
//            Matr4 tmp = Q[v0]+Q[v1];
//            float x[4];
//            Matr4 fang =tmp.inducePrime().LU();
//            fang.SolveSP(x);
//            Vec3f xx(x[0],x[1],x[2]);
//            DelVertex(v1,v0);
//            m_pVertexList[v0]=xx;
//            for (int i=0;i<m_nTriangles;i++)
//                if (!m_bTriangleDel[i]) {
//                    int lindex = m_pTriangleList[i].findindex(v0);
//                    if (lindex!=-1)
//                        updateQ(i);
//                }
//            return true;
//        }
//        return false;
//    }
//    void QObject::DelVertex(int v1, int v0) //v0:replace must be before n
//    {
//        m_bVertexDel[v1]=true;
//        for (int i=0;i<m_nTriangles;i++)
//            if (!m_bTriangleDel[i]) {
//                int rindex = m_pTriangleList[i].findindex(v1);
//                int lindex = m_pTriangleList[i].findindex(v0);
//                if (lindex!=-1)
//                    deupdateQ(i);
//                
//                if ( rindex!=-1 )
//                {
//                    if (lindex!=-1) DelTriangle(i);
//                    else
//                    {
//                        deupdateQ(i);
//                        int p;
//                        if (rindex!=0)
//                        {
//                            p=m_pTriangleList[i][0];
//                            float distan=(m_pVertexList[v0]-m_pVertexList[p]).L2Norm_Sqr();
//                            if ( distan < THETA )
//                            {
//                                Duo duo(v0,p,Q);
//                                ss.insert(duo);
//                            }
//                        }
//                        if (rindex!=1)
//                        {
//                            p=m_pTriangleList[i][1];
//                            float distan=(m_pVertexList[v0]-m_pVertexList[p]).L2Norm_Sqr();
//                            if ( distan < THETA )
//                            {
//                                Duo duo(v0,p,Q);
//                                ss.insert(duo);
//                            }
//                        }
//                        if (rindex!=2)
//                        {
//                            p=m_pTriangleList[i][2];
//                            float distan=(m_pVertexList[v0]-m_pVertexList[p]).L2Norm_Sqr();
//                            if ( distan < THETA )
//                            {
//                                Duo duo(v0,p,Q);
//                                ss.insert(duo);
//                            }
//                        }
//                        m_pTriangleList[i][rindex]=v0;
//                    }
//                    
//                }
//            }
//    }
//    
//}