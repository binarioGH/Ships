#include <stdio.h>
#include <list>
#include <windows.h>
#include <string>
#include <conio.h>
using namespace std;
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

class Bullet{
private:
	int x,y;
	int dx, dy;
	void collition(void);
public:
	Bullet(int _x, int _y, int _dx, int _dy){
		x = _x;
		y = _y;
		dx = _dx;
		dy = _dy;
	}
	void move(void);
	int X(void){return x;}
	int Y(void){return y;}
	bool death = false;
};
void Bullet::collition(void){
	if((x>=78 || x<=2) || (y>=22 || y <= 2)){
		death = true;
	}
	return;
}
void Bullet::move(void){
	gotoxy(x,y);printf(" ");
	x += dx;
	y += dy;
	gotoxy(x,y);printf("%c", 43);
	Bullet::collition();
	return;
}

class Ship{
private:
	int x,y;
	int dx=0, dy=-1;
	int sprite =  UP;
	int eX, eY, DX, DY;
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
	void botMove(int enemyX, int enemyY, int enemyXdir, int enemyYdir);
	void move(int key);
	int X(void){return x;}
	int Y(void){return y;}
	int XD(void){return dx;}
	int YD(void){return dy;}
	bool death = false;
	bool shooting = false;
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
		case 32:shooting = true;break;
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
void Ship::botMove(int enemyX, int enemyY,int enemyXdir,int enemyYdir){
	eX = enemyX;
	eY = enemyY;
	DX = enemyXdir;
	DY = enemyYdir;
	int key = 0;
	int des = rand()%2;
	int mdes = rand()%2;
	if(x == eX && ((DX == dx && dy == DY) || (dx == DX*-1 && DY*-1 == dy))){
		if(mdes == 0){
			key = 32;
			return;
		}
		else{
			if(des == 1){
				key = A;
			}
			else{
				key = D;
			}
		}
	}
	if(y == eY && ((DX == dx && dy == DY) || (dx == DX*-1 && DY*-1 == dy))){
		if(mdes == 0){
			key = 32;
			return;
		}
		else{
			if(des == 1){
				key = W;
			}
			else{
				key = S;
			}
		}
	}
	if(x == 3){
		key = D;
	}
	else if(x == 77){
		key = A;
	}
	if(y == 3){
		key = S;
	}
	else if(y == 21){
		key = W;
	}
	Ship::move(key);
	return;
}

int main(){
	list<Bullet*> bullets;
	list<Bullet*>::iterator bit; //bit significa bullet iterator
	hideCursor();
	cls();
	drawBorders(205,219);
	Ship ms (39,18);
	Ship es (39, 6);
	while(!ms.death && !es.death){
		ms.keyMove();
		es.botMove(ms.X(), ms.Y(), ms.XD(), ms.YD());
		if(ms.shooting){
			bullets.push_back(new Bullet(ms.X()+(ms.XD()*2),ms.Y()+(ms.YD() *2),ms.XD(), ms.YD()));
            ms.shooting = false;			
		}
		if(es.shooting){
			bullets.push_back(new Bullet(es.X()+(es.XD()*2),es.Y()+(es.YD() *2),es.XD(), es.YD()));
            es.shooting = false;	
		}
		for(bit=bullets.begin();bit!=bullets.end();bit++){
			(*bit)->move();
			if((ms.X() == (*bit)->X()) && (ms.Y() == (*bit)->Y())){
				ms.death = true;
			}
			else if((es.X() == (*bit)->X()) && (es.Y() == (*bit)->Y())){
				es.death = true;
			}
			if((*bit)->death){
				delete(*bit);
				bit = bullets.erase(bit);
			}
		}
		Sleep(100);
	}
	cls();
	drawBorders(190, 190);
	gotoxy(35, 12);
	if(es.death){
		printf(" You  Won");
	}
	else{
		printf(" You Lost");
	}
	Sleep(3000);
	gotoxy(0,24);
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