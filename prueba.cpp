#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <list>

#define W 119
#define S 115
#define A 97
#define D 100


void gotoxy(int x, int y);
void hidecursor(void);
void drawBorders(int bx, int by);

class Dot{
private:
	int x, y;
	void collition(void);
public:
	Dot(int _x, int _y){x=_x;y=_y;}
	void move(int key);
	void keyMove(void);
};
void Dot::keyMove(void){
	if(kbhit()){
		char key = getch();
		Dot::move(key);
	}
	return;
}
void Dot::move(int key){
	gotoxy(x,y);printf(" ");
	switch(key){
		case W:y-=1;break;
		case S:y+=1;break;
		case A:x-=1;break;
		case D:x+=1;break;
	}
	Dot::collition();
	gotoxy(x,y);printf("*"); 
	return;
}
void Dot::collition(void){
	if(x <= 2){
		x += 1;
	}
	if(x >= 78){
		x -=1;
	}
	if(y <= 2){
		y += 1;
	}
	if(y >= 22){
		y -= 1;
	}
	return;
}
int main(){
	system("cls");
	drawBorders(219, 219);
	Dot dt (37,11);
	while(true){
		dt.keyMove();
	}
	gotoxy(0,23);
	return 0;
}

void gotoxy(int x, int y){
	HANDLE hCon;
	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X = x;
	dwPos.Y = y;
	SetConsoleCursorPosition(hCon, dwPos);
	return;
}

void hidecursor(void){
	HANDLE hCon;
	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci;
	cci.dwSize = 0;
	cci.bVisible = FALSE;
	SetConsoleCursorInfo(hCon, &cci);
	return;
}

void drawBorders(int bx, int by){
	int x = 2, y = 2;
	for(x;x <= 78;x++){
		y = 2;
		gotoxy(x,y);printf("%c", bx);
		y = 22;
		gotoxy(x,y);printf("%c", bx);
	}
	for(y=2;y<=22;y++){
		x=2;
		gotoxy(x,y);printf("%c", by);
		x=78;
		gotoxy(x,y);printf("%c", by);
	}
	return;
}