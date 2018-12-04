#pragma once

#include "Vec3.h"

class Matrix3
{
public:
	Matrix3();
	~Matrix3();

	static Matrix3 Translation(const Vec3& t);
	static Matrix3 Rotation(const float& ang);
	static Matrix3 Scale(const Vec3& s);
	static Matrix3 Identity();

	float m[3][3];
	Vec3 operator* (const Vec3& RH) const;
	Matrix3 operator* (const Matrix3& RH) const;
	//bool operator== (const Matrix3& RH) const;

};

