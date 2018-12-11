#include "Vec4.h"



Vec4::Vec4()
{
}

Vec4::Vec4(const float& x, const float& y, const float& z, const float& w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}


Vec4::~Vec4()
{
}

void Vec4::normalize() 
{
	float length = sqrt(x * x + y * y + z * z);

	if (length != 0) {
		x = x / length;
		y = y / length;
		z = z / length;
		w = 1.0f;
	}
}

void Vec4::homogenize()
{	
	x = x / w;
	y = y / w;
	z = z / w;
	w = w / w;
}

float Vec4::dot(const Vec4& rh) {
	float pP(x * rh.x + y * rh.y + z * rh.z);
	return pP;
}

Vec4 Vec4::cross(const Vec4& lh, const Vec4& rh)
{
	Vec4 pC(lh.y*rh.z - lh.z * rh.y, lh.z*rh.x - lh.x * rh.z, lh.x*rh.y - rh.x*lh.y, 1);
	return pC;
}

Vec4 Vec4::operator- (const Vec4& RH) const
{
	Vec4 result;
	result.x = x - RH.x;
	result.y = y - RH.y;
	result.z = z - RH.z;
	result.w = 1;

	return result;
}