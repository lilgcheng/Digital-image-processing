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
int arr_l[1024][1024];
int arr_r[1024][1024];
int gray[1024][1024];
int big[1024][1024];
void img_to_gray(int w, int h);
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
	open_bmp("framed_lena_color_256.bmp", R, G, B, width, height); // for gray images
	img_to_gray(width,height); 
	//	save_bmp("lena_gray.bmp", gray, gray, gray);

	//原點訂於圖片正中央，將外圍反白 
	for(x=0;x<width;x++){
		for(y=0;y<height;y++){
			if(gray[x][y]==0){
				gray[x][y]=255;
			}
		}
	}
		save_bmp("lena_edge_space.bmp", gray, gray, gray);
	
	//原點訂於圖片左下角 
	for(x=0;x<width;x++){
		for(y=0;y<height;y++){   
			arr_l[x][y]=gray[x+(width/4)][y+(height/4)];
			if(	arr_l[x][y]==0){
				arr_l[x][y]=255;
			}
		}
	}
		save_bmp("lena_LO.bmp", arr_l, arr_l, arr_l);
	
	//	原點於圖片右上角 
	for(x=0;x<width;x++){
		for(y=0;y<height;y++){   
			arr_r[x][y]=arr_l[x][y-(height/2)];
			if(	arr_r[x][y]==0){
				arr_r[x][y]=255;
			}
		}
	}
	save_bmp("lena_RO.bmp", arr_r, arr_r, arr_r);

	//放大圖片
	 for(x=0;x<width;x+=2){
		for(y=0;y<height;y+=2){ 
			if(x%2==0){
				big[x][y] =arr_l[i][j];
				j++;
			}
		}
		i++;
		j=0;
	}
	save_bmp("lena_big.bmp", big, big, big);
//	
	//水平方向內插 
	for(x=1;x<width;x+=2){
		for(y=0;y<height;y+=2){   
			big[x][y] = big[x-1][y];
		}
	}
	save_bmp("lena_big_hoz.bmp", big, big, big);
//	
	//垂直方向內插 
	for(x=0;x<width;x+=2){
		for(y=1;y<height;y+=2){   
			big[x][y] = big[x][y-1];
		}
	}
	save_bmp("lena_big_ror.bmp", big, big, big);
//	
	//垂直方向內插 (中間) (1,1)(1,3)... 
	for(x=1;x<width;x+=2){
		for(y=1;y<height;y+=2){   
			big[x][y] = big[x-1][y];
		}
	}
	save_bmp("lena_big_final.bmp", big, big, big);
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
