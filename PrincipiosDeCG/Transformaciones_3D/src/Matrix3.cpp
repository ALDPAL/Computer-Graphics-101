#include "Matrix3.h"
#include <math.h>

#define PI 3.14159265


Matrix3::Matrix3()
{
}


Matrix3::~Matrix3()
{
}

Vec3 Matrix3::operator* (const Vec3& RH) const
{
	Vec3 result;

	result.x = m[0][0] * RH.x + m[0][1] * RH.y + m[0][2] * RH.w;

	result.y = m[1][0] * RH.x + m[1][1] * RH.y + m[1][2] * RH.w;

	result.w = m[2][0] * RH.x + m[2][1] * RH.y + m[2][2] * RH.w;

	return result;
}

Matrix3 Matrix3::operator* (const Matrix3& RH) const
{
	Matrix3 result;

	for (int row = 0; row < 3 ; ++row)
		for (int col = 0; col < 3; ++col)
		{
			result.m[row][col] = 0;
		}

	for (int row = 0; row < 3; ++row)
	{
		for (int col = 0; col < 3; ++col)
		{
			for (int i = 0; i < 3; ++i)
			{
				result.m[row][col] += m[row][i] * RH.m[i][col];
			}
		}
	}
	return result;

}

//bool Matrix3::operator== (const Matrix3& RH) const
//{
//	if (this == &RH)
//		return true;
//}

Matrix3 Matrix3::Identity()
{
	Matrix3 r;
	r.m[0][0] = r.m[1][1] = r.m[2][2] = 1;
	r.m[0][1] = r.m[0][2] = r.m[1][0] = r.m[1][2] = r.m[2][0] = r.m[2][1] = 0;
	return r;
}



Matrix3 Matrix3::Translation(const Vec3& t)
{
	Matrix3 r = Matrix3::Identity();

	r.m[0][2] = t.x;
	r.m[1][2] = t.y;

	return r;
}

Matrix3 Matrix3::Scale(const Vec3& s)
{
	Matrix3 r = Matrix3::Identity();

	r.m[0][0] = s.x;
	r.m[1][1] = s.y;

	return r;
}

Matrix3 Matrix3::Rotation(const float& ang)
{
	float angel = ang * PI / 180.0;
	Matrix3 r = Matrix3::Identity();

	r.m[0][0] = r.m[1][1] = cos(angel);
	r.m[0][1] = -(sin(angel));
	r.m[1][0] = sin(angel);

	return r;
}
