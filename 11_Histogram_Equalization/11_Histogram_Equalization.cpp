// 01_Error_diffusion.cpp : ﹚竡北莱ノ祘Α秈翴
//


#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <time.h>
#include "bmp.h"
#include "bmp.cpp"
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
float pmf[256];
float cdf[256];
void img_to_gray(int w, int h);
void PMF(int w, int h);
void CDF();
void HE(int w, int h);
int main()
{
	double START, END;
	int width, height;
	int i, j;
	int x, y;
	int err;
	START = clock();
	//open_bmp("boat.bmp", R, G, B, width, height);
	open_bmp("boat.bmp", original, original, original, width, height); // for gray images
	//printf("height = %3d , width = %3d\n", height, width);
	//	img_to_gray(width, height);
	//	save_bmp("boat_gray.bmp", gray, gray, gray);
	PMF(width, height);
	CDF();
	HE(width, height);
	save_bmp("boat_HE.bmp", histogram_equalization, histogram_equalization, histogram_equalization);
	
	//	for(i=0;i<256;i++){
	//		printf("%f\n",cdf[i]);
	//	} 
	
	
	close_bmp();
	END = clock();
	printf("秈︽笲衡┮禣丁%f S\n", (END - START) / CLOCKS_PER_SEC);
	system("pause");
	return 0;
}

//void img_to_gray(int w, int h){
//	int i, j;
//	for (i = 0; i < w; i++){
//		for (j = 0; j < h; j++){
//			gray[i][j] = ((int)((0.299*R[i][j] + 0.587*G[i][j] + 0.114*B[i][j]) * 1000) / 1000);
//		}
//	}
//}

void PMF(int w, int h){
	int count=0;
	int c=0;
	int i,j;
	float sum=0;
	for(count=0;count<256;count++){	
		for (i = 0; i < w; i++){
			for (j = 0; j < h; j++){
				if(original[i][j]==count){
					c++;//c参璸 单count计Τ碭 
				}
			}
		}
		pmf[count]=(double)c/(w*h);
		c=0;
//		printf("mark = %d ---- %f\n",count,pmf[count]);
		sum +=pmf[count];
	}
//	printf("%f",sum);
}

void CDF(){
	int i,j;
	float sum=0;
	for(i=0;i<256;i++){
		for(j=0;j<=i+1;j++){
			sum = sum+pmf[j];
		}
		cdf[i] = sum;
		printf("cdf ----- %f\n",sum);
		sum = 0;
	}
}


void HE(int w, int h){
	int count=0;
	int c=0;
	int i,j;
	for(count=0;count<256;count++){	
		for (i = 0; i < w; i++){
			for (j = 0; j < h; j++){
				if(original[i][j]==count){
//					gray[i][j] = cdf[count]*gray[i][j];
					histogram_equalization[i][j] = (float)((cdf[count]-0)/ (float)(1-0))*255;
				}
			}
		}
	}
}
