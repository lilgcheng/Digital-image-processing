#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <time.h>
#include <math.h>
#include "bmp.h"
#include "bmp.cpp"
#define PI 3.14159265	//計算角度時使用，圓周率
using namespace std;
int original[MaxBMPSizeX][MaxBMPSizeY]; // MaxBMPSizeX and MaxBMPSizeY are defined in "bmp.h"
int histogram_equalization[MaxBMPSizeX][MaxBMPSizeY]; // MaxBMPSizeX and MaxBMPSizeY are defined in "bmp.h"
int R[MaxBMPSizeX][MaxBMPSizeY];
int G[MaxBMPSizeX][MaxBMPSizeY];
int B[MaxBMPSizeX][MaxBMPSizeY];
int r[MaxBMPSizeX][MaxBMPSizeY];
int g[MaxBMPSizeX][MaxBMPSizeY];
int b[MaxBMPSizeX][MaxBMPSizeY];
int gray[1024][1024];
int arr[1024][1024];
int CL_R[1024][1024];
int CL_G[1024][1024];
int CL_B[1024][1024];

int CL_R1[1024][1024];
int CL_G1[1024][1024];
int CL_B1[1024][1024];
int main()
{
	double START, END;
	int width, height;
	int i, j;
	int CENTER_X,CENTER_Y;
	START = clock();
	open_bmp("building2.bmp", R, G, B, width, height); // for gray images
	CENTER_X = width/2;
	CENTER_Y = height/2;
//	printf("%d",CENTER_X);
//	printf("%d\n",width);
//	printf("%d\n",width);
	double win,wout;
	double din,dout;
	int r;
	win = wout = width/2;
//	for(i=0;i<height;i++){
//		for(j=0;j<width;j++){
//			r = sqrt((CENTER_X-i)*(CENTER_X-i)+(CENTER_Y-j)*(CENTER_Y-j));
////			printf("%d\n",r);
//			if(r>380){
//				CL_R[i][j]=255;
//				CL_G[i][j]=255;
//				CL_B[i][j]=255;
//			}else{
//				CL_R[i][j]=R[i][j];
//				CL_G[i][j]=G[i][j];
//				CL_B[i][j]=B[i][j];
//			}
//		}
//	}
//    save_bmp("circle.bmp", CL_R,CL_G,CL_B);
    double x,y;
  	for(i=0;i<height;i++){
		for(j=0;j<width;j++){
			dout = sqrt((CENTER_X-i)*(CENTER_X-i)+(CENTER_Y-j)*(CENTER_Y-j));
			din = (2*win/180) * asin (dout/wout) * 180 / PI;
			if(din > 0){
				x = ((double)din*i/(double)dout)+0.5;
				y = ((double)din*j/(double)dout)+0.5;
	
//				double a = x-(int)x;
//				double b = y-(int)y;
				
//				printf("%f\n",x);		
//				printf("%f\n",y);
//				printf("%f\n",a);		
//				printf("%f\n",b);
//				
				CL_R[i][j]=R[(int)x][(int)y];
				CL_G[i][j]=G[(int)x][(int)y];
				CL_B[i][j]=B[(int)x][(int)y];
			
			}else{
				din=0;
				CL_R[i][j]=0;
				CL_G[i][j]=0;
				CL_B[i][j]=0;
			}
		}
	}
    save_bmp("circle_2.bmp", CL_R,CL_G,CL_B);
 
    
	close_bmp();
	END = clock();
	printf("進行運算所花費的時間：%f S\n", (END - START) / CLOCKS_PER_SEC);
	system("pause");
	return 0;
}


