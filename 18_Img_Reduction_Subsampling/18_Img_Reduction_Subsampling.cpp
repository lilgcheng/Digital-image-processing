#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <time.h>
#include "bmp.h"
#include "bmp.cpp"
#define blurRadius  1
double weightArr[blurRadius * 2 + 1][blurRadius * 2 + 1] = { 1};
double arr[blurRadius * 2 + 1][blurRadius * 2 + 1] = { 0 };
double getBlurColor(int x, int y);
void  getColorMatrix(int x, int y);
using namespace std;
int original[MaxBMPSizeX][MaxBMPSizeY]; // MaxBMPSizeX and MaxBMPSizeY are defined in "bmp.h"
int histogram_equalization[MaxBMPSizeX][MaxBMPSizeY]; // MaxBMPSizeX and MaxBMPSizeY are defined in "bmp.h"
int R[MaxBMPSizeX][MaxBMPSizeY];
int G[MaxBMPSizeX][MaxBMPSizeY];
int B[MaxBMPSizeX][MaxBMPSizeY];
int r[1024][1024];
int g[1024][1024];
int b[1024][1024];

int gray[1024][1024];
int gray_lpf[1024][1024];
int lpf[1024][1024];
int small[1024][1024];

void img_to_gray(int h, int w);
void Produce_Weight_Arr();
int main()
{
	double START, END;
	int width, height;
	int i=0, j=0;
	int x, y;
	
	int a1,a2,a3,a4;
	int d = 0.5;//水平距離
	int b1,b2,b3,b4; 
	START = clock();
	open_bmp("lena.bmp", R, G, B, width, height); // for gray images
	img_to_gray(width,height); 
	save_bmp("lena_gray.bmp", gray, gray, gray);
	Produce_Weight_Arr();
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			gray_lpf[x][y] = (int)getBlurColor(blurRadius + x, blurRadius + y);
		}
	}
	//原點訂於圖片正中央，將外圍反白 
	for(x=0;x<width;x+=2){
		for(y=0;y<height;y+=2){
			small[i][j] = gray_lpf[x][y];
			j++;
		}
		i++;
		j=0;
	}
	save_bmp("lena_small_add_lpf.bmp", small, small, small);
	close_bmp();
	END = clock();
	printf("進行運算所花費的時間：%f S\n", (END - START) / CLOCKS_PER_SEC);
	system("pause");
	return 0;
}

void img_to_gray(int w, int h){
	int i, j;
	for (i = 0; i < w; i++){
		for (j = 0; j < h; j++){
			gray[i][j] = ((int)((0.299*R[i][j] + 0.587*G[i][j] + 0.114*B[i][j]) * 1000) / 1000);
//			gray_copy[i][j] = gray[i][j];
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
