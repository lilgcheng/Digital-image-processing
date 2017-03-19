
#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <windows.h>
#include "bmp.h"
#include "bmp.cpp"
#define mask 9
#define count 1
using namespace std;
int R[MaxBMPSizeX][MaxBMPSizeY];
int G[MaxBMPSizeX][MaxBMPSizeY];
int B[MaxBMPSizeX][MaxBMPSizeY];
int Sort_arr[mask];
int gray[1024][1024];
int test[3][3] = { { 1, 2, 7 }, { 8, 0, 9 }, { 4, 5, 6 } };
void img_to_gray(int h, int w);
int save(int i, int j);
int main(int argc, _TCHAR* argv[])
{
	int width, height;
	int i, j, c;
	open_bmp("butterfly-noisy.bmp", R, G, B, width, height);
	img_to_gray(height, width);
	for (i = 1; i < width-1; i++){
		for (j = 1; j < height - 1; j++){
			gray[i][j] = save(i,j);
		}
	}
	save_bmp("lrrrr.bmp", gray, gray, gray);
	printf("finish\n");

	close_bmp();
	system("pause");
	return 0;
}

void img_to_gray(int h, int w){
	int i, j;
	printf("%d %d", h, w);
	for (i = 0; i < w; i++){
		for (j = 0; j < h; j++){
			gray[i][j] = ((int)((0.299*R[i][j] + 0.587*G[i][j] + 0.114*B[i][j]) * 1000) / 1000);
		}
	}
	save_bmp("gray.bmp", gray, gray, gray);
}

int save(int i,int j){
	int x, y, c=0;
	for(x=0;x<9;x++){
		Sort_arr[x]=0;
	}
	for (x =i-1 ; x < i-1+3; x++){
		for (y = j-1; y < j-1+3; y++){
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
	for (x = 0; x < 9; x++){
		for (y = x; y < 9 ; y++){
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
	return Sort_arr[4];
}
