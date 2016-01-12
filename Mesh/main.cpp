/*
 * Main.cpp
 *
 *  Created on: 2016年1月8日
 *      Author: Gary
 */

#include<iostream>

#include "TrivialObject.h"
//#include "Duo.cpp"

using namespace std;

int main()
{
    
    SimpleOBJ::TrivialObject tmp;
    char path[100]="/Users/mac/Downloads/Tsinghua/高等计算机图形学/Mesh_helper/test_data/";
    //    char myfile[100]="fixed.perfect.dragon.100K.0.07";
    char myfile[100]="bunny.fine";
    char fileend[20]=".obj";
    char str[220],str2[220],str3[220];
    strcpy (str,path);
    strcat(str, myfile);
    strcpy(str2, str);
    strcat(str, fileend);
    strcat(str2, "_Reduce0.5");
    strcat(str2, fileend);
    strcat(str3, "_Reduce0.1");
    strcat(str3, fileend);
    
    tmp.LoadFromObj(str);
    tmp.initHE();
    //	tmp.showallHE();
    cout<<"HE done!\n";
    //	tmp.initQ();
    //	cout<<"Q done!\n";
    tmp.initPair();
    cout<<"Pair done!\n";
    cout<<"OK!\n";
    int half=tmp.getNumVertices()/2;
    int bili=tmp.getNumVertices()*8/10;
    for (int i=0;i<25614;i++)
    {
//        if (i%100==0)
//        cout<<i<<'\n';
        //		tmp.showallHE();
        tmp.MergeOnePair();
        if (i==half) tmp.SaveRealToObj(str2);
    }
    
    tmp.MergeOnePair();
    tmp.SaveRealToObj(str3);
    //	tmp.SaveToObj("/Users/mac/Downloads/Tsinghua/高等计算机图形学/Mesh_helper/test_data/Nima.obj");
    //Note: after save to, we must re-init...
    
    
    //	SimpleOBJ::Vec3f a(.1,.1,.1),b(.8,.8,.8),c;
    //	c=(a+b)/2;
    //	cout<<c.x<<c.y<<c.z<<endl;
    return 0;
}
