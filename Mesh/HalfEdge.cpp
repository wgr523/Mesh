/*
 * HalfEdge.cpp
 *
 *  Created on: 2016年1月10日
 *      Author: Gary
 */
struct HE_edge
{
	int origin;   // vertex at the end of the half-edge
	int incface;   // face the half-edge borders
	HE_edge* next;   // next half-edge around the face
	HE_edge* opposite;   // oppositely oriented adjacent half-edge
};



