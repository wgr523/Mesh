/*
 * Main.cpp
 *
 *  Created on: 2016年1月8日
 *      Author: Gary
 */

#include<iostream>

#include "TrivialObject.h"
//#include "Duo.cpp"
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{

	SimpleOBJ::TrivialObject tmp;
	tmp.LoadFromObj("/Users/mac/Documents/Java/workspace/Mesh/sphere.obj");
	tmp.initHE();
//	tmp.showallHE();
	cout<<"HE done!\n";
	tmp.initQ();
	cout<<"Q done!\n";
	tmp.initPair();
	cout<<"Pair done!\n";
	cout<<"OK!\n";
	for (int i=0;i<5000;i++)
	{
		cout<<i<<'\n';
//		tmp.showallHE();
		tmp.MergeOnePair();
	}

	tmp.SaveToObj("/Users/mac/Documents/Java/workspace/Mesh/Nima.obj");//Note: after save to, we must re-init...


//	SimpleOBJ::Vec3f a(.1,.1,.1),b(.8,.8,.8),c;
//	c=(a+b)/2;
//	cout<<c.x<<c.y<<c.z<<endl;
	return 0;
}
