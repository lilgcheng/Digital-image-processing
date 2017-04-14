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

int main()
{
	double START, END;
	int width, height;
	int i, j;
	int x, y;
	float rotation;
	START = clock();
	printf("輸入任意角度:\n");
	scanf("%f", &rotation);
	printf("%f\n",rotation);
	if(rotation <360 && rotation>0){
		printf("ok\n");
	}else{
		printf("error\n");
	}
	open_bmp("framed_airplane.bmp", R, G, B, width, height); // for gray images

//	save_bmp("boat_HE.bmp", histogram_equalization, histogram_equalization, histogram_equalization);
	
	close_bmp();
	END = clock();
	printf("進行運算所花費的時間：%f S\n", (END - START) / CLOCKS_PER_SEC);
	system("pause");
	return 0;
}


