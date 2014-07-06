#include"SnakeGame.h"

SnakeGame::SnakeGame(){
	initial();
}

void SnakeGame::initial(){
	snakeX[0] = snakeX[1] = 1;
	snakeX2[0] = snakeX2[1] = 30;
	snakeX3[0] = snakeX3[1] = 30;
	snakeY[0] = 2;
	snakeY[1] = 1;
	snakeY2[0] = snakeY3[0] = 29;
	snakeY2[1] = snakeY3[1] = 30;
	order = 'd';
	order3 = 75;
	length = lengthcom = length3 = 2;
	score = score2 = score3 = 0;
	temp = again = jump = last = '0';
}

void  SnakeGame::moveCursorTo(short row, short column){    //���ù��λ��
	COORD  toPos = { column, row };
	SetConsoleCursorPosition(hOut, toPos);
}

void SnakeGame::hideCursor(void){             // ���ù�겻�ɼ�
	CONSOLE_CURSOR_INFO  cur;
	GetConsoleCursorInfo(hOut, &cur);
	cur.bVisible = 0;
	SetConsoleCursorInfo(hOut, &cur);
}

void SnakeGame::judge(void){               //�ж�ָ��� 
	if (order == 'w'){
		snakeX[0] -= 1;
	}
	else if (order == 's'){
		snakeX[0] += 1;
	}
	else if (order == 'a'){
		snakeY[0] -= 1;
	}
	else if (order == 'd'){
		snakeY[0] += 1;
	}
}
void SnakeGame::judge2(void){               //�ж�ָ��� 
	if (order2 == 'w'){
		snakeX2[0] -= 1;
	}
	else if (order2 == 's'){
		snakeX2[0] += 1;
	}
	else if (order2 == 'a'){
		snakeY2[0] -= 1;
	}
	else if (order2 == 'd'){
		snakeY2[0] += 1;
	}
}
void SnakeGame::judge3(void){               //�ж�ָ��� 
	if (order3 == 72){
		snakeX3[0] -= 1;
	}
	else if (order3 == 80){
		snakeX3[0] += 1;
	}
	else if (order3 == 75){
		snakeY3[0] -= 1;
	}
	else if (order3 == 77){
		snakeY3[0] += 1;
	}
}

void SnakeGame::put_money(void){           //�����Һ��� 
	moneyX = rand() % (H - 1) + 1;
	moneyY = rand() % (H - 1) + 1;
	while (map[moneyX][moneyY] == body || map[moneyX][moneyY] == head || map[moneyX][moneyY] == food){
		moneyX = rand() % (H - 1) + 1;
		moneyY = rand() % (H - 1) + 1;
	}
	moveCursorTo(moneyX, moneyY);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
	printf("%c", food);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
	map[moneyX][moneyY] = food;
}

void SnakeGame::prepare(void){                //��ͼ���ٶȳ�ʼ������
	H = 30;
	speed = 6;
	for (i = 0; i<H + 2; i++){
		map[0][i] = wall;
		map[H + 1][i] = wall;
		map[i][H + 2] = '\0';
	}
	for (i = 1; i<H + 1; i++){
		for (j = 1; j<H + 1; j++){
			map[i][j] = ' ';
		}
		map[i][0] = wall;
		map[i][H + 1] = wall;
	}
	map[1][1] = body;
	map[1][2] = head;
	map[30][30] = body;
	map[30][29] = head;
}

void SnakeGame::record(void){              //��¼Ӱ������
	recordX[0] = snakeX[0];
	recordY[0] = snakeY[0];
	recordX[1] = snakeX[length - 1];
	recordY[1] = snakeY[length - 1];
}
void SnakeGame::record2(void){              //��¼Ӱ������
	recordX2[0] = snakeX2[0];
	recordY2[0] = snakeY2[0];
	recordX2[1] = snakeX2[lengthcom - 1];
	recordY2[1] = snakeY2[lengthcom - 1];
}
void SnakeGame::record3(void){              //��¼Ӱ������
	recordX3[0] = snakeX3[0];
	recordY3[0] = snakeY3[0];
	recordX3[1] = snakeX3[length3 - 1];
	recordY3[1] = snakeY3[length3 - 1];
}

void SnakeGame::gameover(void){              //��������
	order = 'd';
	order3 = 75;
	order2 = 0;
	if (sinormul == '1'){
		moveCursorTo(6, H + 12);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
		printf("�ҵĵ����ǲ���սʤ�ģ�");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
		moveCursorTo(32, 0);
		printf("���¿�ʼ��Y/N)");
		do{
			temp = getch();
		} while (temp != 'y'&&temp != 'Y'&&temp != 'n'&&temp != 'N');
		if (temp == 'y' || temp == 'Y')again = '0';
		else if (temp == 'n' || temp == 'N') again = '1';
	}
	else if (sinormul == '2'){
		moveCursorTo(6, H + 12);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
		printf("���1���ˣ�");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
		moveCursorTo(32, 0);
		printf("���¿�ʼ��Y/N)");
		do{
			temp = getch();
		} while (temp != 'y'&&temp != 'Y'&&temp != 'n'&&temp != 'N');
		if (temp == 'y' || temp == 'Y')again = '0';
		else if (temp == 'n' || temp == 'N') again = '1';
	}
}
void SnakeGame::gameover2(void){              //��������
	order = 'd';
	order3 = 75;
	order2 = 0;
	moveCursorTo(6, H + 12);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_RED);
	printf("�ҵĵ��������ⲻ��ѧ��");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
	moveCursorTo(32, 0);
	printf("���¿�ʼ��Y/N)");
	do{
		temp = getch();
	} while (temp != 'y'&&temp != 'Y'&&temp != 'n'&&temp != 'N');
	if (temp == 'y' || temp == 'Y')again = '0';
	else if (temp == 'n' || temp == 'N') again = '1';
}
void SnakeGame::gameover3(void){              //��������
	order = 'd';
	order3 = 75;
	order2 = 0;
	moveCursorTo(6, H + 12);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_RED);
	printf("���2���ˣ�");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
	moveCursorTo(32, 0);
	printf("���¿�ʼ��Y/N)");
	do{
		temp = getch();
	} while (temp != 'y'&&temp != 'Y'&&temp != 'n'&&temp != 'N');
	if (temp == 'y' || temp == 'Y')again = '0';
	else if (temp == 'n' || temp == 'N') again = '1';
}

void SnakeGame::move(void){               //�ƶ�������
	for (i = length - 1; i>1; i--){
		snakeX[i] = snakeX[i - 1];
		snakeY[i] = snakeY[i - 1];
	}
	snakeX[1] = recordX[0];
	snakeY[1] = recordY[0];
}
void SnakeGame::move2(void){               //�ƶ�������
	for (i = lengthcom - 1; i>1; i--){
		snakeX2[i] = snakeX2[i - 1];
		snakeY2[i] = snakeY2[i - 1];
	}
	snakeX2[1] = recordX2[0];
	snakeY2[1] = recordY2[0];
}
void SnakeGame::move3(void){               //�ƶ�������
	for (i = length3 - 1; i>1; i--){
		snakeX3[i] = snakeX3[i - 1];
		snakeY3[i] = snakeY3[i - 1];
	}
	snakeX3[1] = recordX3[0];
	snakeY3[1] = recordY3[0];
}

void SnakeGame::print(void){               //ˢ�½��溯�� 
	int j;
	system("cls");
	for (j = 0; j<H + 2; j++){
		if (j == 0){
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE);
			printf("%s", map[j]);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
			printf("   W:up S:down A:left D:right Esc:exit\n");
		}
		else if (j == 2){
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE);
			printf("%s", map[j]);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
			printf("     PLAYER1 SCORE:%ld\n", score);
		}
		else if (j == 3){
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE);
			printf("%s", map[j]);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
			printf("     COMPUTER SCORE:%ld\n", score2);
		}
		else if (j == 4){
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE);
			printf("%s", map[j]);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
			printf("     PLAYER2 SCORE:%ld\n", score3);
		}
		else{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE);
			printf("%s\n", map[j]);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
		}
	}
	moveCursorTo(2, H + 21);                     //�ƶ���굽�����仯��λ
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
	printf("%ld", score);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
	moveCursorTo(3, H + 22);                     //�ƶ���굽�����仯��λ
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_RED);
	printf("%ld", score2);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
	moveCursorTo(4, H + 21);                     //�ƶ���굽�����仯��λ
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_RED);
	printf("%ld", score3);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
}

void SnakeGame::choose(void){
	moveCursorTo(7, 35);
	printf("̰����");
	moveCursorTo(10, 33);
	printf("1.������Ϸ");
	moveCursorTo(13, 33);
	printf("2.˫����Ϸ");
	do{
		sinormul = getch();
	} while (sinormul != '1'&&sinormul != '2');
}

void SnakeGame::start(){
	initial();
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);        //��ȡ�����Ϣ
	hideCursor();               //���ع��
	while (again == '0'){
		if (jump == '1'){
			break;
		}
		initial();
		system("cls");
		prepare();                   //ǰ��׼������
		choose();
		system("cls");
		srand(time(NULL));
		print();
		moveCursorTo(1, 1);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
		printf("%c", body);
		moveCursorTo(1, 2);
		printf("%c", head);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
		moveCursorTo(30, 30);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_RED);
		printf("%c", body);
		moveCursorTo(30, 29);
		printf("%c", head);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);

		put_money();
		put_money();

		while (1){
			record();                     //record�����¼��ͷ��β�仯ǰ���� 
			record2();
			Sleep(225 - speed * 20);

			if (kbhit())                 // ������޻���������ͣ��)
				temp = getch();
			if (temp == 'w' || temp == 's' || temp == 'a' || temp == 'd' || temp == 27){
				if (order == 'w'&&temp != 's')order = temp;
				else if (order == 's'&&temp != 'w')order = temp;
				else if (order == 'a'&&temp != 'd')order = temp;
				else if (order == 'd'&&temp != 'a')order = temp;
				else temp = '0';
			}

			judge();
			if (order == 27){
				jump = '1';
				break;
			}

			if (map[snakeX[0]][snakeY[0]] == wall){            //��ͷ����ǽ 
				gameover();
				break;
			}
			else if (map[snakeX[0]][snakeY[0]] == body || map[snakeX[0]][snakeY[0]] == head){          //��ͷ�������� 
				gameover();
				break;
			}
			else if (map[snakeX[0]][snakeY[0]] == ' '){           //��ͷ������ 
				moveCursorTo(snakeX[0], snakeY[0]);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
				printf("%c", head);                             //�ƶ���굽��ͷ�仯��λ
				map[snakeX[0]][snakeY[0]] = head;
				if (length>1){
					move();
				}
				for (i = 1; i<length; i++){
					moveCursorTo(snakeX[i], snakeY[i]);
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
					printf("%c", body);                         //�ƶ���굽����仯��λ
					map[snakeX[i]][snakeY[i]] = body;
				}
				moveCursorTo(recordX[1], recordY[1]);
				printf(" ");
				map[recordX[1]][recordY[1]] = ' ';
			}
			else if (map[snakeX[0]][snakeY[0]] == food){          //��ͷ������� 
				length++;
				moveCursorTo(snakeX[0], snakeY[0]);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
				printf("%c", head);                             //�ƶ���굽��ͷ�仯��λ
				map[snakeX[0]][snakeY[0]] = head;
				if (length>1){
					move();
				}
				for (i = 1; i<length; i++){
					moveCursorTo(snakeX[i], snakeY[i]);       //�ƶ���굽����仯��λ
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
					printf("%c", body);
					map[snakeX[i]][snakeY[i]] = body;
				}
				score += 5 * speed;
				put_money();
				moveCursorTo(2, H + 21);                     //�ƶ���굽�����仯��λ
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
				printf("%ld", score);
			}
			//computer
			if (sinormul == '1'){
				inc = 0;
				for (i = 1; i <= H; i++){
					for (j = 1; j <= H; j++){
						if (map[i][j] == food){
							shortX[inc] = i;
							shortY[inc] = j;
							inc = (inc + 1) % 2;
						}
					}
				}
				if (((snakeX2[0] - shortX[0])*(snakeX2[0] - shortX[0]) + (snakeY2[0] - shortY[0])*(snakeY2[0] - shortY[0]))<((snakeX2[0] - shortX[1])*(snakeX2[0] - shortX[1]) + (snakeY2[0] - shortY[1])*(snakeY2[0] - shortY[1]))){
					moneyX = shortX[0];
					moneyY = shortY[0];
				}
				else{
					moneyX = shortX[1];
					moneyY = shortY[1];
				}
				if (moneyY != snakeY2[0]){
					if (moneyY - snakeY2[0]>0){
						if (map[snakeX2[0]][snakeY2[0] + 1] != head&&map[snakeX2[0]][snakeY2[0] + 1] != body&&map[snakeX2[0]][snakeY2[0] + 1] != wall){
							order2 = 'd';
						}
						else if (map[snakeX2[0] - 1][snakeY2[0]] != head&&map[snakeX2[0] - 1][snakeY2[0]] != body&&map[snakeX2[0] - 1][snakeY2[0]] != wall){
							order2 = 'w';
						}
						else{
							order2 = 's';
						}
					}
					else if (moneyY - snakeY2[0]<0){
						if (map[snakeX2[0]][snakeY2[0] - 1] != head&&map[snakeX2[0]][snakeY2[0] - 1] != body&&map[snakeX2[0]][snakeY2[0] - 1] != wall){
							order2 = 'a';
						}
						else if (map[snakeX2[0] - 1][snakeY2[0]] != head&&map[snakeX2[0] - 1][snakeY2[0]] != body&&map[snakeX2[0] - 1][snakeY2[0]] != wall){
							order2 = 'w';
						}
						else if (map[snakeX2[0] + 1][snakeY2[0]] != head&&map[snakeX2[0] + 1][snakeY2[0]] != body&&map[snakeX2[0] + 1][snakeY2[0]] != wall){
							order2 = 's';
						}
					}
				}
				else if (moneyY == snakeY2[0]){
					if (moneyX - snakeX2[0]>0){
						if (map[snakeX2[0] + 1][snakeY2[0]] != head&&map[snakeX2[0] + 1][snakeY2[0]] != body&&map[snakeX2[0] + 1][snakeY2[0]] != wall){
							order2 = 's';
						}
						else if (map[snakeX2[0]][snakeY2[0] + 1] != head&&map[snakeX2[0]][snakeY2[0] + 1] != body&&map[snakeX2[0]][snakeY2[0] + 1] != wall){
							order2 = 'd';
						}
						else if (map[snakeX2[0]][snakeY2[0] - 1] != head&&map[snakeX2[0]][snakeY2[0] - 1] != body&&map[snakeX2[0]][snakeY2[0] - 1] != wall){
							order2 = 'a';
						}
					}
					else if (moneyX - snakeX2[0]<0){
						if (map[snakeX2[0] - 1][snakeY2[0]] != head&&map[snakeX2[0] - 1][snakeY2[0]] != body&&map[snakeX2[0] - 1][snakeY2[0]] != wall){
							order2 = 'w';
						}
						else if (map[snakeX2[0]][snakeY2[0] + 1] != head&&map[snakeX2[0]][snakeY2[0] + 1] != body&&map[snakeX2[0]][snakeY2[0] + 1] != wall){
							order2 = 'd';
						}
						else if (map[snakeX2[0]][snakeY2[0] - 1] != head&&map[snakeX2[0]][snakeY2[0] - 1] != body&&map[snakeX2[0]][snakeY2[0] - 1] != wall){
							order2 = 'a';
						}
					}
				}
				if (map[snakeX2[0] - 1][snakeY2[0]] == head || map[snakeX2[0] - 1][snakeY2[0]] == body || map[snakeX2[0] - 1][snakeY2[0]] == wall){
					if (map[snakeX2[0]][snakeY2[0] - 1] == head || map[snakeX2[0]][snakeY2[0] - 1] == body || map[snakeX2[0]][snakeY2[0] - 1] == wall){
						if (map[snakeX2[0]][snakeY2[0] + 1] == head || map[snakeX2[0]][snakeY2[0] + 1] == body || map[snakeX2[0]][snakeY2[0] + 1] == wall){
							if (map[snakeX2[0] + 1][snakeY2[0]] == head || map[snakeX2[0] + 1][snakeY2[0]] == body || map[snakeX2[0] + 1][snakeY2[0]] == wall){
								gameover2();
								break;
							}
						}
					}
				}
				if (map[snakeX2[0] + 1][snakeY2[0]] == head || map[snakeX2[0] + 1][snakeY2[0]] == body || map[snakeX2[0] + 1][snakeY2[0]] == wall){
					if (map[snakeX2[0] - 1][snakeY2[0]] == head || map[snakeX2[0] - 1][snakeY2[0]] == body || map[snakeX2[0] - 1][snakeY2[0]] == wall){
						if (map[snakeX2[0]][snakeY2[0] + 1] == head || map[snakeX2[0]][snakeY2[0] + 1] == body || map[snakeX2[0]][snakeY2[0] + 1] == wall){
							order2 = 'a';
						}
					}
				}
				if (map[snakeX2[0] + 1][snakeY2[0]] == head || map[snakeX2[0] + 1][snakeY2[0]] == body || map[snakeX2[0] + 1][snakeY2[0]] == wall){
					if (map[snakeX2[0] - 1][snakeY2[0]] == head || map[snakeX2[0] - 1][snakeY2[0]] == body || map[snakeX2[0] - 1][snakeY2[0]] == wall){
						if (map[snakeX2[0]][snakeY2[0] - 1] == head || map[snakeX2[0]][snakeY2[0] - 1] == body || map[snakeX2[0]][snakeY2[0] - 1] == wall){
							order2 = 'd';
						}
					}
				}
				if (map[snakeX2[0] + 1][snakeY2[0]] == head || map[snakeX2[0] + 1][snakeY2[0]] == body || map[snakeX2[0] + 1][snakeY2[0]] == wall){
					if (map[snakeX2[0]][snakeY2[0] - 1] == head || map[snakeX2[0]][snakeY2[0] - 1] == body || map[snakeX2[0]][snakeY2[0] - 1] == wall){
						if (map[snakeX2[0]][snakeY2[0] + 1] == head || map[snakeX2[0]][snakeY2[0] + 1] == body || map[snakeX2[0]][snakeY2[0] + 1] == wall){
							order2 = 'w';
						}
					}
				}
				if (map[snakeX2[0] - 1][snakeY2[0]] == head || map[snakeX2[0] - 1][snakeY2[0]] == body || map[snakeX2[0] - 1][snakeY2[0]] == wall){
					if (map[snakeX2[0]][snakeY2[0] - 1] == head || map[snakeX2[0]][snakeY2[0] - 1] == body || map[snakeX2[0]][snakeY2[0] - 1] == wall){
						if (map[snakeX2[0]][snakeY2[0] + 1] == head || map[snakeX2[0]][snakeY2[0] + 1] == body || map[snakeX2[0]][snakeY2[0] + 1] == wall){
							order2 = 's';
						}
					}
				}
				judge2();
				if (snakeX2[0] == snakeX2[1] && snakeY2[0] == snakeY2[1]){     //�������˿��� 
					snakeX2[0] = recordX2[0];
					snakeY2[0] = recordY2[0];
					continue;
				}
				if (map[snakeX2[0]][snakeY2[0]] == wall){            //��ͷ����ǽ 
					gameover2();
					break;
				}
				else if (map[snakeX2[0]][snakeY2[0]] == body || map[snakeX2[0]][snakeY2[0]] == head){          //��ͷ�������� 
					gameover2();
					break;
				}
				else if (map[snakeX2[0]][snakeY2[0]] == ' '){           //��ͷ������ 
					moveCursorTo(snakeX2[0], snakeY2[0]);
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_RED);
					printf("%c", head);                             //�ƶ���굽��ͷ�仯��λ
					map[snakeX2[0]][snakeY2[0]] = head;
					if (lengthcom>1){
						move2();
					}
					for (i = 1; i<lengthcom; i++){
						moveCursorTo(snakeX2[i], snakeY2[i]);
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_RED);
						printf("%c", body);                         //�ƶ���굽����仯��λ
						map[snakeX2[i]][snakeY2[i]] = body;
					}
					moveCursorTo(recordX2[1], recordY2[1]);
					printf(" ");
					map[recordX2[1]][recordY2[1]] = ' ';
				}
				else if (map[snakeX2[0]][snakeY2[0]] == food){          //��ͷ������� 
					lengthcom++;
					moveCursorTo(snakeX2[0], snakeY2[0]);
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_RED);
					printf("%c", head);                             //�ƶ���굽��ͷ�仯��λ
					map[snakeX2[0]][snakeY2[0]] = head;
					if (lengthcom>1){
						move2();
					}
					for (i = 1; i<lengthcom; i++){
						moveCursorTo(snakeX2[i], snakeY2[i]);       //�ƶ���굽����仯��λ
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_RED);
						printf("%c", body);
						map[snakeX2[i]][snakeY2[i]] = body;
					}
					score2 += 5 * speed;
					put_money();
					moveCursorTo(3, H + 22);                     //�ƶ���굽�����仯��λ
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_RED);
					printf("%ld", score2);
				}
			}

			//player2
			if (sinormul == '2'){
				record3();
				if (kbhit())                 // ������޻���������ͣ��)
					temp = getch();
				if (temp == 72 || temp == 80 || temp == 75 || temp == 77 || temp == 27){
					if (order3 == 72 && temp != 80)order3 = temp;
					else if (order3 == 80 && temp != 72)order3 = temp;
					else if (order3 == 75 && temp != 77)order3 = temp;
					else if (order3 == 77 && temp != 75)order3 = temp;
					else temp = '0';
				}

				judge3();
				if (order3 == 27){
					jump = '1';
					break;
				}

				if (map[snakeX3[0]][snakeY3[0]] == wall){            //��ͷ����ǽ 
					gameover3();
					break;
				}
				else if (map[snakeX3[0]][snakeY3[0]] == body || map[snakeX3[0]][snakeY3[0]] == head){          //��ͷ�������� 
					gameover3();
					break;
				}
				else if (map[snakeX3[0]][snakeY3[0]] == ' '){           //��ͷ������ 
					moveCursorTo(snakeX3[0], snakeY3[0]);
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE);
					printf("%c", head);                             //�ƶ���굽��ͷ�仯��λ
					map[snakeX3[0]][snakeY3[0]] = head;
					if (length3>1){
						move3();
					}
					for (i = 1; i<length3; i++){
						moveCursorTo(snakeX3[i], snakeY3[i]);
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE);
						printf("%c", body);                         //�ƶ���굽����仯��λ
						map[snakeX3[i]][snakeY3[i]] = body;
					}
					moveCursorTo(recordX3[1], recordY3[1]);
					printf(" ");
					map[recordX3[1]][recordY3[1]] = ' ';
				}
				else if (map[snakeX3[0]][snakeY3[0]] == food){          //��ͷ������� 
					length3++;
					moveCursorTo(snakeX3[0], snakeY3[0]);
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE);
					printf("%c", head);                             //�ƶ���굽��ͷ�仯��λ
					map[snakeX3[0]][snakeY3[0]] = head;
					if (length3>1){
						move3();
					}
					for (i = 1; i<length3; i++){
						moveCursorTo(snakeX3[i], snakeY3[i]);       //�ƶ���굽����仯��λ
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE);
						printf("%c", body);
						map[snakeX3[i]][snakeY3[i]] = body;
					}
					score3 += 5 * speed;
					put_money();
					moveCursorTo(4, H + 21);                     //�ƶ���굽�����仯��λ
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE);
					printf("%ld", score3);
				}
			}
		}
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
	system("cls");
	printf("\n");
	return;
}
