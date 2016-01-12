//#pragma once

#include "TrivialObject.h"
//#include <set>
namespace SimpleOBJ
{
    TrivialObject::TrivialObject()
    {
        m_bBoundary = NULL;
    }
    void TrivialObject::initPair()
    {
        std::set<std::pair<int,int> > record;
//        record.clear();
        ss.clear();
        for (int i=0;i<m_nTriangles;i++)
        {
            {
                int v[3];
                v[0]=m_pTriangleList[i][0]; v[1]=m_pTriangleList[i][1]; v[2]=m_pTriangleList[i][2];
                for (int c=0;c<3;c++)
                {
                    if (record.find(std::make_pair(v[c],v[(c+1)%3]) )==record.end() )
                    {
                        record.insert(std::make_pair(v[c],v[(c+1)%3]));
                        record.insert(std::make_pair(v[(c+1)%3],v[c]));
                        float distan=(m_pVertexList[v[c]]-m_pVertexList[v[(c+1)%3]]).L2Norm_Sqr();
                        if ( distan < THETA )
                        {
                            Duo duo(v[c],v[(c+1)%3],distan);
                            ss.insert(duo);
                        }
                    }
                }
            }
        }
    }
    void TrivialObject::DelVertex(int v1, int v0) //v0:replace must be before n
    {
        m_bVertexDel[v1]=true;
        for (int i=0;i<m_nTriangles;i++)
        {
            int rindex = m_pTriangleList[i].findindex(v1);
            if ( rindex!=-1 )//|| m_pTriangleList[m].find(v2) )
            {
                int lindex = m_pTriangleList[i].findindex(v0);
                if (lindex!=-1) DelTriangle(i);
                else	m_pTriangleList[i][rindex]=v0;
            }
        }
    }
    bool TrivialObject::MergeOnePair()
    {
        std::set<Duo>::iterator it;
        while (!ss.empty())
        {
            it=ss.begin();
            int v0=it->v0,v1=it->v1;
            ss.erase(it);
            DelVertex(v1,v0);
            return true;
        }
        return false;
    }
    
}
