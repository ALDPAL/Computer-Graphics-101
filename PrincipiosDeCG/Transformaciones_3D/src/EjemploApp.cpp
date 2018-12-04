#include "EjemploApp.h"

#define PI 3.14159265

Vec3 v0, v1, v2;
float angle = 0;

EjemploApp::EjemploApp() :
	BaseApplication(),
centerX(WIDTH / 2),
centerY(HEIGHT / 2),
currentPositionX(0),
currentPositionY(0),
currentColor(0,0,0,0)
{

}

EjemploApp::~EjemploApp()
{

}

void EjemploApp::setup()
{
	//Genera vertices para Sierpinsky Gasket (valores iniciales del triangulo y divisiones)

	Vec3 a(0, 200, 1), b(-200, -200, 1), c(200, -200, 1);
	sierpinskyGasket(a, b, c, 5);
}

void EjemploApp::update()
{
	verticesTrans.clear();
	Matrix3 accum = Matrix3::Identity();

	Vec3 vector(50, 50, 1);
	Vec3 vector0(0.5, 0.5, 1);
	Matrix3 mRot = Matrix3::Rotation(angle);
	Matrix3 mScale = Matrix3::Scale(vector0);
	Matrix3 mTrans = Matrix3::Translation(vector);
	accum = mTrans * mScale * mRot;
	angle = angle - 2;

	for (Vec3 v : vertices)
	{
		verticesTrans.push_back(accum * v);
	}

}

void EjemploApp::draw()
{
	//Dibuja los triangulos de Sierpinsky Gasket:

	const Vec3 d(300, 300, 1);

	setColor(0,0,0,0);
	clearScreen();

	setColor(0, 0, 255, 255);

}

void EjemploApp::clearScreen()
{
	for (int i = 0; i < WIDTH; ++i)
	{
		for (int j = 0; j < HEIGHT; ++j)
		{
			putPixel(i, j, currentColor);
		}
	}
}

void EjemploApp::PutPixel(const int&x, const int &y)
{
	putPixel(centerX + x, centerY - y, currentColor);
}

void EjemploApp::setColor(const char& R, const char& G, const char& B, const char& A)
{
	currentColor = Color(R, G, B, A);
}

void EjemploApp::moveTo(const int& x,const int& y)
{
	currentPositionX = x;
	currentPositionY = y;
}

void EjemploApp::lineTo(const int& x,const int& y)
{
	midPointLine(currentPositionX, currentPositionY, x, y);
	moveTo(x, y);
}

void EjemploApp::midPointLine(int X1, int Y1, int X2, int Y2)
{	
	float ang = 0.0;
	int _x1 = 0;
	int _y1 = 0;
	int _x2 = 0;
	int _y2 = 0;

	ang = (atan2(Y2 - Y1, X2 - X1) * (180.0 / PI));

	if (ang < 0.0)
	{
		ang = 360.0 + ang;
	}

	if (ang >= 45 && ang < 90)
	{
		_x1 = Y1;
		_y1 = X1;
		_x2 = Y2;
		_y2 = X2;
	}

	else if (ang >= 90 && ang < 135)
	{
		_x1 = Y1;
		_y1 = -X1;
		_x2 = Y2;
		_y2 = -X2;
	}

	else if (ang >= 135 && ang < 180)
	{
		_x1 = -X1;
		_y1 = Y1;
		_x2 = -X2;
		_y2 = Y2;
	}

	else if (ang >= 180 && ang <= 225)
	{
		_x1 = -X1;
		_y1 = -Y1;
		_x2 = -X2;
		_y2 = -Y2;
	}

	else if (ang > 225 && ang <= 270)
	{
		_x1 = -Y1;
		_y1 = -X1;
		_x2 = -Y2;
		_y2 = -X2;
	}

	else if (ang > 270 && ang <= 315)
	{
		_x1 = -Y1;
		_y1 = X1;
		_x2 = -Y2;
		_y2 = X2;
	}

	else if (ang > 315 && ang <= 360.0)
	{
		_x1 = X1;
		_y1 = -Y1;
		_x2 = X2;
		_y2 = -Y2;
	}

	else
	{
		_x1 = X1;
		_y1 = Y1;
		_x2 = X2;
		_y2 = Y2;
	}

	int x = _x1;
	int y = _y1;
	int a = _y2 - _y1;
	int b = _x2 - _x1;
	int d = 2 * a - b;
	int E = 2 * a;
	int NE = 2 * (a - b);



	while (x < _x2)
	{
		if (ang >= 45 && ang < 90)
			PutPixel(y, x);

		else if (ang >= 90 && ang < 135)
			PutPixel(-y, x);

		else if (ang >= 135 && ang < 180)
			PutPixel(-x, y);

		else if (ang >= 180 && ang <= 225)
			PutPixel(-x, -y);

		else if (ang > 225 && ang <= 270)
			PutPixel(-y, -x);

		else if (ang > 270 && ang <= 315)
			PutPixel(y, -x);

		else if (ang > 315 && ang <= 360.0)
			PutPixel(x, -y);

		else
			PutPixel(x, y);

		if (d > 0)
		{
			++y;
			d += NE;
		}

		else
		{
			d += E;
		}

		++x;
	}


}

void EjemploApp::figures(const int &s, const int& r)
{
	// s = sides, r = radius
	int inc = 360 / s;
	moveTo(r, 0);
	for (int ang = inc; ang < 360; ang += inc)
	{
		int x = r * cos(ang * PI / 180);
		int y = r * sin(ang * PI / 180);
		lineTo(x, y);
	}
	lineTo(r, 0);
}

void EjemploApp::genTri()
{
	for(int numTri = 0;numTri < 3; ++numTri)
	{ 
		triangle(v0, v1, v2);
	}
}

void EjemploApp::triangle(const Vec3& v0, const Vec3& v1, const Vec3& v2)
{
	moveTo(v0.x, v0.y);
	lineTo(v1.x, v1.y);
	lineTo(v2.x, v2.y);
	lineTo(v0.x, v0.y);
}

void EjemploApp::sierpinskyGasket(Vec3 a, Vec3 b, Vec3 c, int subdiv)
{
	if (subdiv <= 0)
	{
		vertices.push_back(a);
		vertices.push_back(b);
		vertices.push_back(c);
	}

	else
	{
		Vec3 ab(((b.x + a.x) / 2), ((b.y + a.y) / 2), 1);
		Vec3 bc(((c.x + b.x) / 2), ((c.y + b.y) / 2), 1);
		Vec3 ca(((a.x + c.x) / 2), ((a.y + c.y) / 2), 1);

		sierpinskyGasket(a, ab, ca, subdiv - 1);
		sierpinskyGasket(ab, b, bc, subdiv - 1);
		sierpinskyGasket(ca, bc, c, subdiv - 1);
	}
}

void EjemploApp::drawArray(const std::vector<Vec3>& v, TYPE type)
{
	switch (type)
	{
	case EjemploApp::POINTS:
		drawPoints(v);
		break;
	case EjemploApp::LINES:
		drawLines(v);
		break;
	case EjemploApp::LINE_STRIP:
		lineStrip(v);
		break;
	case EjemploApp::LINE_LOOP:
		lineLoop(v);
		break;
	case EjemploApp::TRIANGLES:
		drawTriangles(v);
		break;
	case EjemploApp::TRIANGLE_FAN:
		triangleFan(v);
		break;
	case EjemploApp::TRIANGLE_STRIP:
		triangleStrip(v);
		break;
	default:
		break;
	}
}

void EjemploApp::drawPoints(const std::vector<Vec3>& v)
{
	for (int i = 0; i < v.size(); ++i)
	{
		PutPixel(v[i].x, v[i].y);
	}
}

void EjemploApp::drawLines(const std::vector<Vec3>& v)
{
	for (int i = 0; i < v.size(); i += 2)
	{
		moveTo(v[i].x, v[i].y);
		lineTo(v[i + 1].x, v[i + 1].y);
	}
}

void EjemploApp::lineStrip(const std::vector<Vec3>& v)
{
	for (int i = 0; i < v.size(); ++i)
	{
		moveTo(v[i].x, v[i].y);
		lineTo(v[i + 1].x, v[i + 1].y);
	}
}

void EjemploApp::lineLoop(const std::vector<Vec3>& v)
{
	for (int i = 0; i < v.size(); ++i)
	{
		moveTo(v[i].x, v[i].y);
		lineTo(v[i + 1].x, v[i + 1].y);
		lineTo(v[i].x, v[i].y);
	}
}

void EjemploApp::drawTriangles(const std::vector<Vec3>& v)
{

}

void EjemploApp::triangleFan(const std::vector<Vec3>& v)
{

}

void EjemploApp::triangleStrip(const std::vector<Vec3>& v)
{

}