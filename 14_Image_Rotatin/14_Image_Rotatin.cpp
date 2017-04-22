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
int r[1024][1024];
int g[1024][1024];
int b[1024][1024];
int gray[1024][1024];
int arr[1024][1024];
void img_to_gray(int w, int h);
int main()
{
	double START, END;
	int width, height;
	int i, j;

	START = clock();
	float degree = 0;
	printf("輸入任意角度:\n");
	scanf("%f", &degree);
	printf("%f\n",degree);
	if(degree <360 && degree>0){
		printf("ok\n");
	}else{
		printf("error\n");
	}
	double angle = degree*PI/180;
	
	open_bmp("framed_airplane.bmp", R, G, B, width, height); // for gray images
	img_to_gray(width,height); 
	save_bmp("framed_airplane_gray.bmp", gray, gray, gray);
	int x, y, nx, ny;
// 	for(ny=0; ny<height; ++ny){
//        for(nx=0; nx<width; ++nx){
//            x = (int)(nx * cos(angle) - ny * sin(angle) + 0.5);
//            y = (int)(nx * sin(angle) + ny * cos(angle) + 0.5);
//            if(y>=0 && y<height && x>=0 && x<width){
//				arr[ny][nx]=gray[y][x];
//            } else {
//				arr[ny][nx]=255;
//            }
//        }
//    }
//	save_bmp("framed_airplane_gray_原點逆時針.bmp", arr, arr, arr);
    
    int ox = (width-1)/2; //新原點ox 
    int oy = (height-1)/2;//新原點oy 
 	int nx2,ny2;
 	int p1,p2;//計算內插使用
	  
//	for(ny=0; ny<height; ++ny){
//        for(nx=0; nx<width; ++nx){
//    		nx2 = nx - ox;
//			ny2 = ny - oy;
//	        x = (int)( nx2  * cos(angle) + ny2 * sin(angle) +ox);
//            y = (int)(-nx2  * sin(angle) + ny2 * cos(angle) +oy);
//            if(y>=0 && y<height && x>=0 && x<width){
//				arr[ny][nx]=gray[x][y];
//            }
//			else {
//				arr[ny][nx]=255;
//            }
//        }
//    }
//    save_bmp("framed_airplane_gray_平移原點逆時針.bmp", arr, arr, arr);
//    
    for(ny=0; ny<height; ++ny){
        for(nx=0; nx<width; ++nx){
    		nx2 = nx - ox;
			ny2 = ny - oy;
	        x = (int)( nx2  * cos(angle) + ny2 * sin(angle) + 0.5+ox);
            y = (int)(-nx2  * sin(angle) + ny2 * cos(angle) + 0.5+oy);
            if(y>=0 && y<height && x>=0 && x<width){
				p1 = gray[int(x)][int(y)] * abs(y - int(y+1)) + 
					gray[int(x)][int(y+1)] * abs(y - int(y));

				p2 = gray[int(x+1)][int(y)] * abs(y - int(y+1)) +
					gray[int(x+1)][int(y+1)] * abs(y - int(y));
//				arr[x][y] = p1 * abs(x - int(nx+1)) + p2 * abs(x - int(x));
				arr[x][y]=gray[ny][nx];
            } else {
				arr[x][y]=255;
            }
        }
    }
    save_bmp("framed_airplane_gray_內插.bmp", arr, arr, arr);
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
		}
	}
}
