#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;

bool GameOver;
const int Width = 20;
const int Height = 20;
int HeadX, HeadY, FruitX, FruitY, score;
enum direction { STOP = 0, LEFT, RIGHT, UP, DOWN};
direction dir;
int tailX[500], tailY[500];
int nTail; //Length of the Tail

void Setup(){
	GameOver = false;
	dir = STOP;
	HeadX = (Width) / 2;
	HeadY = (Height) / 2;
	FruitX = rand() % Width;
	FruitY = rand() % Height;
	nTail = 0;
	score = 0;
}

void Draw(){
	system("cls");
	for(int i = 0; i < Width + 2; ++i){
		cout << "+";
	}
	cout << '\n';

	for(int i = 0; i < Height; ++i){
		for(int j = -1; j < Width + 1; ++j){
			if(j == -1){
				cout << "+";
			}
			else if(j == Width){
				cout << "+";
			}
			else if(i == HeadY && j == HeadX){
				cout << "O";
			}
			else if(i == FruitY && j == FruitX){
				cout << "F";
			}
			else{
				bool printed_tail = false;
				for(int k = 0; k < nTail && !printed_tail; ++k){
					if(i == tailY[k] && j == tailX[k]){
						cout << "o";
						printed_tail = true;
					}
				}
				if(!printed_tail){
					cout << " ";
				}
			}
		}
		cout << '\n';
	}

	for(int i = 0; i < Width + 2; ++i){
		cout << "+";
	}
	cout << '\n';
	cout << "Score: " << score << '\n';
}
// w - up
// a - LEFT
// d - right
// s - down

void Input(){
	if(_kbhit()){
		switch(_getch()){
			case 'a':
				dir = LEFT;
				break;

			case 'd':
				dir = RIGHT;
				break;

			case 'w':
				dir = UP;
				break;

			case 's':
				dir = DOWN;
				break;

			case 'x':
				GameOver = true;
				break;
		}
	}
}

void Logic(){
	int prevX = HeadX, prevY = HeadY;
	switch (dir){
		case LEFT:
			HeadX--;
			break;
		
		case RIGHT:
			HeadX++;
			break;

		case UP:
			HeadY--;
			break;

		case DOWN:
			HeadY++;
			break;
		
		default:
			break;
	}
	// if(HeadY > Height || HeadY < 0 || HeadX > Width || HeadX < 0){
	// 	GameOver = true;
	// }
	
 
	for(int i = 0; i < nTail; ++i){
		if(HeadY == tailY[i] && HeadX == tailX[i]){
			GameOver = true;
		}
	}

	if (HeadX >= Width) HeadX = 0; else if (HeadX < 0) HeadX = Width - 1;
    if (HeadY >= Height) HeadY = 0; else if (HeadY < 0) HeadY = Height - 1;

	if(HeadX == FruitX && HeadY == FruitY){
		score += 10;
		FruitX = rand() % Width;
		FruitY = rand() % Height;
		nTail++;
	}
	for(int i = nTail - 1; i > 0; --i){
		tailX[i] = tailX[i - 1];
		tailY[i] = tailY[i - 1];
	}
	tailX[0] = prevX;
	tailY[0] = prevY;

}

int main(){
	Setup();
	while(!GameOver){
		Draw();
		Input();
		Logic();
		Sleep(10);
	}
	return 0;
}
