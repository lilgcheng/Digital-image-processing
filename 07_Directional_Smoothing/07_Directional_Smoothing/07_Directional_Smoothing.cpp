// 07_Directional_Smoothing.cpp : 定義主控台應用程式的進入點。
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
int gray_copy[1024][1024];
int dir[1024][1024];
int anagle[4];
void img_to_gray(int h, int w);
int main(int argc, _TCHAR* argv[])
{
	int width, height;
	int i, j, c,k;
	int y[4];
	int a[4];
	int g;
	open_bmp("lena.bmp", R, G, B, width, height);
	img_to_gray(width, height);
	save_bmp("lena_gray.bmp", gray, gray, gray);
	for (i = 1; i < height - 1; i++){
		for (j = 1; j < width - 1; j++){
			y[0] = (gray[i+1][j  ] + gray[i][j] + gray[i-1][j  ]) / 3;
			y[1] = (gray[i][j+1] + gray[i][j] + gray[i][j-1]) / 3;
			y[2] = (gray[i-1][j-1] + gray[i][j] + gray[i+1][j+1  ]) / 3;
			y[3] = (gray[i - 1][j + 1] + gray[i][j] + gray[i + 1][j - 1]) / 3;
			for (c = 0; c < 4; c++){
				a[c] = abs(gray[i][j] - y[c]);
			}
			g=0;
			for (k = 1; k < 4; k++){
				if (a[k]<=a[0]){
					a[0] = a[k];
					g++;
				}
			}
//			printf("%d\n",g);
			gray[i][j] = y[g];
			
		}
	}
	

	save_bmp("lena_DIR.bmp", gray, gray, gray);
	
	for(i=0;i<height;i++){
		for(j=0;j<width;j++){
			dir[i][j] = gray_copy[i][j] - gray[i][j];
		}
	}
	save_bmp("lena_OG-DIR.bmp", dir, dir, dir);
	
	printf("finish\n");

	close_bmp();
	return 0;
}

void img_to_gray(int h, int w){
	int i, j;
	for (i = 0; i < w; i++){
		for (j = 0; j < h; j++){
			gray[i][j] = ((int)((0.299*R[i][j] + 0.587*G[i][j] + 0.114*B[i][j]) * 1000) / 1000);
			gray_copy[i][j] = gray[i][j];
		}
	}
}
