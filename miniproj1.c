#include "bmp.h"
#include "m_mem.h"
#include <math.h>

#define PI 3.1415926535
#define INC 15
#define R_INC 1
#define THRESHOLD 20

unsigned char *bitmap;
int num_pixels;
int SOBEL = 0;

//0 is straight up, 180 is straight down

int main(void)
{
	bitmap = imread("C:\\Users\\EE113D\\Desktop\\image1.bmp");
//	bitmap = imread("C:\\Users\\EE113D\\Desktop\\Lab_4\\square.bmp");

	int i, j, k, x, y, r;
	double radius;
	int result_x, result_y;

	int WIDTH,HEIGHT;
	if(SOBEL==0){
		//If we're processing the original image
		WIDTH = InfoHeader.Width;
		HEIGHT = InfoHeader.Height;
	}
	else{
		WIDTH = (InfoHeader.Width-2);
		HEIGHT= (InfoHeader.Height-2);
	}

	int RANGE = sqrt(WIDTH*WIDTH + HEIGHT*HEIGHT)/R_INC;
	int* hough = (int*)m_malloc(sizeof(int) *2* RANGE * 180/INC);
	for (i = 0; i<(2*RANGE*(180/INC)); i++)
	{
		hough[i] = 0;
	}

	int sobel_x[3][3] = {	{-1, 0, 1},
							{-2, 0, 2},
							{-1, 0, 1} };
	int sobel_y[3][3] = { 	{-1, -2, -1},
							{0, 0, 0},
							{1, 2, 1} };

	int* sobel_temp;
	int* sobel;

	if(SOBEL==1){
		sobel_temp = (int*)m_malloc(sizeof(int)*(WIDTH)*(HEIGHT));
		sobel = (int*)m_malloc(sizeof(int)*(WIDTH-2)*(HEIGHT-2));

	}

	if(SOBEL==2){
		sobel = (int*)m_malloc(sizeof(int)*(WIDTH)*(HEIGHT));
		for(i = 1; i < (InfoHeader.Height-1); i++){
			for(j = 1; j < (InfoHeader.Width-1); j++){
				result_x = 0;
				result_y = 0;
				int a,b;
				for(a = 0; a < 3; a++){
					for(b = 0; b < 3; b++){
						int xn = j + a - 1;
						int yn = i + b - 1;
						int index = xn + yn*InfoHeader.Width;

						result_x += bitmap[3*index] * sobel_x[a][b];
						result_y += bitmap[3*index] * sobel_y[a][b];
					}
				}
				sobel[(i-1)*(WIDTH) + (j-1)] = sqrt(result_x*result_x + result_y*result_y);

				if(sobel[(i-1)*(WIDTH) + (j-1)] < 100){
					sobel[(i-1)*(WIDTH) + (j-1)] = 255;
				}else{
					sobel[(i-1)*(WIDTH) + (j-1)] = 0;
				}
			}
		}

		for(i = 0; i < HEIGHT; i++){
			for(j = 0; j < WIDTH; j++){
				printf("%d ", (int)sobel[i*WIDTH + j]);
			}
			printf("\n");
		}

	}

	if(SOBEL==0){
		for(i = 0; i < num_pixels; i++){
			//Check if black
			if(bitmap[i*3] <= 5){
				//Calculate ze hough transform
				y = i/InfoHeader.Width;
				x = i%InfoHeader.Width;
				int theta;
				for(theta = 0; theta < 180; theta += INC){
					radius = y*cos(theta*PI/180) + x*sin(theta*PI/180);
					r = (int)(radius/R_INC);
					printf("x is %d, y is %d, r is %d, theta is %d, ", x, y, r, theta);
					hough[(r+RANGE)*(180/INC) + theta/INC]++;
					printf("counter is %d \n", hough[(r+RANGE)*(180/INC) + theta/INC]);
					printf(" y index: %f, x index: %f, matrix index: %f \n", (float)(r+RANGE), (float)(theta/INC), (float)((r+RANGE)*(180/INC) + theta/INC));
				}
			}
		}

		for (j = 0; j<(2*RANGE); j++)
		{
			//printf("%d : ", j-RANGE);
			for(k = 0; k<(180/INC); k++)
			{
				printf("%d ", (int)hough[j*(180/INC) + k]);
				/*
				if(hough[j*(180/INC) + k] >= THRESHOLD){
					printf("Radius: %d, Angle: %d, Occurences: %d \n", (j-RANGE)*R_INC, k*INC, hough[j*(180/INC) + k]);
				}*/
			}
			printf("\n");
		}
	}

	else{
		printf("Starting analysis on filtered image...\n");
		for(i = 0; i < WIDTH*HEIGHT; i++){
			//Check if white
			if(sobel[i] == 0){
				//Calculate ze hough transform
				y = i/(WIDTH);
				x = i%(HEIGHT);
				int theta;
				for(theta = 0; theta < 180; theta += INC){
					radius = x*cos(theta*PI/180) + y*sin(theta*PI/180);
					r = (int)(radius/R_INC);
					//printf("x is %d, y is %d, r is %d, theta is %d, ", x, y, r, theta);
					hough[(r+RANGE)*(180/INC) + theta/INC]++;
					//printf("counter is %d \n", hough[(r+RANGE)*(180/INC) + theta/INC]);
					//printf(" y index: %f, x index: %f, matrix index: %f \n", (float)(r+RANGE), (float)(theta/INC), (float)((r+RANGE)*(180/INC) + theta/INC));
				}
			}
		}
	}





	m_free(hough);
	m_free(sobel);
	m_free(sobel_temp);
	return 0;
}

