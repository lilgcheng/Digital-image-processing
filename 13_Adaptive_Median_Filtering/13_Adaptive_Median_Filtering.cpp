
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <windows.h>
#include "bmp.h"
#include "bmp.cpp"
int r = 1;
int flag = 0;
int Zmin = 0;
int Zmax = 0;
int Zmed = 0;
int Zxy  = 0;
int R[MaxBMPSizeX][MaxBMPSizeY];
int G[MaxBMPSizeX][MaxBMPSizeY];
int B[MaxBMPSizeX][MaxBMPSizeY];
int arr[9]= { 0 };
using namespace std;
int gray[1024][1024];
int gray_copy[1024][1024];
void img_to_gray(int h, int w);
void Notation(int x, int y,int r);
void Sort_arr(int size,int x,int y);
int Algorithm(int x,int y,int r);
int main()
{
	int width, height;
	int i, j,c;
	open_bmp("lena_noise_RGB_5.bmp", R, G, B, width, height);
	img_to_gray(width, height);
	save_bmp("lena_gray.bmp", gray, gray, gray);
	
	for(i=0;i<width;i++){
		for(j=0;j<height;j++){
			gray[i][j]=Algorithm(i+r,j+r,r);
		}
	}		
	save_bmp("lena_filter_r0.bmp", gray, gray, gray);
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

void Notation(int x, int y,int r){
	int START_X = x - r;
	int START_Y = y - r;
	int counter = 0;
	int L = r * 2 + 1;
	Zxy = gray[START_X][START_Y];
	for (int i = START_X; i < START_X + L; i++){
		for (int j = START_Y; j < START_Y + L; j++){
			arr[counter] = gray[i][j];
//			printf("[%d] ", counter);
//			printf("%d", counter);
//			printf("%5d", arr[counter]);
			counter++;
		}
	}	
//	printf("\n");
	Sort_arr(counter,START_X,START_Y); 
}

void Sort_arr(int size,int x,int y){
//	printf("%d",size);
	int temp = 0;
	for(int i=0;i<size;i++){
		for(int j=i+1;j<size;j++){
			if(arr[i]>arr[j]){
				temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
		}
	}
	Zmin = arr[0];
	Zmax = arr[size-1];
	Zmed = arr[size/2];
//	printf("Zmin=%3d  Zmax=%3d  Zmed=%3d  Zxy =%3d\n",Zmin,Zmax,Zmed,Zxy);

//	for(int i=0;i<size;i++){
//		printf("%5d",arr[i]);
//	}
//	printf("\n");

}
int Algorithm(int x,int y,int r){
	Notation(x+r,y+r,r);
	
	int A1 = Zmed - Zmin;
	int A2 = Zmed - Zmax;
	if(A1 > 0 && A2<0){
		flag = 1;
	}else{
		flag = 0;
		Notation(x,y,r);
		return Zxy;
	}
	
	if(flag == 1){
	int B1 = Zxy - Zmin;
	int B2 = Zxy - Zmax;
		if(B1 > 0 && B2 < 0){
			return Zxy;
		}else{
			return Zmed;
		}
	}
	
}

