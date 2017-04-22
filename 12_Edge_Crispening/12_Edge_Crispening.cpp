// 04_LPF_2D.cpp : 定義主控台應用程式的進入點。
//


#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <windows.h>
#include "bmp.h"
#include "bmp.cpp"
#define blurRadius  1
double weightArr[blurRadius * 2 + 1][blurRadius * 2 + 1] = { 1};
double arr[blurRadius * 2 + 1][blurRadius * 2 + 1] = { 0 };
double getBlurColor(int x, int y);
void  getColorMatrix(int x, int y);
int R[MaxBMPSizeX][MaxBMPSizeY];
int G[MaxBMPSizeX][MaxBMPSizeY];
int B[MaxBMPSizeX][MaxBMPSizeY];

int r[blurRadius * 2 + 1][blurRadius * 2 + 1] = { 0 };
int g[blurRadius * 2 + 1][blurRadius * 2 + 1] = { 0 };
int b[blurRadius * 2 + 1][blurRadius * 2 + 1] = { 0 };

int LPF_R[MaxBMPSizeX][MaxBMPSizeY];
int LPF_G[MaxBMPSizeX][MaxBMPSizeY];
int LPF_B[MaxBMPSizeX][MaxBMPSizeY];
int HPF_R[MaxBMPSizeX][MaxBMPSizeY];
int HPF_G[MaxBMPSizeX][MaxBMPSizeY];
int HPF_B[MaxBMPSizeX][MaxBMPSizeY];
int FINAL_R[MaxBMPSizeX][MaxBMPSizeY];
int FINAL_G[MaxBMPSizeX][MaxBMPSizeY];
int FINAL_B[MaxBMPSizeX][MaxBMPSizeY];
using namespace std;
int gray[1024][1024];
int lpf[1024][1024];
int hpf[1024][1024];
int final[1024][1024];
void img_to_gray(int h, int w);
void Produce_Weight_Arr();
double getR(int x, int y);
double getG(int x, int y);
double getB(int x, int y);
int main()
{
	int width, height;
	int i, j,c;
	open_bmp("lena.bmp", R, G, B, width, height);
	img_to_gray(width, height);
//	save_bmp("lena_GRAy_3X3.bmp", gray, gray, gray);
	Produce_Weight_Arr();
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
//			lpf[x][y] = (int)getBlurColor(blurRadius + x, blurRadius + y);
			LPF_R[x][y] = (int)getR(blurRadius + x, blurRadius + y);
			LPF_G[x][y] = (int)getG(blurRadius + x, blurRadius + y);
			LPF_B[x][y] = (int)getB(blurRadius + x, blurRadius + y);
		}
	}
	save_bmp("lena_LPF_3X3.bmp", LPF_R, LPF_G, LPF_B);
	
//	int A=0.6;
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
//			hpf[x][y] = 0.2*(gray[x][y] - lpf[x][y]);
			HPF_R[x][y] = (R[x][y] - LPF_R[x][y]);
			HPF_G[x][y] = (G[x][y] - LPF_G[x][y]);
			HPF_B[x][y] = (B[x][y] - LPF_B[x][y]);
		}
	}
	save_bmp("lena_HPF_3X3.bmp", HPF_R, HPF_G, HPF_B);
//	
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
//			final[x][y] = gray[x][y] + hpf[x][y];
			FINAL_R[x][y] = (R[x][y] + HPF_R[x][y]); 
			FINAL_G[x][y] = (G[x][y] + HPF_G[x][y]);
			FINAL_B[x][y] = (B[x][y] + HPF_B[x][y]);
			if(FINAL_R[x][y] > 255 ){
				FINAL_R[x][y]=255;
			}
			if(FINAL_G[x][y] > 255 ){
				FINAL_G[x][y]=255;
			}
			if(FINAL_B[x][y] > 255 ){
				FINAL_B[x][y]=255;
			}
			if(FINAL_R[x][y] < 0 ){
				FINAL_R[x][y]=0;
			}
			if(FINAL_G[x][y] < 0 ){
				FINAL_G[x][y]=0;
			}
			if(FINAL_B[x][y] < 0 ){
				FINAL_B[x][y]=0;
			}
		}
	}
	save_bmp("lena_final_3X3.bmp", FINAL_R, FINAL_G, FINAL_B);
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
	double blur_R = 0;
	double blur_G = 0;
	double blur_B = 0;
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
//			arr[counter%L][counter / L] = gray[i][j];
			r[counter%L][counter / L] = R[i][j];
			g[counter%L][counter / L] = G[i][j];
			b[counter%L][counter / L] = B[i][j];
			//printf("[%d] [%d]", counter%L, counter/L);
			//printf("%d", counter);
			//printf("%f", (double)arr[i][j]);
			counter++;
		}
	
		//printf("\n");
	}	
}

double getR(int x, int y){
	getColorMatrix(x,y);
	double blur_R = 0;
	int length = blurRadius * 2 + 1;
	for (int i = 0; i <length; i++){
		for (int j = 0; j < length; j++){
			blur_R += (double)(1 / (double)(length*length))* r[i][j];
		}
	}
	return blur_R;
}

double getG(int x, int y){
	getColorMatrix(x,y);
	double blur_G = 0;
	int length = blurRadius * 2 + 1;
	for (int i = 0; i <length; i++){
		for (int j = 0; j < length; j++){
			blur_G += (double)(1 / (double)(length*length))* g[i][j];
		}
	}
	return blur_G;
}

double getB(int x, int y){
	getColorMatrix(x,y);
	double blur_B = 0;
	int length = blurRadius * 2 + 1;
	for (int i = 0; i <length; i++){
		for (int j = 0; j < length; j++){
			blur_B += (double)(1 / (double)(length*length))* b[i][j];
		}
	}
	return blur_B;
}
