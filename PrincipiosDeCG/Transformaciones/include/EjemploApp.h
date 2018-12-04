#pragma once

#include "BaseApplication.h"
#include "Vec2D.h"
#include "Vec3.h"
#include "Matrix3.h"
#include "time.h"
#include <vector>

class EjemploApp : public BaseApplication
{
private:
	int centerX, centerY;
	int currentPositionX, currentPositionY;
	int angle;
	std::vector<Vec3> vertices, verticesTrans, vPuntos, vLines, vLineL, vLineS, vTriangles, vTriangleS, vTriangleF;
	Color currentColor;

public:
	EjemploApp();
	~EjemploApp();
	virtual void setup();
	virtual void update();
	virtual void draw();
	void PutPixel(const int& x, const int& y);
	void setColor(const char& R, const char& G, const char& B, const char& A);
	void clearScreen();
	void moveTo(const int& x, const int& y);
	void lineTo(const int& x, const int& y);
	void midPointLine(int X1, int Y1, int X2, int Y2);
	void figures(const int& s, const int &r);
	void genTri();
	void triangle(const Vec3& v0, const Vec3& v1, const Vec3& v2);
	void sierpinskyGasket(Vec3 a, Vec3 b, Vec3 c, int subdiv);

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

	void drawArray(const std::vector<Vec3>& v, TYPE type);
	void drawPoints(const std::vector<Vec3>& v);
	void drawLines(const std::vector<Vec3>& v);
	void lineStrip(const std::vector<Vec3>& v);
	void lineLoop(const std::vector<Vec3>& v);
	void drawTriangles(const std::vector<Vec3>& v);
	void triangleFan(const std::vector<Vec3>& v);
	void triangleStrip(const std::vector<Vec3>& v);
};

