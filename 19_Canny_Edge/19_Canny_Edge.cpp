
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <windows.h>
#include <math.h>
#include "bmp.h"
#include "bmp.cpp"
#define Q 1
#define PI 3.14159265

int blurRadius = 1;
int length = blurRadius * 2 + 1;
double weightArr[3][3] = { 0 };
double sum=0;

int R[MaxBMPSizeX][MaxBMPSizeY];
int G[MaxBMPSizeX][MaxBMPSizeY];
int B[MaxBMPSizeX][MaxBMPSizeY];
int gray[1024][1024];
int GASSIAN[1024][1024];
float GX[1024][1024];
float GY[1024][1024];
int GG[1024][1024];
float angle[1024*1024];
int degree[1024*1024];
using namespace std;
void img_to_gray(int h, int w);
double Getweight(int x, int y);
void Printf_WeightArr();
void Add_Arr();
void Final_weight();
int main()
{
	int width, height;
	int i, j, c;
	int count=0;
//	printf("%f\n",atan (135/45) * 180 / PI);
	open_bmp("lena.bmp", R, G, B, width, height);
	img_to_gray(width, height);
//	save_bmp("lena_gray.bmp", gray, gray, gray);

	for (i = 0; i<length; i++){
		for (j = 0; j<length; j++){
			weightArr[i][j] = Getweight(j - blurRadius, blurRadius - i);
			printf("(%3d,%3d)  ",j-blurRadius,blurRadius-i);
		}
		printf("\n");
	}
	Printf_WeightArr();
	Add_Arr();
	printf("\n");
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
	
	for(int x=1; x<height;x++){
		for(int y=1;y<width;y++){
			GX[x][y] = 
			(-1)*GASSIAN[x-1][y-1]  + 0*GASSIAN[x][y-1] + 1*GASSIAN[x+1][y-1]
      		+(-2)*GASSIAN[x-1][y] + 0*GASSIAN[x][y]+2*GASSIAN[x+1][y]
      		+(-1)*GASSIAN[x-1][y+1] + 0*GASSIAN[x][y+1] + 1*GASSIAN[x+1][y+1];
		}
	}
//	save_bmp("lena_GX.bmp", GX, GX, GX);
	
	for(int x=1; x<height;x++){
		for(int y=1;y<width;y++){
			GY[x][y] = 
			1* GASSIAN[x-1][y-1] + 2*GASSIAN[x][y-1]+ 1*GASSIAN[x+1][y-1]
      +0*GASSIAN[x-1][y] +0*GASSIAN[x][y] + 0*GASSIAN[x+1][y]
      +(-1)*GASSIAN[x-1][y+1] + (-2)*GASSIAN[x][y+1] + (-1)*GASSIAN[x+1][y+1];
		}
	}
//	save_bmp("lena_GY.bmp", GY, GY, GY);

	
	for(int x=1; x<height;x++){
		for(int y=1;y<width;y++,count++){
			angle[count]=atan (GY[x][y]/GX[x][y]) * 180 / PI;
			count++;
//			printf("%f\n",atan (GY[x][y]/GX[x][y]) * 180 / PI);
		}
		
	}
	
	//梯度方向 
	for(int x=0;x<1024*1024;x++){
		if(angle[x]<22.5 && angle[x]>-22.5){
			degree[x] = 0;
		}
		if(angle[x]<67.5 && angle[x]> 22.5){
			degree[x] = 45;
		}
		if(angle[x]<112.5 && angle[x]> 67.5){
			degree[x] = 90;
		}
		if(angle[x]<-22.5 && angle[x]> -67.5){
			degree[x] = -45;
		}
		if(angle[x]<-67.5 && angle[x]>-122.5){
			degree[x] = -90;
		}
	}

//	for(int x=0;x<1024*1024;x++){
//		printf("%d\n",degree[x]);
//	}
	for(int x=1; x<height;x++){
		for(int y=1;y<width;y++){
			GG[x][y] = abs(GX[x][y])+abs(GY[x][y]);
//			if(GG[x][y]>150){
//				GG[x][y]=255;
//			}else{
//				GG[x][y]=0;
//			}
		}
	}
	save_bmp("lena_GGAA.bmp", GG, GG, GG);
	
	count =0;
	for(int k=0;k<100;k++){
		
		for(int x=1; x<height;x++){
			for(int y=1;y<width;y++){
				if(degree[count] == 0){
					if(GG[x][y] > GG[x-1][y]){
						GG[x][y] =GG[x][y];
					}else if(GG[x][y] > GG[x+1][y]){
						GG[x][y] =GG[x][y];
					}else{
						GG[x][y] = 0;
					}
				}
				if(degree[count] == 45){
					if(GG[x][y] > GG[x-1][y-1]){
						GG[x][y] =GG[x][y];
					}else if(GG[x][y] > GG[x+1][y+1]){
						GG[x][y] =GG[x][y];
					}else{
						GG[x][y] = 0;
					}
				}			
				if(degree[count] == 90){
					if(GG[x][y] > GG[x][y+1]){
						GG[x][y] =GG[x][y];
					}else if(GG[x][y] > GG[x][y-1]){
						GG[x][y] =GG[x][y];
					}else{
						GG[x][y] = 0;
					}
				}			
				if(degree[count] == -45){
					if(GG[x][y] > GG[x-1][y+1]){
						GG[x][y] =GG[x][y];
					}else if(GG[x][y] > GG[x+1][y-1]){
						GG[x][y] =GG[x][y];
					}else{
						GG[x][y] = 0;
					}
				}			
				if(degree[count] == -90){
					if(GG[x][y] > GG[x][y+1]){
						GG[x][y] =GG[x][y];
					}else if(GG[x][y] > GG[x][y-1]){
						GG[x][y] =GG[x][y];
					}else{
						GG[x][y] = 0;
					}
				}			
				count++;
			}
		}
		count=0;
		
	}
	for(int x=1; x<height;x++){
		for(int y=1;y<width;y++){
//			GG[x][y] = 
//			abs(GX[x][y])+abs(GY[x][y]);
			if(GG[x][y]>120 && GG[x][y]<150){
				GG[x][y]=255;
			}else if(GG[x][y]>150){
				GG[x][y]=255;
			}else{
				GG[x][y] =0;
			}
		}
	}
	save_bmp("lena_GGFF.bmp", GG, GG, GG);
	printf("finish\n");

	close_bmp();
	system("pause");
	return 0;
}

//影像灰階 
void img_to_gray(int h, int w){
	int i, j;
	for (i = 0; i < w; i++){
		for (j = 0; j < h; j++){
			gray[i][j] = ((int)((0.299*R[i][j] + 0.587*G[i][j] + 0.114*B[i][j]) * 1000) / 1000);
			GASSIAN[i][j] = gray[i][j];
		}
	}
}

//高斯模糊常態分佈權重 
double Getweight(int x, int y){
	double sigma = 2;
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

//加總權重 
void Add_Arr(){
	int i, j;
	for (i = 0; i < length; i++){
		for (j = 0; j < length; j++){
			sum += weightArr[i][j];
		}
	}
	printf("sum = %f\n", sum);
}

//權重規一化 
void Final_weight(){
	int i, j;
	for (i = 0; i < length; i++){
		for (j = 0; j < length; j++){
			weightArr[i][j] = weightArr[i][j]/sum;
		}
	}
}
