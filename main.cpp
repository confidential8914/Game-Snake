
#include       "C:\dllBridge\Lego\WinMain.h"  
using namespace Lego;

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

short int length = 1;
short int score  = 0;

short int Press;

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
		
}Cells[SizeArray][SizeArray];

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
	
	ReleaseDC(hWnd, hdc);
	
}

class Snake
{
private:						
	
	int x;
	int y;
	
	void Drwing(int x, int y)
	{
		Square(Cells[x][y].x, Cells[x][y].y, Green);	
		Field[x][y] = 1;
	}
	
	void Motion()
	{	
		head++; 
		tail = (head - (length - 1)) - 1;
	}
	
	void Control()
	{ 	
		for(int i = 37; i != 40; i++)
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
	}

};

Snake a;

void INIT()
{	
	SetCoordinatesForCells();
	
}

void START()
{  
	a.main();
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






