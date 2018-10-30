#include "EjemploApp.h"

#define PI 3.14159265

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
	//Mueve el origen de donde se comienza a dibujar:

	//moveTo(20, -100);
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

	double r = 300;


	for (int deg = 0; deg < 360; ++deg)
	{
		int x = r * cos(deg * PI / 180.0);
		int y = r * sin(deg * PI / 180.0);
		lineTo(x, y);		
	}

	//Draws every Pixel in Black.

		//clearScreen();


	//Dibuja una X, una linea horizontal y una vertical que se intersectan en el centro de la pantalla

	/*for (int i = 0; i < WIDTH; ++i)
	{
		putPixel(i, WIDTH / 2, azul);
	}

	for (int i = 0; i < HEIGHT; ++i)
	{
		putPixel(HEIGHT / 2, i, rojo);
	}

	for (int i = 0; i < WIDTH; ++i)
	{
		putPixel(i, i, verde);
	}

	for (int i = 0; i < WIDTH; ++i)
	{
		putPixel(i, i, verde);
	}

	for (int i = 0; i < WIDTH; ++i)
	{
		putPixel(WIDTH - i, i, verde);
	}*/
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
	centerX = centerX + x;
	centerY = centerY - y;
}

void EjemploApp::lineTo(const int& x,const int& y)
{
	midPointLine(currentPositionX, currentPositionY, x, y);
}

void EjemploApp::midPointLine(int X1, int Y1, int X2, int Y2)
{	
	int ang = 0.0;
	int _x1 = 0;
	int _y1 = 0;
	int _x2 = 0;
	int _y2 = 0;

	ang = (atan2(Y2, X2) * (180.0 / PI));

	if (ang >= 0.0)
	{
		if (Y2 < 0)
			ang = 359;
		else
		ang = ang;
	}

	else if (ang < 0.0)
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