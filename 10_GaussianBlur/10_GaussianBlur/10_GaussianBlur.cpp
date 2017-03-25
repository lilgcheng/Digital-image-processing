// 10_GaussianBlur.cpp : 定義主控台應用程式的進入點。
//

// 04_LPF_2D.cpp : ﹚竡北莱ノ祘Α秈翴
//

#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <windows.h>
#include <math.h>
#include "bmp.h"
#include "bmp.cpp"
#define Q 1
#define M_PI 3.14159265358979323846

int blurRadius = 1;
int length = blurRadius * 2 + 1;
double weightArr[3][3] = { 0 };
double sum=0;

int R[MaxBMPSizeX][MaxBMPSizeY];
int G[MaxBMPSizeX][MaxBMPSizeY];
int B[MaxBMPSizeX][MaxBMPSizeY];
int gray[1024][1024];
using namespace std;
void img_to_gray(int h, int w);
double Getweight(int x, int y);
void Printf_WeightArr();
void Add_Arr();
void Final_weight();
int main(int argc, _TCHAR* argv[])
{
	int width, height;
	int i, j, c;
	open_bmp("lena.bmp", R, G, B, width, height);
	img_to_gray(width, height);
	save_bmp("lena_gray.bmp", gray, gray, gray);
	//最初權重
	for (i = 0; i<length; i++){
		for (j = 0; j<length; j++){
			weightArr[i][j] = Getweight(j - blurRadius, blurRadius - i);
			printf("(%3d,%3d)  ",j-blurRadius,blurRadius-i);
		}
		printf("\n");
	}
	Printf_WeightArr();
	Add_Arr();

	Final_weight();
	Printf_WeightArr();

	for (i = 0; i < height; i++){
		for (j = 0; j < width; j++){
			gray[i][j] = 
   				  (gray[i - 1][j - 1] * weightArr[(i-1)%3][(j-1)%3]) + (gray[i][j - 1] * weightArr[i%3][(j-1)%3]) + (gray[i + 1][j - 1] * weightArr[(i+1)%3][(j-1)%3])
				+ (gray[i - 1][j + 0] * weightArr[(i-1)%3][(j+0)%3]) + (gray[i][j + 0] * weightArr[i%3][(j+0)%3]) + (gray[i + 1][j + 0] * weightArr[(i+1)%3][(j+0)%3])
				+ (gray[i - 1][j + 1] * weightArr[(i-1)%3][(j+1)%3]) + (gray[i][j + 1] * weightArr[i%3][(j+1)%3]) + (gray[i + 1][j + 1] * weightArr[(i+1)%3][(j+1)%3]);
			//printf("%d\n", gray[i][j]);
		}
	}
	save_bmp("lena_Gassian_Blur.bmp", gray, gray, gray);
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

//得到權重傳回 
double Getweight(int x, int y){
	double sigma = 1.5;
	double weight = (1 / (2 * M_PI*sigma*sigma))*exp(((-(x*x + y*y)) / ((2 * sigma)*(sigma))));
	return weight;
}

void Printf_WeightArr(){
	int i, j;
	for (i = 0; i < length; i++){
		for (j = 0; j < length; j++){
			printf("%3f\t", weightArr[i][j]);
		}
		printf("\n");
	}
}

//因為權重值總合不為1，所以先相加
void Add_Arr(){
	int i, j;
	for (i = 0; i < length; i++){
		for (j = 0; j < length; j++){
			sum += weightArr[i][j];
		}
	}
	//printf("%f\n", sum);
}

//使權重總合為1
void Final_weight(){
	int i, j;
	for (i = 0; i < length; i++){
		for (j = 0; j < length; j++){
			weightArr[i][j] = weightArr[i][j]/sum;
		}
	}
}