
#include       "C:\dllBridge\Lego\WinMain.h"  
using namespace Lego;

#define  body 1
#define apple 10

#define NA 2  

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

short int NApples = NA;
short int length  = 1;
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
	
	for(int i = 1; i < SizeArray - 1; i++)
	{	
		Square(Cells[0 ][i].x, Cells[0 ][i].y, Gray);
		Square(Cells[24][i].x, Cells[24][i].y, Gray);
		Square(Cells[i ][0].x, Cells[i ][0].y, Gray);
		Square(Cells[i][24].x, Cells[i][24].y, Gray);
	}
	
}


class Snake
{
public:
	
	int x;
	int y;
	
private:						
	
	bool stand;
	
	void Restart()
	{
		x = (SizeArray / 2) - 1;	
		y = (SizeArray / 2) - 1;	
		
		NApples = NA;
		
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
				
		CreateApple = true;
	}
	
	void GameOver(int Color)
	{
		for(int a = 1; a < SizeArray - 1; a++)
			for(int b = 1; b < SizeArray - 1; b++)	
			{	
				Field[a][b] = Color;
				Square(Cells[a][b].x, Cells[a][b].y, Field[a][b]);
				Sleep(1);
			}
			
		Sleep(1);
		Restart();
	}	
	
	void Collision()
	{
		for(int i = tail; i < head; i++)
			if(CSnake[i].x == CSnake[NfCV].x && CSnake[i].y == CSnake[NfCV].y)
			{	
				GameOver(Red);
				Restart();		
			}
	}
	
	void AteApple()
	{			
		if(x == CApple[NfC].x && y == CApple[NfC].y )
		{	
			Beep(500, 50);
			length++;
			score += 5;
			
			NApples--;
								
			Field[x][y] = 0;
			CreateApple = true;
		}
	}
	
	
	void Drwing(int x, int y)
	{
		Square(Cells[x][y].x, Cells[x][y].y, Green);	
		Field[x][y] = body;
	}
	
	void Boundaries()
	{
		if(x <= 0 || x >= 24)
		{	
			Restart();	
			GameOver(Red);
		}	
		if(y <= 0 || y >= 24)
		{
			Restart();	
			GameOver(Red);
		}
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
		if(NApples == 0)
			GameOver(Green);
		
		Collision();
		Control();
		Drwing(x, y);
		AteApple();
		Boundaries();
	}

};
Snake snake;

class Apple
{

private:
	
	int randX,
		randY;

public: 
	
	void Drawing()
	{
		Square(Cells[randX][randY].x, Cells[randX][randY].y, Red);
	}

private:
	
	void Coordinates()
	{	
		Repeat:
			
		srand(time(0));
		
		randX = rand()%SizeArray,
		randY = rand()%SizeArray;
		
		if(randX < 1 || randY < 1 || randX > 23 || randY > 23)
			goto Repeat;
				
		NfC++;
		Field[randX][randY] = apple; 
		CApple[NfC].x = randX;
		CApple[NfC].y = randY;
		
		Drawing();
	}

public:
	
	void main()
	{
		Coordinates();
	}
};

Apple apples;

class ControlBar
{
	
private:
	
	void CreateItems()
	{
		Button btn[10];	
		EditBox edt[10];
	}

public:
	
	void Drawing(int x, int y)
	{	
		pen = CreatePen(PS_SOLID, 1, Gray);	
		SelectObject (hdc, pen);
		
		for(int i = 0; i < 2; i++)
		{
			MoveToEx(hdc, x + (i * 150), y, NULL); 
			LineTo(hdc, x + (i * 150), y + 510);		
			
			MoveToEx(hdc, x, y + (i * 510), NULL); 
			LineTo(hdc, x + 150, y + (i * 510));		
			
		}			
	}
	
	void main()
	{
		if(Timer_CLK < 5)
		{			
			CreateItems();	
		}
	}
	
}Bar;

void INIT()
{	
}

void START()
{  		
	SetCoordinatesForCells(); // ??????????? // 
	
	Bar.main();
	
	snake.main();
	
	if(CreateApple == true)
	{	
		apples.main();
		CreateApple = false;
	}
	
	if(CreateApple)
		apples.main();
	
	apples.Drawing();
	
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
	Bar.Drawing(FieldX + 515, FieldY - 5);
	DrawingField(FieldX, FieldY, size);	
}








//     Эта функция вызывается из оконной процедуры WndProc(), если пользователь выбрал:
// 1)  Какой-либо пункт меню.
// 2)  Нажал кнопку.	

////////////////////////////////////////////////////            
void ScanButtonsAndMenuItems(int item)            //                  
{
	


 
}






