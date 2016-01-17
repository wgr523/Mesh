/*
 * Main.cpp
 *
 *  Created on: 2016年1月8日
 *      Author: Gary
 */

#include<iostream>

#include "HEObject.h"
//#include "QObject.hpp"
//#include "Vec3f.h"
//#include "Duo.cpp"

using namespace std;

int main()
{
    SimpleOBJ::TrivialObject tmp;
    char path[100]="/Users/mac/Downloads/Tsinghua/高等计算机图形学/Mesh_helper/test_data/";
    char myfile[100]="fixed.perfect.dragon.100K.0.07";
//    char myfile[100]="bunny.fine";
//    char myfile[100]="dinosaur.2k";
//    char myfile[100]="horse.fine.90k";
//    char myfile[100]="kitten.50k";
////    char myfile[100]="fandisk.18k";
//        char myfile[100]="sphere";
//        char myfile[100]="block";
//        char myfile[100]="rocker-arm.18k";
//        char myfile[100]="Arma";

    char fileend[20]=".obj";
    char str[220],str2[220],str3[220];
    strcpy (str,path);
    strcat(str, myfile);
    strcpy(str2, str);
    strcpy(str3, str);
    strcat(str, fileend);
    strcat(str3, "^Reduce_HE_End");
    strcat(str3, fileend);
//
    tmp.LoadFromObj(str);
//    tmp.initHE();
    cout<<"HE done!\n";
    tmp.initPair();

//    tmp.initQ();

//    tmp.showallHE();
//    tmp.initPair();
//    cout<<"Pair done!\n";
//    cout<<"OK!\n";
//
    set<int> Show;
    int onum = tmp.getNumVertices()/2;
    while (onum>100)
    {
        Show.insert(onum);
        onum/=2;
    }
    
    float bili=0.05;
    int num=tmp.getNumVertices();
    int loop=(int)((1-bili)*num);
    for (int i=1;i<loop;i++)
    {
        cout<<i<<'\n';
//        if (Show.find(num-i)!=Show.end())
//        {
//            char tmpchar[220];
//            sprintf(tmpchar,"%s^2_%d.obj",str2,(num-i));
//            tmp.SaveRealToObj(tmpchar);
//        }
        if (!tmp.MergeOnePair()) {cout<<"Premature.\n";break;}
    }
//
    tmp.SaveRealToObj(str3);
    return 0;
}
