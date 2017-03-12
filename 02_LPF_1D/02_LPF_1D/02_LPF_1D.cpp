

#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <windows.h>
#include "bmp.h"
#include "bmp.cpp"
#define mask 7
#define size 3
using namespace std;
int R[MaxBMPSizeX][MaxBMPSizeY];
int G[MaxBMPSizeX][MaxBMPSizeY];
int B[MaxBMPSizeX][MaxBMPSizeY];
int r[1024][1024];
int g[1024][1024];
int b[1024][1024];
int gray[1024][1024];
int main(int argc, _TCHAR* argv[])
{
	int width, height;
	int i, j;
	int x,y,c;
	open_bmp("lena.bmp", R, G, B, width, height);

	for (i = 0; i < width; i++){
		for (j = 0; j < height; j++){
			gray[i][j] = ((int)((0.299*R[i][j] + 0.587*G[i][j] + 0.114*B[i][j]) * 1000) / 1000);
		}
	}
//	save_bmp("butterfly-noisy_gray.bmp", gray, gray, gray);


/*error x,y corrid*/ 
//	
//	for (x = 0; x < width; x++){
//		for (y = 3; y < height-3; y++){
//			gray[x][y] = (gray[x][y-1] / mask) + (gray[x][y] / mask) + (gray[x][y+1] / mask);
//		}
//	}	
	for (y = 3; y < width-3; y++){
		for (x = 0; x < height; x++){
			gray[y][x] = (gray[y-1][x] / mask) + (gray[y][x] / mask) + (gray[y+1][x] / mask);
		}
	}	
	

	save_bmp("lena_LPF_1D_1.bmp", gray, gray, gray);
	
//	for(c=0;c<5;c++){
//		for (y = 2; y < width-2; y++){
//			for (x = 0; x < height; x++){
//				gray[y][x] = (gray[y-1][x] / mask) + (gray[y][x] / mask) + (gray[y+1][x] / mask);
//			}
//		}	
//	}
//	save_bmp("butterfly-noisy_LPF_1D_10.bmp", gray, gray, gray);
	printf("finish\n");

	close_bmp();
	return 0;
}

