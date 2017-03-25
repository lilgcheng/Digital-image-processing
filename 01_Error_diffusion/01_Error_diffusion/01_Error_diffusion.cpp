// 01_Error_diffusion.cpp : 定義主控台應用程式的進入點。
//

#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
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
int half[1024][1024];
int D1[2][2] = { { 0, 128 }, { 192, 64 } };
int D2[4][4] = { { 0, 128, 32, 160 }, { 192, 64, 224, 96 }, { 48, 176, 16, 144 }, { 240, 112, 208, 80 } };
int D3[8][8] = { { 0, 32, 8, 40, 2, 34, 10, 42 }, { 48, 16, 56, 24, 50, 18, 58, 26 }, { 12, 14, 4, 36, 14, 46, 6, 38 }, { 60, 28, 52, 20, 62, 30, 54, 22 },
{ 3, 35, 11, 43, 1, 33, 9, 41 }, { 51, 19, 59, 27, 49, 17, 57, 25 }, { 15, 47, 7, 39, 13, 45, 5, 37 }, { 63, 31, 55, 23, 61, 29, 53, 21 } };
int main(int argc, _TCHAR* argv[])
{
	int width, height;
	int i, j;
	int x, y;
	int Diffuse;
	open_bmp("lena.bmp", R, G, B, width, height);
	printf("height = %3d , width = %3d\n", height, width);
	for (i = 0; i < width; i++){
		for (j = 0; j < height; j++){
			gray[i][j] = ((int)((0.299*R[i][j] + 0.587*G[i][j] + 0.114*B[i][j]) * 1000) / 1000);
			half[i][j] = gray[i][j];
		}
	}
	save_bmp("gray_lena.bmp", gray, gray, gray);
	for (i = 0; i < width; i++){
		for (j = 0; j < height; j++){
			if (half[i][j]>D3[i % 8][j % 8]){
				half[i][j] = 255;
			}
			else{
				half[i][j] = 0;
			}
		}
	}
	save_bmp("half_lena.bmp", half, half, half);
	for (i = 0; i < width; i++){
		for (j = 0; j < height; j++){
			if (i == width-1){
				if (gray[i][j] < 128){
					Diffuse = gray[i][j];//需要擴散值 
					gray[i][j] = 0;
					gray[i][j + 1] = gray[i][j + 1] + Diffuse * 7 / 16;
					//					gray[i+1][j-1] = gray[i+1][j-1] + Diffuse*1/16;
					//					gray[i+1][j] = gray[i+1][j] +  Diffuse*5/16;
					//					gray[i+1][j+1] = gray[i+1][j+1] + Diffuse*3/16;

				}
				else{
					Diffuse = gray[i][j] - 255;//需要擴散值 
					gray[i][j] = 1;
					gray[i][j + 1] = gray[i][j + 1] + (Diffuse * 7 / 16);
					//					gray[i+1][j-1] = gray[i+1][j-1] + (Diffuse*1/16);
					//					gray[i+1][j] = gray[i+1][j] +  (Diffuse*5/16);
					//					gray[i+1][j+1] = gray[i+1][j+1] + (Diffuse*3/16);	
				}
				//				printf("[%d][%d]=%d   ",i,j,gray[i][j]);
			}
			else{
				if (gray[i][j] < 128){
					Diffuse = gray[i][j];//需要擴散值 
					gray[i][j] = 0;
					gray[i][j + 1] = gray[i][j + 1] + Diffuse * 7 / 16;
					gray[i + 1][j + 1] = gray[i + 1][j + 1] + Diffuse * 1 / 16;
					gray[i + 1][j] = gray[i + 1][j] + Diffuse * 5 / 16;
					gray[i + 1][j - 1] = gray[i + 1][j - 1] + Diffuse * 3 / 16;
					/*for (x = 0; x<5; x++){
						for (y = 0; y<5; y++){
						if (gray[x][y] == 1){
						gray[x][y] = 255;
						}
						printf("%5d   ", gray[x][y]);
						}
						printf("\n");
						}*/
				}
				else{
					Diffuse = gray[i][j] - 255;//需要擴散值 
					gray[i][j] = 1;
					gray[i][j + 1] = gray[i][j + 1] + Diffuse * 7 / 16;
					gray[i + 1][j + 1] = gray[i + 1][j + 1] + Diffuse * 1 / 16;
					gray[i + 1][j] = gray[i + 1][j] + Diffuse * 5 / 16;
					gray[i + 1][j - 1] = gray[i + 1][j - 1] + Diffuse * 3 / 16;
					/*for (x = 0; x<5; x++){
						for (y = 0; y<5; y++){
						if (gray[x][y] == 1){
						gray[x][y] = 255;
						}
						printf("%5d   ", gray[x][y]);
						}
						printf("\n");
						}
						}
						printf("\n");*/
					//				printf("[%d][%d]=%d   ",i,j,gray[i][j]);
				}

			}
			//printf("\n");
		}


	}

	for (x = 0; x<width; x++){
		for (y = 0; y<height; y++){
			if (gray[x][y] == 1){
				gray[x][y] = 255;
			}
			//printf("%5d   ", gray[x][y]);
		}
		//printf("\n");
	}
	save_bmp("new.bmp", gray, gray, gray);
	close_bmp();
	system("pause");
	return 0;
}
