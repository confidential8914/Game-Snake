
#include       "C:\dllBridge\Lego\WinMain.h"  
using namespace Lego;

#define  body 1
#define apple 10

#include <time.h>

const short int FieldX    = 24;
const short int FieldY    = 24;
const short int size     = 500;
const short int SizeCells = 20;

HPEN     pen;
HBRUSH brush;

const int Red   = RGB(255, 51, 51);
const int Green = RGB(  0, 204, 0);
const int Gray  = RGB( 96, 96, 96);
const int Black = RGB(  0,  0,  0);

const short int SizeArray = 25; 
int    Field[SizeArray][SizeArray];
int OldField[SizeArray][SizeArray];

short int tail;
short int head;

short int NApples = 50;
short int length  = 9;
short int score   = 0;

short int Press;

bool CreateApple = true;

void Square(int x, int y, int Color)
{
	hdc = GetDC(hWnd);

	brush = CreateSolidBrush(Color);	
	SelectObject(hdc, brush);	
	
	Rectangle(hdc, x, y, x + SizeCells, y + SizeCells);	
	
	ReleaseDC(hWnd,hdc);
}

struct Coordinates
{
	short int x;
	short int y;
		
};

int NfCV;
int NfC;

Coordinates Cells[SizeArray + 2][SizeArray + 2];
Coordinates CSnake[1000];
Coordinates CApple[1000];

void SetCoordinatesForCells()
{	
	int Fx = FieldX, 
		Fy = FieldY;
	
	for(int a = 0; a < SizeArray; a++)
	{	
		for(int b = 0; b < SizeArray; b++)
		{	
			for(int x = Fx; x < (Fx + SizeCells); x++)
				for(int y = Fy; y < (Fy + SizeCells); y++)
				{	
					Cells[a][b].x = Fx;
					Cells[a][b].y = Fy;	
				}
					
			Fx += SizeCells;
		}	
		Fy += SizeCells;
		Fx = FieldX;
	}	
}

void ChecksCells(int Color)
{
	for(int a = 0; a < SizeArray; a++)	
		for(int b = 0; b < SizeArray; b++)
			if(OldField[a][b] != Field[a][b])
			{
				Square(Cells[a][b].x, Cells[a][b].y, Color);
				OldField[a][b] = Field[a][b];	
			}
}

void DrawingField(int x, int y, int size)
{
	hdc = GetDC(hWnd);
			
	pen = CreatePen(PS_SOLID, 1, Gray);	
	SelectObject (hdc, pen);		
		
	x -= 5;
	y -= 5;
	size += 10;
	
	for(int i = 0; i < 2; i++)
	{
		MoveToEx(hdc, x, y + (i * size), NULL); 
		LineTo(hdc, x + size, y + (i * size));		
		
		MoveToEx(hdc, x + (i * size), y, NULL); 
		LineTo(hdc, x + (i * size), y + size);			
	}
	
	SetCoordinatesForCells();
	
	for(int i = 0; i < SizeArray; i++)
	{	
		Square(Cells[0 ][i].x, Cells[0 ][i].y, Gray);
		Square(Cells[24][i].x, Cells[24][i].y, Gray);
		Square(Cells[i ][0].x, Cells[i ][0].y, Gray);
		Square(Cells[i][24].x, Cells[i][24].y, Gray);
	}
	
	ReleaseDC(hWnd, hdc);
	
}

class Apple
{
private:
	
	void Drawing(int randX, int randY)
	{
		NfC++;
		
		Field[randX][randY] = apple; 	
		Square(Cells[randX][randY].x, Cells[randX][randY].y, Red);
		
		CApple[NfC].x = randX;
		CApple[NfC].y = randY;
	}
	
	void Coordinates()
	{	
		Repeat:
			
		srand(time(0));
		
		int randX = rand()%SizeArray,
			randY = rand()%SizeArray;
		
		if(randX < 1 || randY < 1 || randX > 23 || randY > 23)
			goto Repeat;
		
		Drawing(randX, randY);
	}

public:
	
	void main()
	{
		Coordinates();
	}
};

Apple apples;

class Snake
{
private:						
	
	int x;
	int y;
	
	bool stand;
	
	void AteApple()
	{			
		if(x == CApple[NfC].x && y == CApple[NfC].y )
		{	
			Beep(500, 50);
			length++;
					
			Field[x][y] = 0;
			CreateApple = true;
		}
	}
	
	
	void Drwing(int x, int y)
	{
		Square(Cells[x][y].x, Cells[x][y].y, Green);	
		Field[x][y] = body;
	}
	
	void Restart()
	{
		x = (SizeArray / 2) - 1;	
		y = (SizeArray / 2) - 1;	
		
		length = 1;
		score  = 0;
		tail   = 0;
		head   = 0;
		
		Key_Pressed = 0;
		
		NfC    = 0;
		NfCV   = 0;
	
		for(int i = 0; i < 1000; i++)
		{	
			CSnake[i].x = CApple[i].x = 0;
			CSnake[i].y = CApple[i].y = 0;
		}	
		
		for(int a = 0; a < SizeArray; a++)
			for(int b = 0; b < SizeArray; b++)
			{	
				Square(Cells[a][b].x, Cells[a][b].y, Black);	
			}
			
		DrawingField(FieldX, FieldY, size);
		apples.main();
	}
	
	void Boundaries()
	{
		if(x <= 0 || x >= 24)
			Restart();	
			
		if(y <= 0 || y >= 24)
			Restart();	
	}
	
	//?????????????????????????????????????????????????????????????//
	void Motion()
	{	
		NfCV++;
		Press++;
			
		CSnake[NfCV].x = x;
		CSnake[NfCV].y = y;	
		
		head++; 
		tail = (head - (length - 1)) - 1;
		
		for(int i = tail + 1; i <= head; i++)
			Square(Cells[CSnake[i].x][CSnake[i].y].x, Cells[CSnake[i].x][CSnake[i].y].y, Green);	
		
		Square(Cells[CSnake[tail].x][CSnake[tail].y].x, Cells[CSnake[tail].x][CSnake[tail].y].y, Black);
		
	}	
	//?????????????????????????????????????????????????????????????//
	
	
	void Control()
	{ 	
		for(int i = 37; i <= 40; i++)
			if(Key_Pressed == i)
				Motion();
		
		switch(Key_Pressed)
		{
			case 37: y--; break;	
			case 38: x--; break;
			case 39: y++; break;
			case 40: x++; break;
		}
	}
	
public:
	
	Snake()
	{
		x = (SizeArray / 2) - 1;	
		y = (SizeArray / 2) - 1;
	}
	
	void main()
	{
		Control();
		Drwing(x, y);
		AteApple();
		Boundaries();
	}

};

Snake snake;

void INIT()
{	
	
	
}

void START()
{  		
	SetCoordinatesForCells(); // ??????????? // 
	
	snake.main();
	
	if(CreateApple == true)
	{	
		apples.main();
		CreateApple = false;
	}
	
	if(CreateApple)
		apples.main();
}













































//			                                                                   (   )       
//													                          (    )
//													                           (    )
//													                          (    )
//													                            )  )
//													                           (  (                  /\
//													                            (_)                 /  \  /\
//													                    ________[_]________      /\/    \/  \
//													           /\      /\        ______    \    /   /\/\  /\/\
//													          /  \    //_\       \    /\    \  /\/\/    \/    \
//													   /\    / /\/\  //___\       \__/  \    \/
//													  /  \  /\/    \//_____\       \ |[]|     \
//													 /\/\/\/       //_______\       \|__|      \
//													/      \      /XXXXXXXXXX\                  \
//													        \    /_I_II  I__I_\__________________\
//													               I_I|  I__I_____[]_|_[]_____I
//													               I_II  I__I_____[]_|_[]_____I
//													               I II__I  I     XXXXXXX     I
//					                                             E-mail:    dllbridge@gmail.com







//     В этой функции Вы можете рисовать. Контекст уже захвачен функцией BeginPaint() и будет освобождён автоматически.
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////     void mainPAINT()    /////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void mainPAINT()
{
	DrawingField(FieldX, FieldY, size);
}








//     Эта функция вызывается из оконной процедуры WndProc(), если пользователь выбрал:
// 1)  Какой-либо пункт меню.
// 2)  Нажал кнопку.	

////////////////////////////////////////////////////            
void ScanButtonsAndMenuItems(int item)            //                  
{
	


 
}






