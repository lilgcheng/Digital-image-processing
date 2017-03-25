// 09_Salt_and_pepper_noise.cpp : 定義主控台應用程式的進入點。
//


#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <time.h>
#include <windows.h>
#include "bmp.h"
#include "bmp.cpp"
#define mask 9
#define count 1
#define n 100000
int R[MaxBMPSizeX][MaxBMPSizeY];
int G[MaxBMPSizeX][MaxBMPSizeY];
int B[MaxBMPSizeX][MaxBMPSizeY];
using namespace std;
int gray[1024][1024];
void saltandpepprt(int w, int h);
void img_to_gray(int h, int w);
int main(int argc, _TCHAR* argv[])
{
	int width, height;
	int i, j, c;
	open_bmp("lena.bmp", R, G, B, width, height);


	saltandpepprt(width, height);
	save_bmp("lena_noise_RGB.bmp", R, G, B);
	//img_to_gray(height, width);
	//save_bmp("lena_noise_Gray.bmp", gray, gray, gray);
	printf("finish\n");

	close_bmp();
	system("pause");
	return 0;
}

void img_to_gray(int h, int w){
	int i, j;
	for (i = 0; i < w; i++){
		for (j = 0; j < h; j++){
			gray[i][j] = ((int)((0.299*R[i][j] + 0.587*G[i][j] + 0.114*B[i][j]) * 1000) / 1000);
		}
	}
}

void saltandpepprt(int w,int h){
	int k;
	for (k = 0; k < n; k++){
		int i = rand() % w;
		int j = rand() % h;
		//printf("%d\n %d\n", i, j);
		if (rand() % 2 == 0){
			R[i][j] = 255;
			G[i][j] = 255;
			B[i][j] = 255;
		}
		else{
			R[i][j] = 0;
			G[i][j] = 0;
			B[i][j] = 0;
		}
	}
}