#include<cstring>
#include<cmath>
#include"Vec3f.h"
#define EPS 1e-6
class Matr4
{
public:
    Matr4();
    Matr4(const Matr4 & m);
	Matr4(const SimpleOBJ::Vec3f & p, float d);	
    Matr4& operator=(const Matr4 & m);
    ~Matr4();
	void operator +=(const Matr4 & m);
	void operator -=(const Matr4 & m);
	Matr4 operator +(const Matr4 & m) const;
	Matr4 operator -(const Matr4 & m) const;
	Matr4 operator *(const Matr4 & m) const;
//	float det() const;
	Matr4 LU() const;
	void SolveSP(float res[4]) const;
	//solve Ux=b, b=[0 0 0 1];
	float diagProd() const;
	float inner(const SimpleOBJ::Vec3f & l,const SimpleOBJ::Vec3f & r) const;
	Matr4 inducePrime() const;
    void showall() const;
    static Matr4 calc(const SimpleOBJ::Vec3f & v0, const SimpleOBJ::Vec3f & v1, const SimpleOBJ::Vec3f & v2);
    //float getCell(int row, int col) const;
    //void setCell(int row, int col, float value);

    float m_values[4][4];
//protected:
	
};
