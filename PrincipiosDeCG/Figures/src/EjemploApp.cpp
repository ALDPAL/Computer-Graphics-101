#include "EjemploApp.h"

#define PI 3.14159265

Vec2D v0, v1, v2;

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
	//Genera valores aleatorios en (x, y) para cada vertice de un triangulo
	/*
	srand(time(NULL));
	v0.x = rand() % (WIDTH + 1) + (-(WIDTH / 2));
	v0.y = rand() % (HEIGHT + 1) + (-(HEIGHT / 2));

	v1.x = rand() % (WIDTH + 1) + (-(WIDTH / 2));
	v1.y = rand() % (HEIGHT + 1) + (-(HEIGHT / 2));

	v2.x = rand() % (WIDTH + 1) + (-(WIDTH / 2));
	v2.y = rand() % (HEIGHT + 1) + (-(HEIGHT / 2));*/

	//Genera vertices para Sierpinsky Gasket (valores iniciales del triangulo y divisiones)

	Vec2D a(0, 300), b(-300, -300), c(300, -300);
	sierpinskyGasket(a, b, c, 5);
}

void EjemploApp::update()
{

}

void EjemploApp::draw()
{
	//Color azul(0, 0, 255, 255);
	//Color rojo(255, 0, 0, 255);
	//Color verde(0, 255, 0, 255);

	setColor(0, 0, 255, 255);

	//Dibuja Figuras

	//figures(3, 100);
	//figures(4, 200);
	//figures(5, 300);

	//Dibuja Triangulos con diversos angulos:

	//genTri();

	//Dibuja los triangulos de Sierpinsky Gasket:

	for (int i = 0; i < vertices.size(); i += 3)
	{
		triangle(vertices[i], vertices[i + 1], vertices[i + 2]);
	}
}

void EjemploApp::clearScreen()
{
	setColor(0,0,0,0);
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

void EjemploApp::triangle(const Vec2D& v0, const Vec2D& v1, const Vec2D& v2)
{
	moveTo(v0.x, v0.y);
	lineTo(v1.x, v1.y);
	lineTo(v2.x, v2.y);
	lineTo(v0.x, v0.y);
}

void EjemploApp::sierpinskyGasket(Vec2D a, Vec2D b, Vec2D c, int subdiv)
{
	if (subdiv <= 0)
	{
		vertices.push_back(a);
		vertices.push_back(b);
		vertices.push_back(c);
		//triangle(a, b, c);
	}

	else
	{
		Vec2D ab(((b.x + a.x) / 2), ((b.y + a.y) / 2));
		Vec2D bc(((c.x + b.x) / 2), ((c.y + b.y) / 2));
		Vec2D ca(((a.x + c.x) / 2), ((a.y + c.y) / 2));

		sierpinskyGasket(a, ab, ca, subdiv - 1);
		sierpinskyGasket(ab, b, bc, subdiv - 1);
		sierpinskyGasket(ca, bc, c, subdiv - 1);
	}
}