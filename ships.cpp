#include <stdio.h>
#include <list>
#include <windows.h>
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
	void Bshoot(int des, int mdes, int mv1, int mv2);
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
	int key=0;
	int des = rand()%2;
	int mdes = rand()%2;
	if((eY == y) && (DX == dx)){
		Ship::Bshoot(des, mdes, W, S);
		return;
	}
	else if((eX == x) && (DY == dy)){
		Ship::Bshoot(des, mdes, A,D);
		return;
	}
	if(x == 3 || x == 76){
		dx *=-1;
	}
	if(y == 3 || y == 21){
		dy *=-1;
	}
	
	return;
}

void Ship::Bshoot(int des, int mdes, int mv1, int mv2){
	if(des == 0){
		shooting = true;
	}
	else{
		if(mdes){
			Ship::move(mv1);
		}
		else{
			Ship::move(mv2);
		}
	}
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
	while(!ms.death){
		ms.keyMove();
		es.botMove(ms.X(), ms.Y(), ms.XD(), ms.YD());
		if(ms.shooting){
			bullets.push_back(new Bullet(ms.X()+(ms.XD()*2),ms.Y()+(ms.YD() *2),ms.XD(), ms.YD()));
            ms.shooting = false;			
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