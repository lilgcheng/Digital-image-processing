
#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <time.h>
#include <windows.h>
#include "bmp.h"
#include "bmp.cpp"
#define mask 3
#define N mask*mask
#define count 1
using namespace std;
int R[MaxBMPSizeX][MaxBMPSizeY];
int G[MaxBMPSizeX][MaxBMPSizeY];
int B[MaxBMPSizeX][MaxBMPSizeY];
int Sort_arr[N];
int gray[1024][1024];

void img_to_gray(int h, int w);
int Median(int i, int j);
int main(int argc, _TCHAR* argv[])
{
	int width, height;
	double START, END;
	int i, j, c;
	START = clock();
	open_bmp("lena_noise_RGB.bmp", R, G, B, width, height);
	img_to_gray(height, width);


	//printf("\n%d\n", mask / 2);
	for (i = mask / 2; i < width - mask / 2; i++){
		for (j = mask / 2; j < height - mask / 2; j++){
			gray[i][j] = Median(i, j);
		}
	}
	save_bmp("mask3.bmp", gray, gray, gray);
	printf("finish\n");

	close_bmp();
	END = clock();

	//printf("程式執行所花費：%f", (double)clock());
	printf("進行運算所花費的時間：%f S\n", (END - START) / CLOCKS_PER_SEC);
	system("pause");
	return 0;
}

void img_to_gray(int h, int w){
	int i, j;
	//printf("%d %d", h, w);
	for (i = 0; i < w; i++){
		for (j = 0; j < h; j++){
			gray[i][j] = ((int)((0.299*R[i][j] + 0.587*G[i][j] + 0.114*B[i][j]) * 1000) / 1000);
		}
	}
	save_bmp("gray.bmp", gray, gray, gray);
}

int Median(int i,int j){
	int x, y, c=0;
	for (x = 0; x<N; x++){
		Sort_arr[x]=0;
	}
	for (x = i - (mask / 2); x < i - (mask / 2)+mask; x++){
		for (y = j - (mask / 2); y < j - (mask / 2) + mask; y++){
			Sort_arr[c] = gray[x][y];
			c++;
		}
	}
	c = 0;
	/*printf("新儲存值:\n");
	for (x = 0; x < 9; x++){
		printf("%5d", Sort_arr[x]);
	}
	printf("\n");*/
	int temp = 0;
	for (x = 0; x < N; x++){
		for (y = x; y < N ; y++){
			if (Sort_arr[x] > Sort_arr[y]) {
				temp = Sort_arr[y];
				Sort_arr[y] = Sort_arr[x];
				Sort_arr[x] = temp;
			}
		}
	}
	/*printf("排序後:\n");
	for (x = 0; x < 9; x++){
		printf("%5d", Sort_arr[x]);
	}
	printf("\n");*/
	return Sort_arr[N/2];
}
