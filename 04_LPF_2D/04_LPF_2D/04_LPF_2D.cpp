// 04_LPF_2D.cpp : 定義主控台應用程式的進入點。
//

#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <windows.h>
#include "bmp.h"
#include "bmp.cpp"
#define mask 9
#define count 1
int R[MaxBMPSizeX][MaxBMPSizeY];
int G[MaxBMPSizeX][MaxBMPSizeY];
int B[MaxBMPSizeX][MaxBMPSizeY];
using namespace std;
int gray[1024][1024];
void img_to_gray(int h, int w);
int main(int argc, _TCHAR* argv[])
{
	int width, height;
	int i, j,c;
	open_bmp("lena.bmp", R, G, B, width, height);
	img_to_gray(width, height);
	for (c = 0; c < count; c++){
		for (i = 1; i < height - 1; i++){
			for (j = 1; j < width - 1; j++){
				gray[i][j] = 
					  (gray[i - 1][j - 1] / mask) + (gray[i][j - 1] / mask) + (gray[i + 1][j - 1] / mask)
					+ (gray[i - 1][j + 0] / mask) + (gray[i][j + 0] / mask) + (gray[i + 1][j + 0] / mask)
					+ (gray[i - 1][j + 1] / mask) + (gray[i][j + 1] / mask) + (gray[i + 1][j + 1] / mask);
			}
		}
	}
	
	save_bmp("lena_LPF.bmp", gray, gray, gray);
	printf("finish\n");

	close_bmp();
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