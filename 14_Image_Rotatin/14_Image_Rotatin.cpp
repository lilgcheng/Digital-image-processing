#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <time.h>
#include <math.h>
#include "bmp.h"
#include "bmp.cpp"
#define PI 3.14159265	//�p�⨤�׮ɨϥΡA��P�v
using namespace std;
int original[MaxBMPSizeX][MaxBMPSizeY]; // MaxBMPSizeX and MaxBMPSizeY are defined in "bmp.h"
int histogram_equalization[MaxBMPSizeX][MaxBMPSizeY]; // MaxBMPSizeX and MaxBMPSizeY are defined in "bmp.h"
int R[MaxBMPSizeX][MaxBMPSizeY];
int G[MaxBMPSizeX][MaxBMPSizeY];
int B[MaxBMPSizeX][MaxBMPSizeY];
int R1[MaxBMPSizeX][MaxBMPSizeY];
int G1[MaxBMPSizeX][MaxBMPSizeY];
int B1[MaxBMPSizeX][MaxBMPSizeY];
int r[1024][1024];
int g[1024][1024];
int b[1024][1024];

int arr[1024][1024];
void img_to_gray(int w, int h);
int main()
{
	double START, END;
	int width, height;
	int i, j;

	START = clock();
	float degree = 0;
	printf("��J���N����:\n");
	scanf("%f", &degree);
	printf("%f\n",degree);
	if(degree <360 && degree>0){
		printf("ok\n");
	}else{
		printf("error\n");
	}
	double angle = degree*PI/180;
	
	open_bmp("framed_airplane.bmp", R, G, B, width, height); // for gray images
    int ox = (width-1)/2; //�s���Iox 
    int oy = (height-1)/2;//�s���Ioy 
 	int nx2,ny2;
 	int p1,p2,p3,p4,p5,p6;//�p�⤺���ϥ�
	int x, y, nx, ny;
 	for(ny=0; ny<height; ++ny){
        for(nx=0; nx<width; ++nx){
    		nx2 = nx - ox;//����X�Ϥ����� 
			ny2 = ny - oy;//����y�Ϥ�����
	        x = (int)( nx2  * cos(angle) + ny2 * sin(angle) +ox);//
            y = (int)(-nx2  * sin(angle) + ny2 * cos(angle) +oy);//
            if(y>=0 && y<height && x>=0 && x<width){
				R1[x][y]=R[ny][nx];
				G1[x][y]=G[ny][nx];
				B1[x][y]=B[ny][nx];
            } else {
				R1[x][y]=255;
				G1[x][y]=255;
				B1[x][y]=255;
            }
        }
    }
	save_bmp("framed_airplane_space_���I�f�ɰw.bmp", R1, G1, B1);
    
	
    for(ny=0; ny<height; ++ny){
        for(nx=0; nx<width; ++nx){
    		nx2 = nx - ox;//����X�Ϥ����� 
			ny2 = ny - oy;//����y�Ϥ�����
	        x = (int)( nx2  * cos(angle) - ny2 * sin(angle) +ox);//����Ϲ����y�� 
            y = (int)(nx2  * sin(angle) + ny2 * cos(angle) +oy);//��
            if(y>=0 && y<height && x>=0 && x<width){
            
				p1 = R[int(x)][int(y)] * abs(y - int(y+1)) + 
 					R[int(x)][int(y+1)] * abs(y - int(y));
 
 				p2 = R[int(x+1)][int(y)] * abs(y - int(y+1)) +
 					R[int(x+1)][int(y+1)] * abs(y - int(y));
 				
 				p3 = G[int(x)][int(y)] * abs(y - int(y+1)) + 
 					G[int(x)][int(y+1)] * abs(y - int(y));
 
 				p4 = G[int(x+1)][int(y)] * abs(y - int(y+1)) +
 					G[int(x+1)][int(y+1)] * abs(y - int(y));
 					
 				p5 = B[int(x)][int(y)] * abs(y - int(y+1)) + 
 					B[int(x)][int(y+1)] * abs(y - int(y));
 
 				p6 = B[int(x+1)][int(y)] * abs(y - int(y+1)) +
 					B[int(x+1)][int(y+1)] * abs(y - int(y));

				R1[nx][ny]=p1 * abs(x - int(x+1)) + p2 * abs(x - int(x));
				G1[nx][ny]=p3 * abs(x - int(x+1)) + p4 * abs(x - int(x));
				B1[nx][ny]=p5 * abs(x - int(x+1)) + p6 * abs(x - int(x));
//			
//				R1[nx][ny]=R[x][y];
//				G1[nx][ny]=G[x][y];
//				B1[nx][ny]=B[x][y];
            } else {
				R1[x][y]=255;
				G1[x][y]=255;
				B1[x][y]=255;
            }
        }
    }
    save_bmp("framed_airplane_gray_����no.bmp", R1, G1, B1);
    save_bmp("arr.bmp", arr, arr, arr);
	close_bmp();
	END = clock();
	printf("�i��B��Ҫ�O���ɶ��G%f S\n", (END - START) / CLOCKS_PER_SEC);
	system("pause");
	return 0;
}


