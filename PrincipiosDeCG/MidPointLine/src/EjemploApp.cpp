#include "EjemploApp.h"

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
	//moveTo(20, 100);
}

void EjemploApp::update()
{

}

void EjemploApp::draw()
{
	Color azul(0, 0, 255, 255);
	Color rojo(255, 0, 0, 255);
	Color verde(0, 255, 0, 255);

	setColor(azul);


	float pi = 3.14159265;
	int r = 300;

	for (int deg = 0; deg < 360; ++deg)
	{
		int x = r * cos(deg * pi / 180);
		int y = r * sin(deg * pi / 180);

		if(deg < 45 || deg < 360 || deg < 180)
			midPointLine(currentPositionX, currentPositionY, x, y, deg);
		if((deg < 90 || deg < 135 || deg < 270 || deg < 315) && deg > 45)
			midPointLine(currentPositionY, currentPositionX, y, x, deg);
		if (deg < 225 && deg > 180)
			midPointLine(x, y, currentPositionX, currentPositionY, deg);
	}


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

void EjemploApp::PutPixel(const int&x, const int &y)
{
	putPixel(centerX + x, centerY - y, currentColor);
}

void EjemploApp::setColor(Color c)
{
	currentColor = c;
}

void EjemploApp::moveTo(int x, int y)
{
	centerX += x;
	centerY -= y;
}

void EjemploApp::lineTo(int x, int y)
{
	int rx = centerX + x;
	int ry = centerY + y;

	int rh = sqrt(pow(rx,2) + pow(ry,2));
}

void EjemploApp::midPointLine(int X1, int Y1, int X2, int Y2, int deg)
{	
	int a = Y2 - Y1; //DY
	int b = X2 - X1; //DX
	int d = 2 * a - b;
	int E = 2 * a;
	int NE = 2 * (a - b);
	int x = X1;
	int y = Y1;
	
	if(deg <= 45 || deg <= 225)
		PutPixel(x, y);

	if(deg <= 90)
		PutPixel(y, x);

	if (deg <= 135)
		PutPixel(-y, x);

	if (deg <= 180)
		PutPixel(-x, y);

	if (deg <= 270)
		PutPixel(-y, -x);


	if (deg <= 270)
		PutPixel(y, -x);

	if (deg <= 360)
		PutPixel(x, -y);

	while (x <= X2)
	{
		if (d <= 0)
		{
			d += E;
			x++;
		}

		else
		{
			d += NE;
			x++;
			y++;
		}
		
		if (deg <= 45 || deg <= 225)
			PutPixel(x, y);

		if (deg <= 90)
			PutPixel(y, x);

		if (deg <= 135)
			PutPixel(-y, x);

		if (deg <= 180)
			PutPixel(-x, y);
		
		if (deg <= 270)
			PutPixel(-y, -x);

		if (deg <= 270)
			PutPixel(y, -x);

		if (deg <= 360)
			PutPixel(x, -y);
	}
}