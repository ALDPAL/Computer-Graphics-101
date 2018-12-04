#include "Matrix4.h"
#include <math.h>

#define PI 3.14159265


Matrix4::Matrix4()
{
}


Matrix4::~Matrix4()
{
}

Vec4 Matrix4::operator* (const Vec4& RH) const
{
	Vec4 result;

	result.x = m[0][0] * RH.x + m[0][1] * RH.y + m[0][2] * RH.z + m[0][3] * RH.w;

	result.y = m[1][0] * RH.x + m[1][1] * RH.y + m[1][2] * RH.z + m[1][3] * RH.w;

	result.z = m[2][0] * RH.z + m[2][1] * RH.z + m[2][2] * RH.z + m[2][3] * RH.w;

	result.w = m[3][0] * RH.x + m[3][1] * RH.y + m[3][2] * RH.z + m[3][3] * RH.w;

	return result;
}

Matrix4 Matrix4::operator* (const Matrix4& RH) const
{
	Matrix4 result;

	for (int row = 0; row < 4; ++row)
		for (int col = 0; col < 4; ++col)
		{
			result.m[row][col] = 0;
		}

	for (int row = 0; row < 4; ++row)
	{
		for (int col = 0; col < 4; ++col)
		{
			for (int i = 0; i < 4; ++i)
			{
				result.m[row][col] += m[row][i] * RH.m[i][col];
			}
		}
	}
	return result;
}

Matrix4 Matrix4::Identity()
{
	Matrix4 r;
	r.m[0][0] = r.m[1][1] = r.m[2][2] = r.m[3][3] = 1;
	r.m[0][1] = r.m[0][2] = r.m[0][3] = r.m[1][0] = r.m[1][2] = r.m[1][3] = r.m[2][0] = r.m[2][1] = r.m[2][3] = r.m[3][0] = r.m[3][1] = r.m[3][2] = 0;
	return r;
}

Matrix4 Matrix4::Translate(const Vec4& t)
{
	Matrix4 r = Matrix4::Identity();

	r.m[0][3] = t.x;
	r.m[1][3] = t.y;
	r.m[2][3] = t.z;

	return r;
}

Matrix4 Matrix4::Scale(const Vec4& s)
{
	Matrix4 r = Matrix4::Identity();

	r.m[0][0] = s.x;
	r.m[1][1] = s.y;
	r.m[2][2] = s.z;

	return r;
}

Matrix4 Matrix4::RotateX(const float& ang)
{
	float angel = ang * PI / 180.0;
	Matrix4 r = Matrix4::Identity();

	r.m[1][1] = r.m[2][2] = cos(angel);
	r.m[1][2] = -(sin(angel));
	r.m[2][1] = sin(angel);

	return r;
}

Matrix4 Matrix4::RotateY(const float& ang)
{
	float angel = ang * PI / 180.0;
	Matrix4 r = Matrix4::Identity();

	r.m[0][0] = r.m[2][2] = cos(angel);
	r.m[2][0] = -(sin(angel));
	r.m[0][2] = sin(angel);

	return r;
}

Matrix4 Matrix4::RotateZ(const float& ang) {
	float angel = ang * PI / 180.0;
	Matrix4 r = Matrix4::Identity();

	r.m[0][0] = r.m[1][1] = cos(angel);
	r.m[0][1] = -(sin(angel));
	r.m[1][0] = sin(angel);

	return r;
}

Matrix4 Matrix4::LookAt(Vec4 eye, Vec4 target, Vec4 up)
{
	Vec4 x, y, z;

	z = target - eye;
	z.normalize();

	x = Vec4::cross(z, up);
	x.normalize();
	
	y = Vec4::cross(x, z);
	y.normalize();

	Matrix4 r;

	r.m[0][0] = x.x; r.m[0][1] = x.y; r.m[0][2] = x.z; r.m[0][3] = 0;
	r.m[1][0] = y.x; r.m[1][1] = y.y; r.m[1][2] = y.z; r.m[1][3] = 0;
	r.m[2][0] = z.x; r.m[2][1] = z.y; r.m[2][2] = z.z; r.m[2][3] = 0;
	r.m[3][0] = r.m[3][1] = r.m[3][2] = 0; r.m[3][3] = 1;

	Matrix4 t = Matrix4::Identity();

	t.m[0][3] = -eye.x; t.m[1][3] = -eye.y; t.m[2][3] = -eye.z;

	Matrix4 resultado = r * t;
}