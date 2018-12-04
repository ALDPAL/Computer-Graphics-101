#pragma once
#include "Vec4.h"

class Matrix4
{
public:
	Matrix4();
	~Matrix4();

	static Matrix4 Identity();
	static Matrix4 RotateX(const float& ang);
	static Matrix4 RotateY(const float& ang);
	static Matrix4 RotateZ(const float& ang);
	static Matrix4 Translate(const Vec4& t);
	static Matrix4 Scale(const Vec4& s);
	static Matrix4 LookAt(Vec4 eye, Vec4 target, Vec4 up);

	Matrix4 operator* (const Matrix4& RH) const;
	Vec4 operator* (const Vec4& RH) const;

	float m[4][4];
};

