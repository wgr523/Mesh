#pragma once
#include "Vec3f.h"
#include <vector>
#include <cassert>
#include <cstring>

namespace SimpleOBJ
{
    template <typename T, int N> class Array 
    {
    public:
        enum {_len = N};
        typedef T t_Val; 
    public:
        T& operator[] (int i)
        {
            assert(i>=0&&i<N);
            return _p[i];
        }
        const T& operator[] (int i) const 
        {
            assert(i>=0&&i<N);
            return _p[i];
        }
        bool find (T x)
        {
        	for (int i=0;i<N;i++)
        	{
        		if (_p[i]==x) {
        			return true;
        		}
        	}
        	return false;
        }
        int findindex (T x)
        {
        	for (int i=0;i<N;i++)
        	{
        		if (_p[i]==x) {
        			return i;
        		}
        	}
        	return -1;
        }

    protected:
        T _p[N];
    };

    class CSimpleObject
    {
    public:
        CSimpleObject(void);
        ~CSimpleObject(void);
        
    public:
        bool IsLoaded() { return m_pVertexList!=NULL;}

        void Destroy();
        bool LoadFromObj(const char* fn);
        bool SaveToObj(const char* fn);
        void calcRealVertex();
        
    protected:
        bool Parse(FILE* fp);
        bool CheckParse(int nVertices,std::vector<Array<int,3> > & vecTriangles);
        void DelVertex(int n, int replace);
        void DelTriangle(int n);


    protected:

        int             m_nVertices;
        int             m_nTriangles;
        Vec3f*          m_pVertexList;
        Array<int,3>*   m_pTriangleList;
        bool*			m_bVertexDel;
        bool*			m_bTriangleDel;
    };

}
