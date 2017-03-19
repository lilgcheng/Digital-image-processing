
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
	int i, j, c;
	open_bmp("lena.bmp", R, G, B, width, height);
	for ( i = 1; i < width-1; i++)
	{
		for (j = 1; j < height-1; j++){
			R[i][j] = 
			      (R[i - 1][j - 1] / mask) + (R[i][j - 1] / mask) + (R[i + 1][j - 1] / mask)
				+ (R[i - 1][j + 0] / mask) + (R[i][j + 0] / mask) + (R[i + 1][j + 0] / mask)
				+ (R[i - 1][j + 1] / mask) + (R[i][j + 1] / mask) + (R[i + 1][j + 1] / mask);
		}
		
	}
	for (i = 1; i < width - 1; i++)
	{
		for (j = 1; j < height - 1; j++){
			G[i][j] =
			      (G[i - 1][j - 1] / mask) + (G[i][j - 1] / mask) + (G[i + 1][j - 1] / mask)
				+ (G[i - 1][j + 0] / mask) + (G[i][j + 0] / mask) + (G[i + 1][j + 0] / mask)
				+ (G[i - 1][j + 1] / mask) + (G[i][j + 1] / mask) + (G[i + 1][j + 1] / mask);
		}

	}
	for (i = 1; i < width - 1; i++)
	{
		for (j = 1; j < height - 1; j++){
			B[i][j] =
				(B[i - 1][j - 1] / mask) + (B[i][j - 1] / mask) + (B[i + 1][j - 1] / mask)
				+ (B[i - 1][j + 0] / mask) + (B[i][j + 0] / mask) + (B[i + 1][j + 0] / mask)
				+ (B[i - 1][j + 1] / mask) + (B[i][j + 1] / mask) + (B[i + 1][j + 1] / mask);
		}

	}
	/*img_to_gray(width, height);
	for (c = 0; c < count; c++){
		for (i = 1; i < height - 1; i++){
			for (j = 1; j < width - 1; j++){
				gray[i][j] =
					(gray[i - 1][j - 1] / mask) + (gray[i][j - 1] / mask) + (gray[i + 1][j - 1] / mask)
					+ (gray[i - 1][j + 0] / mask) + (gray[i][j + 0] / mask) + (gray[i + 1][j + 0] / mask)
					+ (gray[i - 1][j + 1] / mask) + (gray[i][j + 1] / mask) + (gray[i + 1][j + 1] / mask);
			}
		}
	}*/

	save_bmp("lena_LPF_RGB.bmp", R, G, B);
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