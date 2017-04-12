
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <windows.h>
#include "bmp.h"
#include "bmp.cpp"
#define blurRadius  1
#define a 0.5
double weightArr[blurRadius * 2 + 1][blurRadius * 2 + 1] = 
{ 
{-0.5,-0.5,-0.5},
{-0.5, 5.5,-0.5},
{-0.5,-0.5,-0.5}
};
int arr[blurRadius * 2 + 1][blurRadius * 2 + 1] = { 0 };
void  getColorMatrix(int x, int y);
int R[MaxBMPSizeX][MaxBMPSizeY];
int G[MaxBMPSizeX][MaxBMPSizeY];
int B[MaxBMPSizeX][MaxBMPSizeY];
using namespace std;
int gray[1024][1024];
int gray_copy[1024][1024];
int lpf[1024][1024];
int mask[1024][1024];
int edge[1024][1024];
double getBlurValue(int x, int y);
void img_to_gray(int h, int w);
void Produce_Weight_Arr();
int main()
{
	int width, height;
	int i, j,c;
	open_bmp("lena.bmp", R, G, B, width, height);
	Produce_Weight_Arr(); 
	for (int x = 0; x < 3; x++) {
		for (int y = 0; y < 3; y++) {
			printf("%f	",weightArr[x][y]);
		}
		printf("\n");
	}
	img_to_gray(width, height);
	save_bmp("lena_gray.bmp", gray, gray, gray);
	
//	Produce_Weight_Arr();
	for(c=0;c<1;c++){
		for (int x = 1; x < width; x++) {
			for (int y = 1; y < height; y++) {
				lpf[x][y] = (int)getBlurValue(blurRadius + x, blurRadius + y);
	//			printf("%d",lpf[x][y]);
			}
	//		printf("\n");
		}
	}
//	
	save_bmp("lena_LPF1.bmp", lpf, lpf, lpf);
//
		for (int x = 0; x < width; x++) {
			for (int y = 0; y < height; y++) {
				mask[x][y] = (lpf[x][y] - gray[x][y])*0.01;
			}
		}
//	
	save_bmp("lena_mask.bmp", mask, mask, mask);
////	
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			edge[x][y] = gray_copy[x][y] + mask[x][y];
		}
	}
	save_bmp("lena_Edge.bmp", edge, edge, edge);
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
			gray_copy[i][j]=gray[i][j];
		}
	}
} 

//
void Produce_Weight_Arr(){

	for (int i=0; i < blurRadius * 2 + 1; i++){
		for (int j = 0; j < blurRadius * 2 + 1; j++){
			weightArr[i][j] = ( 1/(a+1) ) * weightArr[i][j];
		}
//		printf("\n");
	}
}

double getBlurValue(int x, int y){
	getColorMatrix(x,y);
	double blurGray = 0;
	//double colorMat[blurRadius * 2 + 1][blurRadius * 2 + 1] = getColorMatrix(x, y, whichColor);

	int length = blurRadius * 2 + 1;
	for (int i = 0; i <length; i++){
		for (int j = 0; j < length; j++){
			blurGray +=weightArr[i][j]*arr[i][j];
		}
//		printf("\n");
	}

//	printf("%f\n",blurGray);
	return blurGray;
}

//·í¹³¯À°Ï¶ô 
 void  getColorMatrix(int x, int y){
//	arr[blurRadius * 2 + 1][blurRadius * 2 + 1] = { 0 };
	int startX = x - blurRadius;
	int startY = y - blurRadius;
	int counter = 0;
	int L = blurRadius * 2 + 1;
	
	for (int i = startX; i < startX + L; i++){
		for (int j = startY; j < startY + L; j++){
			arr[counter%L][counter / L] = gray[i][j];
//			printf("[%d][%d] ", counter%L, counter/L);
//			printf("%d", counter);
//			printf("%d", arr[i][j]);
			counter++;
		}
//		printf("\n");
	}	
}
