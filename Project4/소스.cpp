#include <stdio.h>
#include <iostream>
#include <time.h>
#include <stdlib.h>
using namespace std;

int map_size, boom_number, map[20][20], blink[20][20], i, j, k;

int random(int a) { return rand() % (a); }

void draw_view() {
	int i, j;

	cout << endl;

	cout << "     ";
	for (i = 0; i < map_size; i++) {
		if (i + 1 < 10)cout << " ";
		cout << i + 1;
	}
	cout << endl;

	for (i = 0; i < map_size; i++) {
		cout << endl;
		if (i + 1 < 10)cout << " ";
		cout << i + 1 << "   ";
		for (j = 0; j < map_size; j++) {
			if (blink[i][j]) {
				if (map[i][j] == 0)cout << "  ";
				else
				{
					if (map[i][j] != -1)cout << " " << map[i][j];
					else cout << "♥";
				}
			}
			else cout << "♡";

		}
	}
	cout << endl;
	cout << endl;
}

int main()
{
	int commend, boom = 0, i, j, k;

start:
	srand((unsigned)time(NULL));

	for (i = 0; i < 20; i++)for (j = 0; j < 20; j++) {
		map[i][j] = -2;
		blink[i][j] = 0;
	}

	cout << "               :: Mine Sweeper :: ver 1.0" << endl << endl;

	cout << "난이도를 선택하세요. ( 0 - 끝내기 / 1 - 쉬움 / 2 - 중간 / 3 - 어려움 ) : ";
	cin >> commend;

	switch (commend)
	{
	case 0:
		goto exit;
	case 1:
		map_size = 10;
		boom_number = 10;
		break;
	case 2:
		map_size = 15;
		boom_number = 45;
		break;
	case 3:
		map_size = 20;
		boom_number = 80;
		break;
	}

	for (i = 0; i < map_size; i++)for (j = 0; j < map_size; j++)map[i][j] = 0;
	for (k = 0; k < boom_number; k++) {
		int a, b;
		a = random(map_size);
		b = random(map_size);
		while (map[a][b] == -1) {
			a = random(map_size);
			b = random(map_size);
		}
		map[a][b] = -1;
	}

	for (i = 0; i < map_size; i++) {
		for (j = 0; j < map_size; j++) {
			if (map[i][j] != -1)
			{
				int boom_num = 0;
				if (i > 0) {
					if (map[i - 1][j] == -1)boom_num++;
					if (j > 0)if (map[i - 1][j - 1] == -1)boom_num++;
					if (j < map_size)if (map[i - 1][j + 1] == -1)boom_num++;
				}
				if (i < map_size) {
					if (map[i + 1][j] == -1)boom_num++;
					if (j > 0)if (map[i + 1][j - 1] == -1)boom_num++;
					if (j < map_size)if (map[i + 1][j + 1] == -1)boom_num++;
				}
				if (j > 0)if (map[i][j - 1] == -1)boom_num++;
				if (j < map_size)if (map[i][j + 1] == -1)boom_num++;

				map[i][j] = boom_num;
			}
		}
	}

draw:
	system("cls");
	draw_view();
	goto step;

step:
	cout << "Select coordinates ( x, y )(x좌표 누르고 스페이스바 누르고 y좌표 누르세요) : ";
	cin >> j >> i;
	i--;
	j--;
	if (map[i][j] == -1) {
		system("cls");
		for (i = 0; i < map_size; i++)for (j = 0; j < map_size; j++)if (map[i][j] == -1)blink[i][j] = 1;
		draw_view();
		cout << "                     !!Boom!!" << endl;
		goto start;
	}
	blink[i][j] = 1;

	boom = 0;

	if (map[i][j] == 0)
	{
		for (k = 0; k < 10; k++)
		{
			for (i = 0; i < map_size; i++) {
				for (j = 0; j < map_size; j++) {
					if (blink[i][j] == 1 && map[i][j] == 0)
					{
						if (i > 0) {
							blink[i - 1][j] = 1;
							if (j > 0)blink[i - 1][j - 1] = 1;;
							if (j < map_size)blink[i - 1][j + 1] = 1;
						}
						if (i < map_size) {
							blink[i + 1][j] = 1;
							if (j > 0)blink[i + 1][j - 1] = 1;
							if (j < map_size)blink[i + 1][j + 1] = 1;
						}
						if (j > 0)blink[i][j - 1] = 1;
						if (j < map_size)blink[i][j + 1] = 1;
					}
				}
			}
		}
	}

	for (i = 0; i < map_size; i++)for (j = 0; j < map_size; j++)if (blink[i][j] == 0)boom++;
	if (boom == boom_number)goto win;

	goto draw;

win:
	for (i = 0; i < map_size; i++)for (j = 0; j < map_size; j++)blink[i][j] = 1;
	system("cls");
	draw_view();
	cout << "                     !! 축하합니다 !!" << endl;
	goto start;

exit:
	return 0;
}