#pragma once

#include "BaseApplication.h"
#include "Vec2D.h"
#include "Vec3.h"
#include "Matrix3.h"
#include "Vec4.h"
#include "Matrix4.h"
#include "time.h"
#include <vector>

class EjemploApp : public BaseApplication
{
private:
	int centerX, centerY;
	int currentPositionX, currentPositionY;
	float angle, angle1;
	std::vector<Vec4> vertices, verticesTrans, cubo, cuboT;
	Color currentColor;

public:
	EjemploApp();
	~EjemploApp();
	virtual void setup();
	virtual void update();
	virtual void draw();
	void PutPixel(const int& x, const int& y);
	void PutPixel(const float& x, const float& y);
	void setColor(const char& R, const char& G, const char& B, const char& A);
	void clearScreen();
	void moveTo(const int& x, const int& y);
	void lineTo(const int& x, const int& y);
	void midPointLine(int X1, int Y1, int X2, int Y2);
	void figures(const int& s, const int &r);
	void genTri();
	void triangle(const Vec4& v0, const Vec4& v1, const Vec4& v2);
	void sierpinskyGasket(Vec4 a, Vec4 b, Vec4 c, int subdiv);

	enum TYPE
	{
		POINTS,
		LINES,
		LINE_STRIP,
		LINE_LOOP,
		TRIANGLES,
		TRIANGLE_FAN,
		TRIANGLE_STRIP
	};

	void drawArray(const std::vector<Vec4>& v, TYPE type);
	void drawPoints(const std::vector<Vec4>& v);
	void drawLines(const std::vector<Vec4>& v);
	void lineStrip(const std::vector<Vec4>& v);
	void lineLoop(const std::vector<Vec4>& v);
	void drawTriangles(const std::vector<Vec4>& v);
	void triangleFan(const std::vector<Vec4>& v);
	void triangleStrip(const std::vector<Vec4>& v);
};

