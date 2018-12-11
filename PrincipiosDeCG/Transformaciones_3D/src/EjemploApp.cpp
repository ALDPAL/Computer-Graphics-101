#include "EjemploApp.h"

#define PI 3.14159265

Vec4 v0, v1, v2;

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
	//Verices para triangulo:

	/*
	Vec4 a(0, 200, 0, 1), b(-200, -200, 0, 1), c(200, -200, 0, 1);
	vertices.push_back(a); vertices.push_back(b); vertices.push_back(c);
	*/
	
	//Vertices para cubo:

	Vec4 vC0(-100, 100, 100, 1), vC1(-100, -100, 100, 1), vC2(100, -100, 100, 1), vC3(100, 100, 100, 1), vC4(-100, 100, -100, 1), vC5(-100, -100, -100, 1), vC6(100, -100, -100, 1), vC7(100, 100, -100, 1);
	
	//Near:
	cubo.push_back(vC0); cubo.push_back(vC1); cubo.push_back(vC2); cubo.push_back(vC2); cubo.push_back(vC3); cubo.push_back(vC0);
	//Far:
	cubo.push_back(vC4); cubo.push_back(vC5); cubo.push_back(vC6); cubo.push_back(vC6); cubo.push_back(vC7); cubo.push_back(vC4);
	//Right:
	cubo.push_back(vC3); cubo.push_back(vC2); cubo.push_back(vC6); cubo.push_back(vC6); cubo.push_back(vC7); cubo.push_back(vC3);
	//Left:
	cubo.push_back(vC4); cubo.push_back(vC5); cubo.push_back(vC1); cubo.push_back(vC1); cubo.push_back(vC0); cubo.push_back(vC4);
	//Top:
	cubo.push_back(vC4); cubo.push_back(vC0); cubo.push_back(vC3); cubo.push_back(vC3); cubo.push_back(vC7); cubo.push_back(vC4);
	//Bottom:
	cubo.push_back(vC5); cubo.push_back(vC1); cubo.push_back(vC2); cubo.push_back(vC2); cubo.push_back(vC6); cubo.push_back(vC6);

	//Angulos para rotar

	angle = 0;
	angle1 = 0;
}

void EjemploApp::update()
{
	verticesTrans.clear();
	cuboT.clear();

	Matrix4 accum = Matrix4::Identity();
	Matrix4 accumO = Matrix4::Identity();
	Matrix4 accumP = Matrix4::Identity();

	//Transformaciones en 3D de triangulo:
	/*
	Vec4 vector(0, 0, 0, 1);
	Vec4 vector0(1, 1, 1, 1);
	Matrix4 mRot = Matrix4::RotateX(angle);
	Matrix4 mRot1 = Matrix4::RotateY(angle);
	Matrix4 mRot2 = Matrix4::RotateZ(angle);
	Matrix4 mScale = Matrix4::Scale(vector0);
	Matrix4 mTrans = Matrix4::Translate(vector);
	accum = mTrans * mScale * mRot * mRot1 * mRot2;
	angle = angle - 2;
	for (Vec4 v : vertices)
	{
		verticesTrans.push_back(accum * v);
	}
	*/

													//Transformaciones para cubo:

	//Ortogonal:

	Matrix4 Orto = Matrix4::Ortogonal(-200, 200, 200, -200, 200, -200);
	Matrix4 Camara = Matrix4::LookAt(Vec4(2, 2, 2, 1), Vec4(0, 0, 0, 1), Vec4(0, 1, 0, 1));
	Matrix4 mRot1 = Matrix4::RotateY(angle1);
	accumO = Camara * mRot1;
	angle1 -= 2;

	//Perspectiva:

	/*
	Vec4 vector(0, 0, 0, 1);
	Vec4 vector0(0.5, 0.5, 0.5, 0.5);
	Matrix4 mRot = Matrix4::RotateX(angle);
	Matrix4 mRot1 = Matrix4::RotateY(angle1);
	Matrix4 mScale = Matrix4::Scale(vector0);
	Matrix4 mTrans = Matrix4::Translate(vector);
	Matrix4 Pers = Matrix4::Perspective(0, WIDTH / HEIGHT, 100, -100);

	accumP = mTrans * mScale * mRot * mRot1;
	angle -= 2;
	--angle1;
	*/

	for (Vec4 v : cubo)
	{
		cuboT.push_back(accumO * v);
	}

}

void EjemploApp::draw()
{

	setColor(0,0,0,0);
	clearScreen();

	setColor(0, 0, 255, 255);

	//Dibuja triangulo:

	//drawArray(verticesTrans, TRIANGLES);

	//Dibuja cubo:

	drawArray(cuboT, TRIANGLES);
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

//Put Pixel Para Graficar en Universo de 3D:

void EjemploApp::PutPixel(const float& x, const float& y)
{
	int xP = ((float)WIDTH / 2.0) * x;
	int yP = ((float)HEIGHT / 2.0) * y;
	PutPixel(xP , yP);
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

void EjemploApp::triangle(const Vec4& v0, const Vec4& v1, const Vec4& v2)
{
	moveTo(v0.x, v0.y);
	lineTo(v1.x, v1.y);
	lineTo(v2.x, v2.y);
	lineTo(v0.x, v0.y);
}

void EjemploApp::sierpinskyGasket(Vec4 a, Vec4 b, Vec4 c, int subdiv)
{
	if (subdiv <= 0)
	{
		vertices.push_back(a);
		vertices.push_back(b);
		vertices.push_back(c);
	}

	else
	{
		Vec4 ab(((b.x + a.x) / 2), ((b.y + a.y) / 2), 0, 1);
		Vec4 bc(((c.x + b.x) / 2), ((c.y + b.y) / 2), 0, 1);
		Vec4 ca(((a.x + c.x) / 2), ((a.y + c.y) / 2), 0, 1);

		sierpinskyGasket(a, ab, ca, subdiv - 1);
		sierpinskyGasket(ab, b, bc, subdiv - 1);
		sierpinskyGasket(ca, bc, c, subdiv - 1);
	}
}

void EjemploApp::drawArray(const std::vector<Vec4>& v, TYPE type)
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

void EjemploApp::drawPoints(const std::vector<Vec4>& v)
{
	for (int i = 0; i < v.size(); ++i)
	{
		PutPixel(v[i].x, v[i].y);
	}
}

void EjemploApp::drawLines(const std::vector<Vec4>& v)
{
	for (int i = 0; i < v.size() - 1; i += 2)
	{
		moveTo(v[i].x, v[i].y);
		lineTo(v[i + 1].x, v[i + 1].y);
	}
}

void EjemploApp::lineStrip(const std::vector<Vec4>& v)
{
	for (int i = 0; i < v.size() - 1; ++i)
	{
		moveTo(v[i].x, v[i].y);
		lineTo(v[i + 1].x, v[i + 1].y);
	}
}

void EjemploApp::lineLoop(const std::vector<Vec4>& v)
{
	for (int i = 0; i < v.size() - 1; ++i)
	{
		moveTo(v[i].x, v[i].y);
		lineTo(v[i + 1].x, v[i + 1].y);
	}

	lineTo(v[0].x, v[0].y);
}

void EjemploApp::drawTriangles(const std::vector<Vec4>& v)
{
	for (int i = 0; i < v.size() - 1; i += 3)
	{
		triangle(v[i], v[i + 1], v[i + 2]);
	}
}

void EjemploApp::triangleFan(const std::vector<Vec4>& v)
{
	Vec4 vOld(v[0].x, v[0].y, 0, 1);

	for (int i = 0; i < v.size(); i < 3 ? i += 3 : ++i)
	{

		if (i < 3)
			triangle(v[i], v[i + 1], v[i + 2]);

		else
		{
			moveTo(v[i - 1].x, v[i - 1].y);
			lineTo(v[i].x, v[i].y);
			lineTo(vOld.x, vOld.y);
		}
	}
}

void EjemploApp::triangleStrip(const std::vector<Vec4>& v)
{
	Vec4 vOld;

	for (int i = 0; i < v.size(); i < 3 ? i += 3 : ++i)
	{

		if (i < 3)
			triangle(v[i], v[i + 1], v[i + 2]);

		else
		{
			if (i == 3)
				vOld = v[i - 3];

			else
				vOld = v[i - 2];

			moveTo(v[i - 1].x, v[i - 1].y);
			lineTo(v[i].x, v[i].y);
			lineTo(vOld.x, vOld.y);
		}
	}
}