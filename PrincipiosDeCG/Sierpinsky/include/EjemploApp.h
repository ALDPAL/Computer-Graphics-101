#pragma once

#include "BaseApplication.h"
#include "Vec2D.h"
#include "time.h"
#include <vector>

class EjemploApp : public BaseApplication
{
private:
	int centerX, centerY;
	int currentPositionX, currentPositionY;
	std::vector<Vec2D> vertices;
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
	void triangle(const Vec2D& v0, const Vec2D& v1, const Vec2D& v2);
	void sierpinskyGasket(Vec2D a, Vec2D b, Vec2D c, int subdiv);
};

