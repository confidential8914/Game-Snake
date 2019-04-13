
#include       "C:\dllBridge\Lego\WinMain.h"  
using namespace Lego;

#include <fstream>
using namespace std;

Button  BtnSave, BtnExit;
EditBox EdtName; 

void INIT()
{	
	EdtName.Create("Enter your name", 10, 45, 105, 25);
	
	BtnSave.Create("Save", 120, 45, 75, 25);
	BtnExit.Create("Exit", 200, 45, 75, 25);
	
	Print_Set_Font(7);
	
	Print(10, 10, "--------Saving-player-data--------");
}

void Save(char name[50])
{
	char path[100];
	sprintf(path, "%s%s%s", "Users\\", name, ".txt");
	
	ofstream file;
	file.open(path);
	
	file << name;
}

void START()
{  
	if(BtnSave.Press())
		Save(EdtName.GetText());
			
	if(BtnExit.Press())
		exit(0);
}







//     В этой функции Вы можете рисовать. Контекст уже захвачен функцией BeginPaint() и будет освобождён автоматически.
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////     void mainPAINT()    /////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void mainPAINT()
{




}








//     Эта функция вызывается из оконной процедуры WndProc(), если пользователь выбрал:
// 1)  Какой-либо пункт меню.
// 2)  Нажал кнопку.	

////////////////////////////////////////////////////            
void ScanButtonsAndMenuItems(int item)            //                  
{
	


 
}






