#include"Matr4.h"

Matr4::Matr4()
{
	memset(m_values,0,sizeof(m_values));
}
Matr4::Matr4(const Matr4 & m)
{
	memcpy(m_values,m.m_values,sizeof(m_values));
}
Matr4::Matr4(const SimpleOBJ::Vec3f & p, float d)
{
	for (int i=0;i<3;i++)
		for (int j=0;j<3;j++)
			m_values[i][j]=p[i]*p[j];
	for (int i=0;i<3;i++)
	{
		m_values[i][3]=p[i]*d;
		m_values[3][i]=p[i]*d;
	}
	m_values[3][3]=d*d;
}
Matr4& Matr4::operator = (const Matr4 & m)
{
	memcpy(m_values,m.m_values,sizeof(m_values));
	return (*this);
}
Matr4::~Matr4(){}

void Matr4::operator += (const Matr4 & m)
{
	for (int i=0;i<4;i++)
		for (int j=0;j<4;j++)
			m_values[i][j]+=m.m_values[i][j];
}
void Matr4::operator -= (const Matr4 & m)
{
	for (int i=0;i<4;i++)
		for (int j=0;j<4;j++)
			m_values[i][j]-=m.m_values[i][j];
}
Matr4 Matr4::operator + (const Matr4 & m) const
{
	Matr4 res;
	for (int i=0;i<4;i++)
		for (int j=0;j<4;j++)
			res.m_values[i][j]=m_values[i][j]+m.m_values[i][j];
	return res;
}
Matr4 Matr4::operator - (const Matr4 & m) const
{
	Matr4 res;
	for (int i=0;i<4;i++)
		for (int j=0;j<4;j++)
			res.m_values[i][j]=m_values[i][j]-m.m_values[i][j];
	return res;
}
Matr4 Matr4::operator * (const Matr4 & m) const
{
	Matr4 res;
	for (int i=0;i<4;i++)
		for (int j=0;j<4;j++)
			for (int k=0;k<4;k++)
				res.m_values[i][j]+=m_values[i][k]*m.m_values[k][j];
	return res;
}
Matr4 Matr4::LU() const
{
	Matr4 res((*this));
	for (int k=0;k<4-1;k++)
	{
		if (std::abs(res.m_values[k][k])<EPS) break;
		for (int i=k+1;i<4;i++)
		{
			res.m_values[i][k]/=res.m_values[k][k];
			for (int j=k+1;j<4;j++)
				res.m_values[i][j]-=res.m_values[i][k]*res.m_values[k][j];
		}
	}
	return res;
}
void Matr4::SolveSP(float res[4]) const
{
	float b[4]={0,0,0,1};
	for (int i=3;i>=0;i--)
	{
		res[i]=b[i];
		for (int j=i+1;j<4;j++)
			res[i]-=res[j]*m_values[i][j];
		res[i]/=m_values[i][i];
	}
}

float Matr4::det() const
{
	int com[24][4]={{1,2,3,4}, {1,2,4,3}, {1,3,2,4}, {1,3,4,2}, {1,4,2,3}, {1,4,3,2}, {2,1,3,4}, {2,1,4,3}, {2,3,1,4}, {2,3,4,1}, {2,4,1,3}, {2,4,3,1}, {3,1,2,4}, {3,1,4,2}, {3,2,1,4}, {3,2,4,1}, {3,4,1,2}, {3,4,2,1}, {4,1,2,3}, {4,1,3,2}, {4,2,1,3}, {4,2,3,1}, {4,3,1,2}, {4,3,2,1}};
	float pm[4]={1,-1,-1,1};
	float res=0,ret;
	for (int c=0;c<24;c++)
	{
		ret=1;
		for (int i=0;i<4;i++)
			ret*=m_values[i][com[c][i]-1];
		res+=ret*pm[c%4];
	}
	return res;
}
float Matr4::diagProd() const
{
	return m_values[0][0]*m_values[1][1]*m_values[2][2]*m_values[3][3];
}
float Matr4::inner(const SimpleOBJ::Vec3f & l,const SimpleOBJ::Vec3f & r) const
{
	float vl[4]={l._p[0],l._p[1],l._p[2],1};
	float vr[4]={r._p[0],r._p[1],r._p[2],1};
	float res=0;
	for (int i=0;i<4;i++)
	{
		float t=0;
		for (int j=0;j<4;j++)
		{
			t+=m_values[i][j]*vr[j];
		}
		res+=vl[i]*t;
	}
	return res;
}
Matr4 Matr4::inducePrime() const
{
	Matr4 res;
	res.m_values[3][3]=1;
	for (int j=0;j<4;j++)
	{
		res.m_values[0][j]=m_values[0][j];
		res.m_values[1][j]=m_values[1][j];
		res.m_values[2][j]=m_values[2][j];
	}
	for (int i=0;i<3;i++)
		for (int j=0;j<=i;j++)
		{
			res.m_values[i][j]=m_values[i][j];
		}
	return res;
}

