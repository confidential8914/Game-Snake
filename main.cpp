
#include       "C:\dllBridge\Lego\WinMain.h"  
using namespace Lego;

const short int FieldX = 24;
const short int FieldY = 24;
const short int size  = 500;

HPEN     pen;
HBRUSH brush;


const int Red   = RGB(255, 51, 51);
const int Green = RGB(  0, 204, 0);
const int Gray  = RGB( 96, 96, 96);

int Field[20][20];

void DrawingField(int x, int y, int size)
{
	hdc = GetDC(hWnd);
			
	pen = CreatePen(PS_SOLID , 1 , Gray);	
	SelectObject (hdc, pen);		
	
	for(int i = 0; i < 2; i++)
	{
		MoveToEx(hdc, x, y + (i * size), NULL); 
		LineTo(hdc, x + size, y + (i * size));		
		
		MoveToEx(hdc, x + (i * size), y, NULL); 
		LineTo(hdc, x + (i * size), y + size);			
	}
	
	ReleaseDC(hWnd, hdc);
	
}


void INIT()
{	
}

void START()
{  
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






