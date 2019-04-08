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
	int type;
	Bullet(int _x, int _y, int _dx, int _dy, int t){
		x = _x;
		y = _y;
		dx = _dx;
		dy = _dy;
		type = t;
	}
	void move(void);
	int X(void){return x;}
	int Y(void){return y;}
	bool death = false;
	
};
void Bullet::collition(void){
	if((x>=76 || x<=3) || (y<=3 || y>=20)){
		death = true;
	}
	return;
}
void Bullet::move(void){
	gotoxy(x,y);printf(" ");
	x += dx;
	y += dy;
	Bullet::collition();
	if(!death){
		gotoxy(x,y);printf("%c", 43);
	}
	return;
}

class Ship{
private:
	int x,y;
	int dx=0, dy=-1;
	int sprite =  UP;
	int eX, eY, DX, DY;
	void collition(void);
	bool hor = true, der = true;	
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
class Queen{
private:
	int x, y;
	int der = 1;
	int cooldown = 0;
	int finalcooldown = 0;

public:
	Queen(int _x, int _y){
		x = _x;
		y = _y;
	}
	~Queen(void){}
	int X(void){return x;}
	int Y(void){return y;}
	void move(int eX, int eY);
	void displayLive(void);
	bool death = false;
	int live = 3;
	bool shooting = false;
	bool minion = false;
	bool finalAttack = false;
	bool protection = false;
	bool p = false;
};
void Queen::displayLive(void){
	gotoxy(2,24);printf("                                                                          ");
	gotoxy(2,24);printf("Queen's live: %i", live);
	return;
}
void Queen::move(int eX, int eY){
	gotoxy(x,y);printf("%c", 32);
	x += der;
	if(x <= 3 || x >= 77){
		der *= -1;
		
	}
	gotoxy(x,y);printf("%c",190);
	if(eX == x){
		shooting = true;
	}
	if(eY == 7 && !p){
		protection = true;
		p = true;
	}
	if(!protection ){
		if(cooldown == 30){
		    minion = true;
		    cooldown = 0;
	    }
	    else{
		    cooldown += 1;
		}
	    if(finalcooldown == 100){
		    finalAttack = true;
		    finalcooldown = 0;
	    }
	    else{
		    finalcooldown += 1;
	    }
	}
	return;
}

class Minion{
private:
	int x,y;
	int cooldown = 0;
	void collition(void);
public:
	Minion(int _x, int _y){
		x = _x;
		y = _y;
	}
	~Minion(void){}
	int X(void){return x;}
	int Y(void){return y;}
	void move(void);
	bool shooting = false;
	bool death = false;

};
void Minion::move(void){
	gotoxy(x,y);printf("%c", 32);
	if(cooldown == 5){
		shooting = true;
		cooldown = 0;
	}
	else{
		cooldown += 1;
	}
	y += 1;
	Minion::collition();
	if(!death){
		gotoxy(x,y);printf("%c", 223);
	}
	return;
}
void Minion::collition(void){
	if(y >= 22){
		death = true;
	}
	return;
}
class Sentry{
private:
	int x,y;
	int xd;
	int d;
	void collition(void);
public:
	Sentry(int _x, int _y, int _d){
		x = _x;
		y = _y;
		xd = _d *-1;
		d = _d;
	}
	~Sentry(void){}
	void move(void);
	int X(void){return x;}
	int Y(void){return y;}
	int XD(void){return xd;}
};
void Sentry::move(void){
	gotoxy(x,y);printf("%c", 32); 
	Sentry::collition();
	y += d;
	gotoxy(x,y);printf("%c",206);
	return;
}
void Sentry::collition(void){
	if(y==6 || y == 20){
		d *= -1;
	}
	return;
}

class Protection{
private:
	int x,y;
public:
	Protection(int _x, int _y){
		x = _x;
		y = _y;
		Sleep(10);
		gotoxy(x,y);printf("%c",205); 
	}
	~Protection(void){
		gotoxy(x,y);printf("%c",126);
		Sleep(10);
		gotoxy(x,y);printf("%c", 32);
	}
	void draw(void){
		gotoxy(x,y);printf("%c",205);
	}
	int lives = 3;
	int X(void){return x;}
	int Y(void){return y;}
};
int main(){
	list<Protection*> protectors;
	list<Protection*>::iterator pit;
	list<Sentry*> sentrys;
	list<Sentry*>::iterator sit;
	list<Bullet*> bullets;
	list<Bullet*>::iterator bit; //bit significa bullet iterator
	list<Minion*> minions;
	list<Minion*>::iterator mit;//mit == minion iterator.
	hideCursor();
	cls();
	drawBorders(205,219);
	Ship ms (39,18);
	Queen q (39, 4);
	q.displayLive();
	int x;
	int pp = 0;
	while(!ms.death && !q.death){
		ms.keyMove();
		q.move(ms.X(), ms.Y());
		if(ms.shooting){
			bullets.push_back(new Bullet(ms.X()+(ms.XD()*2),ms.Y()+(ms.YD() *2),ms.XD(), ms.YD(), 1));
            ms.shooting = false;			
		}
		if(q.shooting){
			bullets.push_back(new Bullet(q.X(),q.Y()+1,0,1, 0));
			q.shooting = false;
		}
		if(q.finalAttack){
			for(x=0;x<=4;x+=1){
				minions.push_back(new Minion(x+37, 5));
			}
			q.finalAttack = false;
		}
		if(q.protection){
			int px; 
			for(px=3;px<78;px++){
				protectors.push_back(new Protection(px,5));
			}
			sentrys.push_back(new Sentry(3,6,1));
			sentrys.push_back(new Sentry(77,20,-1));
		}
		if(q.minion){
			minions.push_back(new Minion(q.X(),q.Y()+1));
			q.minion = false;
		}
		for(mit=minions.begin();mit!=minions.end();mit++){
			(*mit)->move();
			if((*mit)->shooting){
				bullets.push_back(new Bullet((*mit)->X()-1,(*mit)->Y(),1,0, 0));
			    bullets.push_back(new Bullet((*mit)->X()+1,(*mit)->Y(),-1,0, 0));
			    bullets.push_back(new Bullet((*mit)->X(),(*mit)->Y()+1,-1,-1, 0));
			    bullets.push_back(new Bullet((*mit)->X(),(*mit)->Y()+1,-1,-1, 0));
			    bullets.push_back(new Bullet((*mit)->X(),(*mit)->Y()+1,-1,1, 0));
			    bullets.push_back(new Bullet((*mit)->X()+1,(*mit)->Y()-1,1,-1, 0));
			    (*mit)->shooting = false;
			}
			for(bit=bullets.begin();bit!=bullets.end();bit++){
				if((*bit)->X() == (*mit)->X() && (*bit)->Y() == (*mit)->Y()){
					(*mit)->death = true;
					(*bit)->death = true;
					delete(*mit);
					mit = minions.erase(mit);
					break;
				}
			}
			for(sit=sentrys.begin();sit!=sentrys.end();sit++){
				if((*sit)->X() == ms.X()){
					bullets.push_back(new Bullet((*sit)->X(), (*sit)->Y(), (*sit)->XD(),0,0));
				}
				if(((*sit)->X() == (*bit)->X() && (*sit)->Y() == (*bit)->Y()) && (*bit)->type == 1){
					delete(*bit);
					bit = bullets.erase(bit);
					delete(*sit);
					sit = sentrys.erase(sit);
				}
				
			}
		}

		for(bit=bullets.begin();bit!=bullets.end();bit++){
			(*bit)->move();
			if((ms.X() == (*bit)->X()) && (ms.Y() == (*bit)->Y())){
				ms.death = true;
			}
			if(q.X() == (*bit)->X() && q.Y() == (*bit)->Y() && (*bit)->type == 1){
				q.live -= 1;
				q.displayLive();
			}
			if((*bit)->death){
				gotoxy((*bit)->X(),(*bit)->Y());printf("%c", 32);
				delete(*bit);
				bit = bullets.erase(bit);
			}
		    pp = 0;
			for(pit=protectors.begin();pit != protectors.end();pit++){
				pp += 1;
				if((*pit)->X() == (*bit)->X() && (*pit)->Y() == (*bit)->Y()){
					delete(*bit);
					bit = bullets.erase(bit);
					(*pit)->lives -= 1;
					(*pit)->draw();
					if((*pit)->lives <= 0){
						delete(*pit);
						pit = protectors.erase(pit);
					}
				}
			}			
		}
		if(pp == 0){
			q.p = false;
		}
		if(q.live <= 0){
				q.death = true;
		}
		Sleep(100);
	}
	for(bit=bullets.begin();bit!=bullets.end();bit++){
		delete(*bit);
		bit = bullets.erase(bit);
	}
	for(mit=minions.begin();mit!=minions.end();mit++){
		delete(*mit);
		mit = minions.erase(mit);
	}
	delete &ms;
	delete &q;
	cls();
	drawBorders(190, 190);
	gotoxy(35, 12);
	if(q.death){
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