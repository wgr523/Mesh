//
//  HEObject.cpp
//  Mesh
//
//  Created by Gary Wang on 16/1/13.
//  Copyright © 2016年 Gary Wang. All rights reserved.
//

#include "HEObject.h"
namespace SimpleOBJ
{
    void HEObject::Destroy()
    {
        if (m_pHalfEdgeList) delete [] m_pHalfEdgeList;
        if (m_pVertexToEdge) delete [] m_pVertexToEdge;
        if (m_bBoundary) delete [] m_bBoundary;
    }
//    void HEObject::checkSelfEdge()
//    {
//        for (int i=0;i<m_nVertices;i++)
//            if (!m_bVertexDel[i])
//            {
//                if (m_pVertexToEdge[i]==-1) {std::cout<<"This is NULL\n";break;}
//                HE_edge* p=m_pHalfEdgeList+m_pVertexToEdge[i];
//                int tobreak=p->next->origin;
//                //                std::cout<<"Node "<<i<<" neighbor are: ";
//                int cnt=0;
//                do
//                {
//                    cnt++;
//                    //                    std::cout<<p->next->origin<<' ';
//                    if (p->next->next->opposite==NULL) {break;}
//                    if (p->next->origin==i) {
//                        std::cout<<"Self-enjoy!\n";break;
//                    }
//                    p=p->next->next->opposite;
//                }while(p->next->origin!=tobreak);
//                if (m_bBoundary[i]) std::cout<<i<<"    And Is Boundary!\n";
//                //                std::cout<<"\n";
//                if (cnt<=2) std::cout<<i<<"    And Is Single!\n";
//            }
//
//    }
    void HEObject::initHE()
    {
        if (m_pHalfEdgeList) delete [] m_pHalfEdgeList;
        if (m_pVertexToEdge) delete [] m_pVertexToEdge;
        if (m_bBoundary) delete [] m_bBoundary;
        m_pHalfEdgeList = new HE_edge [m_nTriangles*3];
        memset(m_pHalfEdgeList,0,m_nTriangles*3*sizeof(HE_edge));
        HE_edge* lis=m_pHalfEdgeList;
        m_pVertexToEdge = new int[m_nVertices];
        memset(m_pVertexToEdge,0xff,m_nVertices*sizeof(int));
        m_bBoundary = new bool [m_nVertices];
        memset(m_bBoundary,0,m_nVertices*sizeof(bool));
        std::map<std::pair<int,int>, int> Edges;
        for (int i=0;i<m_nTriangles;i++)
            if (!m_bTriangleDel[i]){
                int v[3];
                v[0]=m_pTriangleList[i][0]; v[1]=m_pTriangleList[i][1]; v[2]=m_pTriangleList[i][2];
                for (int c=0;c<3;c++)
                {
                    lis->incface=i;
                    lis->origin=v[c];
                    if (m_pVertexToEdge[v[c]]==-1)
                        m_pVertexToEdge[v[c]]=3*i+c;
                    Edges[std::make_pair(v[c],v[(c+1)%3])]=3*i+c;
                    if (Edges.find(std::make_pair(v[(c+1)%3],v[c]) )!=Edges.end() )
                    {
                        HE_edge* tmp=m_pHalfEdgeList+Edges[std::make_pair(v[(c+1)%3],v[c])];
                        lis->opposite=tmp;
                        tmp->opposite=lis;
                    }
                    if (c==2) lis->next=lis-2;
                    else lis->next=lis+1;
                    lis++;
                }
            }
        HE_edge* tmpp=m_pHalfEdgeList;
        for (int i=0;i<3*m_nTriangles;i++)
        {
            if (tmpp->opposite==NULL)
            {
                m_bBoundary[tmpp->origin]=true;
                HE_edge* p=m_pHalfEdgeList+m_pVertexToEdge[tmpp->origin];// get to the right starting HE
                while (p->opposite){
                    p=p->opposite->next;
                }
                m_pVertexToEdge[tmpp->origin]=p-m_pHalfEdgeList;
            }
            tmpp++;
        }
    }
    void HEObject::showallHE()
    {
        FILE *f=fopen("/Users/mac/Downloads/Tsinghua/高等计算机图形学/Mesh_helper/HE.txt", "w");
        fprintf(f, "----------------------------------------------------------\n");
        bool tf=false;int singleman=0;
        for (int i=0;i<m_nVertices;i++)//m_nVertices
            if (!m_bVertexDel[i])
            {
                if (m_bBoundary[i]) tf=true;
                if (m_pVertexToEdge[i]==-1) {fprintf(f, "Some is NULL\n");break;}
                HE_edge* p=m_pHalfEdgeList+m_pVertexToEdge[i];
                int tobreak=p->next->origin;
//                std::cout<<"Node "<<i<<" neighbor are: ";
                fprintf(f, "Node %d neighbor: ",i);
                int cnt=0;
                do
                {
                    cnt++;
                    fprintf(f, "%d ",p->next->origin);
                    if (m_bVertexDel[p->next->origin]) fprintf(f, "(DEL) ");
//                    std::cout<<p->next->origin<<' ';
                    if (p->next->next->opposite==NULL) {break;}
                    p=p->next->next->opposite;
                }while(p->next->origin!=tobreak);
                if (m_bBoundary[i]) fprintf(f, "is Boundary");
                fprintf(f, "\n");
//                std::cout<<"\n";
                if (cnt<2) singleman++;
            }
        fclose(f);
//        HE_edge* tmpp=m_pHalfEdgeList;
//        for (int i=0;i<3*m_nTriangles;i++)
//        {
//            std::cout<<tmpp->origin<<' '<<tmpp->next->origin<<" OPPO "<<tmpp->opposite->origin<<' '<<tmpp->opposite->next->origin<<'\n';
//            tmpp++;
//        }
    }
    void HEObject::initPair()
    {
        bool* recordo = new bool [3*m_nTriangles];
        memset(recordo,0,3*m_nTriangles*sizeof(bool));
        ss.clear();
        HE_edge* p=m_pHalfEdgeList;
        for (int i=0;i<3*m_nTriangles;i++)
        {
            if (!recordo[i])
            {
                int v0=p->origin,v1=p->next->origin;
                recordo[i]=true;
                if (p->opposite!=NULL) recordo[p->opposite - m_pHalfEdgeList]=true;
                else continue;// on boundary
                float distan=(m_pVertexList[v0]-m_pVertexList[v1]).L2Norm_Sqr();
                if ( distan < THETA )
                {
                    Duo duo(v0,v1,distan);
                    ss.insert(duo);
                }
            }
            p++;
        }
        delete [] recordo;
    }
    void HEObject::DelVertex(int v1, int v0) //v0:replace must be before n
    {
        //        if (v0==223) std::cout<<v1<<' '<<v0<<'\n';
        m_bVertexDel[v1]=true;
        HE_edge* p;
        int tobreak;
        p=m_pHalfEdgeList+m_pVertexToEdge[v1];
        tobreak=p->next->origin;
        do
        {
            
            int i=p->incface;
            if (m_bTriangleDel[i]) {p=p->next->next->opposite;continue;}
            //				if (m_pTriangleList[i].findindex(v0)!=-1) DelTriangle(i);
            if (p->next->origin==v0 || p->next->next->origin==v0) DelTriangle(i);
            else
            {
//                float distan=(m_pVertexList[v0]-m_pVertexList[p->next->origin]).L2Norm_Sqr();
//                if ( distan < THETA )
//                {
//                    Duo duo(v0,p->next->origin,distan);
//                    ss.insert(duo);
//                }
                int rindex = m_pTriangleList[i].findindex(v1);
                if (rindex!=-1)
                    m_pTriangleList[i][rindex]=v0;
            }
            if (p->next->next->opposite==NULL) break;
            p=p->next->next->opposite;
        }while(p->next->origin!=tobreak);
        
        p=m_pHalfEdgeList+m_pVertexToEdge[v1];//update HE origin
        tobreak=p->next->origin;
        do
        {
            p->origin=v0;
            if (p->next->next->opposite==NULL) break;
            p=p->next->next->opposite;
        }while(p->next->origin!=tobreak);
        p=m_pHalfEdgeList+m_pVertexToEdge[v1];//update HE opposite
        tobreak=p->next->origin;
        do
        {
            if (p->next->origin==v0) break;
            if (p->next->next->opposite==NULL) break;
            p=p->next->next->opposite;
        }while(p->next->origin!=tobreak);
        //update HE's opposite
        HE_edge* t1,* t2;
        t1=p->next->opposite;
        t2=p->next->next->opposite;
        t1->opposite=t2;
        t2->opposite=t1;
        t1=p->opposite->next->opposite;
        t2=p->opposite->next->next->opposite;
        t1->opposite=t2;
        t2->opposite=t1;
        //if other edge in p->incface is used, we must change it to...
        HE_edge* fu;int temp0,temp1;
        temp0=p->next->next->origin;
        fu=m_pHalfEdgeList+m_pVertexToEdge[temp0];
        if (fu->next->origin==v0) m_pVertexToEdge[temp0]=fu->next->next->opposite-m_pHalfEdgeList;//special case
        temp1=p->opposite->next->next->origin;
        fu=m_pHalfEdgeList+m_pVertexToEdge[temp1];
        if (fu->next->origin==v0) m_pVertexToEdge[temp1]=fu->next->next->opposite-m_pHalfEdgeList;//special case
        fu=m_pHalfEdgeList+m_pVertexToEdge[v0];
        while (fu->next->origin==v0 || fu->next->origin==temp0) fu=fu->next->next->opposite;
        m_pVertexToEdge[v0]=fu-m_pHalfEdgeList;//special case
    }
    bool HEObject::MergeOnePair()
    {
        std::set<Duo>::iterator it;
        while (!ss.empty())
        {
            it=ss.begin();
            int v0=it->v0,v1=it->v1;
            ss.erase(it);
            if (m_bVertexDel[v0] || m_bVertexDel[v1] || m_bBoundary[v0] || m_bBoundary[v1] ) {continue;}
            else //if only 3 neighbor vertices, should not merge it.
            {
                HE_edge* p0,* p1,* p2,* p3;
                int cnt=0;
                p0=m_pHalfEdgeList+m_pVertexToEdge[v0];
                p1=m_pHalfEdgeList+m_pVertexToEdge[v1];
                int tobreak0=p0->next->origin;
                int tobreak1=p1->next->origin;
                do
                {
                    if (p0->next->origin==v1) break;
                    p0=p0->next->next->opposite;
                }while(p0->next->origin!=tobreak0);
                if (p0->next->origin!=v1) {std::cout<<"BUG:disconnect"<<v0<<' '<<v1<<"\n";continue;}
                p2=p0->next->next;p3=p0->opposite->next->next;
//                if (p2==NULL || p3==NULL) {std::cout<<"BUG:no third node"<<v0<<' '<<v1<<"\n";break;}
                
                bool tmpf=false;
                p0=m_pHalfEdgeList+m_pVertexToEdge[v0];
                do
                {
                    if (p0->next->origin==v0) {
                        std::cout<<"Error of selfloop ";tmpf=true;break;
                    }
                    if (m_pTriangleList[p0->incface].findindex(v0)==-1)
                    {
                        std::cout<<"BUG:Triangle index err ";tmpf=true;break;
                    }
                    p0=p0->next->next->opposite;
                }while(p0->next->origin!=tobreak0 && p0->next->origin!=v0);
                do
                {
                    if (p1->next->origin==v1) {
                        std::cout<<"Error of selfloop ";tmpf=true;break;
                    }
                    if (m_pTriangleList[p1->incface].findindex(v1)==-1)
                    {
                        std::cout<<"BUG:Triangle index err ";tmpf=true;break;
                    }
                    p1=p1->next->next->opposite;
                }while(p1->next->origin!=tobreak1 && p1->next->origin!=v1);
                if (tmpf) {std::cout<<v0<<' '<<v1<<"\n";continue;}

                p0=m_pHalfEdgeList+m_pVertexToEdge[v0];
                p1=m_pHalfEdgeList+m_pVertexToEdge[v1];
                int tobreak2=p2->next->origin;
                int tobreak3=p3->next->origin;
//                p1=m_pHalfEdgeList+m_pVertexToEdge[v1];
                do
                {
                    
                    cnt++;
                    p0=p0->next->next->opposite;
                    p1=p1->next->next->opposite;
                    p2=p2->next->next->opposite;
                    p3=p3->next->next->opposite;
                    if (p0==NULL || p1==NULL || p2==NULL ||p3==NULL) break;
                }while(p0->next->origin!=tobreak0 && p1->next->origin!=tobreak1 && p2->next->origin!=tobreak2 && p3->next->origin!=tobreak3);
                if (cnt<4) continue;
            }

//            HE_edge* p;
//            int tobreak;
//            
//            p=m_pHalfEdgeList+m_pVertexToEdge[v0];
//            tobreak=p->next->origin;
//            
            m_pVertexList[v0]=(m_pVertexList[v0]+m_pVertexList[v1])/2;
            DelVertex(v1,v0);
            
//            p=m_pHalfEdgeList+m_pVertexToEdge[v0];
//            tobreak=p->next->origin;
            
            return true;
        }
        return false;
    }
    
}
