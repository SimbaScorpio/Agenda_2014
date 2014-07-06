#ifndef SNAKEGAME_H
#define SNAKEGAME_H

#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>
#include<windows.h>
#define maxlength 500
#define head 001
#define body 002
#define wall '%'
#define food 004

class SnakeGame{
public:
	SnakeGame();
	void start();
	void  moveCursorTo(short row, short column);
	void  hideCursor(void);
	void judge(void);
	void judge2(void);
	void judge3(void);
	void put_money(void);
	void prepare(void);
	void record(void);
	void record2(void);
	void record3(void);
	void gameover(void);
	void gameover2(void);
	void gameover3(void);
	void move(void);
	void move2(void);
	void move3(void);
	void print(void);
	void choose(void);
	void initial(void);
private:
	int snakeX[maxlength], snakeX2[maxlength], snakeX3[maxlength];
	int snakeY[maxlength], snakeY2[maxlength], snakeY3[maxlength];
	char order, order2, order3;
	int i, j;
	int length, lengthcom, length3;
	int moneyX, moneyY, recordX[2], recordY[2], recordX2[2], recordY2[2], recordX3[2], recordY3[2];
	long score, score2, score3;
	int speed;
	int H;
	int shortX[2], shortY[2], inc;
	char map[45][45];
	HANDLE hOut;
	char sinormul;
	char temp, again, jump, last;
};

#endif