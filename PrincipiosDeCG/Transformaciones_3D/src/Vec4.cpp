#include "Vec4.h"



Vec4::Vec4()
{
}

Vec4::Vec4(const float& x, const float& y, const float& z)
{
	this->x = x;
	this->y = y;
	this->z = z;
	w = 1.0f;
}


Vec4::~Vec4()
{
}

Vec4 Vec4::normalize() {
	Vec4 vector;

	float length = sqrt(x * x + y * y + z * z);

	if (length != 0) {
		vector.x = x / length;
		vector.y = y / length;
		vector.z = z / length;
		w = 1.0f;
	}

	return vector;
}

Vec4 Vec4::homogenize()
{
	Vec4 vector;
	vector.x = x / w;
	vector.y = y / w;
	vector.z = z / w;
	vector.w = w / w;

	return vector;
}

float Vec4::dot(const Vec4& rh) {
	float pP(x * rh.x + y * rh.y + z * rh.z);
	return pP;
}

Vec4 Vec4::cross(const Vec4& lh, const Vec4& rh)
{
	Vec4 pC(lh.y*rh.z - lh.z * rh.y, lh.z*rh.x - lh.x * rh.z, lh.x*rh.y - rh.x*lh.y);
	return pC;
}

Vec4 Vec4::operator- (const Vec4& RH) const
{
	Vec4 result;
	result.x = x - RH.x;
	result.y = y - RH.y;
	result.z = z - RH.z;

	return result;
}