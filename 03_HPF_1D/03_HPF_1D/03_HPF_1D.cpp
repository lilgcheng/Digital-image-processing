// 03_HPF_1D.cpp : 定義主控台應用程式的進入點。
//

#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <windows.h>
#include "bmp.h"
#include "bmp.cpp"
#define mask 3
#define size 3
using namespace std;
int R[MaxBMPSizeX][MaxBMPSizeY];
int G[MaxBMPSizeX][MaxBMPSizeY];
int B[MaxBMPSizeX][MaxBMPSizeY];
int r[1024][1024];
int g[1024][1024];
int b[1024][1024];
int gray[1024][1024];
int gray_LPF[1024][1024];
int gray_HPF[1024][1024];
int main(int argc, _TCHAR* argv[])
{
	int width, height;
	int i, j;
	open_bmp("lena.bmp", R, G, B, width, height);

	for (i = 0; i < width; i++){
		for (j = 0; j < height; j++){
			gray[i][j] = ((int)((0.299*R[i][j] + 0.587*G[i][j] + 0.114*B[i][j]) * 1000) / 1000);
		}
	}
	
	//save_bmp("lena_gray.bmp", gray, gray, gray);
	int x, y, c;
	for (y = 1; y < width - 1; y++){
		for (x = 0; x < height; x++){
			gray_LPF[y][x] = (gray[y - 1][x] / mask) + (gray[y][x] / mask) + (gray[y + 1][x] / mask);
		}
	}
	save_bmp("lena_LPF_1D.bmp", gray_LPF, gray_LPF, gray_LPF);
	printf("finish\n");
	for (y = 1; y < width - 1; y++){
		for (x = 0; x < height; x++){
			gray_HPF[y][x] = abs(gray[y][x] - (gray[y - 1][x] / mask) + (gray[y][x] / mask) + (gray[y + 1][x] / mask));
		}
	}
	save_bmp("lena_HPF_1D.bmp", gray_HPF, gray_HPF, gray_HPF);
	close_bmp();
	return 0;
}

