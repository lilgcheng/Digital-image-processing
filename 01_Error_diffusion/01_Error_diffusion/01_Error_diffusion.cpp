// 01_Error_diffusion.cpp : �w�q�D���x���ε{�����i�J�I�C
//

#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <time.h>
#include "bmp.h"
#include "bmp.cpp"
using namespace std;
int R[MaxBMPSizeX][MaxBMPSizeY];
int G[MaxBMPSizeX][MaxBMPSizeY];
int B[MaxBMPSizeX][MaxBMPSizeY];
int r[1024][1024];
int g[1024][1024];
int b[1024][1024];
int gray[1024][1024];
int output[1024][1024];
void img_to_gray(int w, int h);
int main(int argc, _TCHAR* argv[])
{
	double START, END;
	int width, height;
	int i, j;
	int x, y;
	int err;
	START = clock();
	open_bmp("lena.bmp", R, G, B, width, height);
	//printf("height = %3d , width = %3d\n", height, width);
	img_to_gray(width, height);

	//�X���~�t��k
	for (i = 0; i < width; i++){
		for (j = 0; j < height; j++){
			if (gray[i][j] < 128){
				output[i][j] = 0;
			}
			else{
				output[i][j] = 1;
			}

			err = gray[i][j] - (255 * output[i][j]);

			gray[i][j + 1] += err * 7 / 16;
			gray[i+1][j - 1] += err * 3 / 16;
			gray[i+1][j] += err * 5 / 16;
			gray[i+1][j + 1] += err * 1 / 16;
		}
	}

	//�ഫ�x�}
	for (i = 0; i < width; i++){
		for (j = 0; j < height; j++){
			if (output[i][j] ==1 ){
				output[i][j] = 255;
			}
		}
	}
	save_bmp("new.bmp", output, output, output);
	close_bmp();
	END = clock();

	//printf("�{������Ҫ�O�G%f", (double)clock());
	printf("�i��B��Ҫ�O���ɶ��G%f S\n", (END - START) / CLOCKS_PER_SEC);

	system("pause");
	return 0;
}

void img_to_gray(int w, int h){
	int i, j;
	for (i = 0; i < w; i++){
		for (j = 0; j < h; j++){
			gray[i][j] = ((int)((0.299*R[i][j] + 0.587*G[i][j] + 0.114*B[i][j]) * 1000) / 1000);
		}
	}
}