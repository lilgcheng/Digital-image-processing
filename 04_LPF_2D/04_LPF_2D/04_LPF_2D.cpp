// 04_LPF_2D.cpp : 定義主控台應用程式的進入點。
//

#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <windows.h>
#include "bmp.h"
#include "bmp.cpp"
//#define mask 9
//#define count 1
#define blurRadius  1
double weightArr[blurRadius * 2 + 1][blurRadius * 2 + 1] = { 1};
double arr[blurRadius * 2 + 1][blurRadius * 2 + 1] = { 0 };
double getBlurColor(int x, int y);
void  getColorMatrix(int x, int y);
int R[MaxBMPSizeX][MaxBMPSizeY];
int G[MaxBMPSizeX][MaxBMPSizeY];
int B[MaxBMPSizeX][MaxBMPSizeY];
using namespace std;
int gray[1024][1024];
void img_to_gray(int h, int w);
void Produce_Weight_Arr();
int main(int argc, _TCHAR* argv[])
{
	int width, height;
	int i, j,c;
	open_bmp("lena-noise.bmp", R, G, B, width, height);
	img_to_gray(width, height);
	Produce_Weight_Arr();
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			gray[x][y] = (int)getBlurColor(blurRadius + x, blurRadius + y);
			
		}
	}

	//printf("%f", (double)1 / (double)9));
	/*for ( i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++){
			printf("%f", weightArr[i][j]);
		}
		printf("\n");
	}*/
	/*for (c = 0; c < count; c++){
		for (i = 1; i < height - 1; i++){
			for (j = 1; j < width - 1; j++){
				gray[i][j] = 
					  (gray[i - 1][j - 1] / mask) + (gray[i][j - 1] / mask) + (gray[i + 1][j - 1] / mask)
					+ (gray[i - 1][j + 0] / mask) + (gray[i][j + 0] / mask) + (gray[i + 1][j + 0] / mask)
					+ (gray[i - 1][j + 1] / mask) + (gray[i][j + 1] / mask) + (gray[i + 1][j + 1] / mask);
			}
		}
	}*/
	
	save_bmp("lena_LPF_3X3.bmp", gray, gray, gray);
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

void Produce_Weight_Arr(){
	double weightArr[blurRadius * 2 + 1][blurRadius * 2 + 1];
	for (int i=0; i < blurRadius * 2 + 1; i++){
		for (int j = 0; j < blurRadius * 2 + 1; j++){
			weightArr[i][j] = (double)1 / (double)(((blurRadius * 2) + 1)*((blurRadius * 2) + 1));
			//printf("%3f", (double)weightArr[i][j]);
		}
		//printf("\n");
	}
}

double getBlurColor(int x, int y){
	getColorMatrix(x,y);
	double blurGray = 0;
	//double colorMat[blurRadius * 2 + 1][blurRadius * 2 + 1] = getColorMatrix(x, y, whichColor);

	int length = blurRadius * 2 + 1;
	for (int i = 0; i <length; i++){
		for (int j = 0; j < length; j++){
			blurGray += (double)(1 / (double)(length*length))* arr[i][j];
		}
	}

	return blurGray;
}

 void  getColorMatrix(int x, int y){
	arr[blurRadius * 2 + 1][blurRadius * 2 + 1] = { 0 };
	int startX = x - blurRadius;
	int startY = y - blurRadius;
	int counter = 0;
	int L = blurRadius * 2 + 1;
	
	for (int i = startX; i < startX + L; i++){
		for (int j = startY; j < startY + L; j++){
			arr[counter%L][counter / L] = gray[i][j];
			//printf("[%d] [%d]", counter%L, counter/L);
			//printf("%d", counter);
			//printf("%f", (double)arr[i][j]);
			counter++;
		}
	
		//printf("\n");
	}	
}
