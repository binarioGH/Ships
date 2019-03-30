#include <stdio.h>
#include <list>
#include <windows.h>
#include <conio.h>

#define W 119
#define S 115
#define A 97
#define D 100
#define UP 30
#define DOWN 31
#define LEFT 17
#define RIGHT 16

void gotoxy(int x, int y);
void hideCursor(void);
void drawBorders(int bx, int by);
void cls(void);

class Ship{
private:
	int x,y;
	int dx=0, dy=-1;
	int sprite =  UP;
	void collition(void);
public:
	Ship(int _x, int _y){
		x = _x;
		y = _y;
	}
	Ship(int _x, int _y, int _dx, int _dy){
		x = _x;
		y = _y;
		dx = _dx;
		dy = _dy;
	}
	~Ship(void){}
	void keyMove(void);
	void move(int key);
	bool death = false;
};
void Ship::keyMove(void){
	char k = 'k';
	if(kbhit()){
		k = getch();
	}
	Ship::move(k);
	return;
}
void Ship::move(int key){
	gotoxy(x,y);printf(" ");
	switch(key){
		case W:dx=0;dy=-1;sprite=UP;break;
		case S:dx=0;dy=1;sprite=DOWN;break;
		case A:dx=-1;dy=0;sprite=LEFT;break;
		case D:dx=1;dy=-0;sprite=RIGHT;break;
	}
	Ship::collition();
	x+=dx;
	y+=dy;
	gotoxy(x,y);printf("%c", sprite);
	return;
}
void Ship::collition(void){
	if((x>=78 || x<=2 )|| (y>=22 || y<=2)){
		x-=dx;
		y-=dy;
		death = true;
	}
	return;
}


int main(){
	hideCursor();
	cls();
	drawBorders(205,219);
	Ship ms (39,11);
	while(!ms.death){
		ms.keyMove();
		Sleep(100);
	}

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

void hideCursor(void){
	HANDLE hCon;
	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci;
	cci.dwSize = 0;
	cci.bVisible = FALSE;
	SetConsoleCursorInfo(hCon, &cci);
	return;
}
void drawBorders(int bx, int by){
	int x, y;
	for(x=2;x<78;x++){
		y = 2;
		gotoxy(x,y);printf("%c", bx);
		y = 22;
		gotoxy(x,y);printf("%c", bx);
	}
	for(y=2;y<22;y++){
		x = 2;
		gotoxy(x,y);printf("%c", by);
		x = 78;
		gotoxy(x,y);printf("%c", by);
	}
	return;
}

void cls(void){
	int x,y;
	for(y=0;y<=24;y++){
		for(x=0;x<=80;x++){
			gotoxy(x,y);printf(" ");
		}
	}
	return;
}