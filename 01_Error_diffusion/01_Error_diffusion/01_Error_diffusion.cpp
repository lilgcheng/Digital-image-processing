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
		}
	}


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
