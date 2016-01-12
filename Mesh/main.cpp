/*
 * Main.cpp
 *
 *  Created on: 2016年1月8日
 *      Author: Gary
 */

#include<iostream>

//#include "TrivialObject.h"
#include "HEObject.h"

//#include "Duo.cpp"

using namespace std;

int main()
{
    
    SimpleOBJ::HEObject tmp;
    char path[100]="/Users/mac/Downloads/Tsinghua/高等计算机图形学/Mesh_helper/test_data/";
    //    char myfile[100]="fixed.perfect.dragon.100K.0.07";
    char myfile[100]="bunny.fine";
    char fileend[20]=".obj";
    char str[220],str2[220],str3[220];
    strcpy (str,path);
    strcat(str, myfile);
    strcpy(str2, str);
    strcpy(str3, str);
    strcat(str, fileend);
    strcat(str3, "_Reduce0.1");
    strcat(str3, fileend);
    
    tmp.LoadFromObj(str);
    
    tmp.initHE();
//	  tmp.showallHE();
    cout<<"HE done!\n";
    tmp.initPair();
    cout<<"Pair done!\n";
    cout<<"OK!\n";
//    int half=tmp.getNumVertices()/2;
    int bili=tmp.getNumVertices()*9/10;
    for (int i=1;i<bili;i++)
    {
        cout<<i<<'\n';
//        if (i==1609 ) tmp.showallHE();
        //		tmp.showallHE();
        if (i%10000==0)
        {
            char tmpchar[220];
            sprintf(tmpchar,"%s^%d.obj",str2,(bili-i)/10000);
            tmp.SaveRealToObj(tmpchar);
//            tmp.initHE();
//            tmp.initPair();
        }
        if (!tmp.MergeOnePair()) {cout<<"Premature.\n";break;}
//        if (i==half) tmp.SaveRealToObj(str2);
    }
    
//    tmp.MergeOnePair();
    tmp.SaveRealToObj(str3);
    //	tmp.SaveToObj("/Users/mac/Downloads/Tsinghua/高等计算机图形学/Mesh_helper/test_data/Nima.obj");
    return 0;
}
