#include "bmp.h"
#include "m_mem.h"
#include <math.h>

#define PI 3.1415926535
#define INC 15
#define R_INC 2

#define SOBEL 1

unsigned char *bitmap;
int num_pixels;

//0 is straight up, 180 is straight down

int main(void)
{
//	bitmap = imread("C:\\Users\\EE113D\\Desktop\\image1.bmp");
	bitmap = imread("G:\\test2.bmp");

	num_pixels = InfoHeader.Width*InfoHeader.Height;

	int i, j, k, x, y, r;
	double radius;
	int result_x, result_y;

	int RANGE = sqrt(InfoHeader.Width*InfoHeader.Width + InfoHeader.Height*InfoHeader.Height)/R_INC;

	int* hough = (int*)m_malloc(sizeof(int) *2* RANGE * 180/INC);

	for (i = 0; i<(2*RANGE*(180/INC)); i++)
	{
		hough[i] = 0;
	}

	int sobel_x[3][3] = { {-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1} };
	int sobel_y[3][3] = { {-1, -2, -1}, {0, 0, 0}, {1, 2, 1} };

	if(SOBEL==1){
		int* sobel_temp = (int*)m_malloc(sizeof(int)*(InfoHeader.Width-2)*(InfoHeader.Height-2));
		int* sobel = (int*)m_malloc(sizeof(int)*(InfoHeader.Width-4)*(InfoHeader.Height-4));

		for(i = 1; i < (InfoHeader.Height-1); i++){
			for(j = 1; j < (InfoHeader.Width-1); j++){
				result_x = (bitmap[3*((i-1)*InfoHeader.Width + (j-1))]*sobel_x[2][0] +
							bitmap[3*((i-1)*InfoHeader.Width + (j))]*sobel_x[2][1] +
							bitmap[3*((i-1)*InfoHeader.Width + (j+1))]*sobel_x[2][2] +
							bitmap[3*((i)*InfoHeader.Width + (j-1))]*sobel_x[1][0] +
							bitmap[3*((i)*InfoHeader.Width + (j))]*sobel_x[1][1] +
							bitmap[3*((i)*InfoHeader.Width + (j+1))]*sobel_x[1][2] +
							bitmap[3*((i+1)*InfoHeader.Width + (j-1))]*sobel_x[0][0] +
							bitmap[3*((i+1)*InfoHeader.Width + (j))]*sobel_x[0][1] +
							bitmap[3*((i+1)*InfoHeader.Width + (j+1))]*sobel_x[0][2]);
				sobel_temp[(i-1)*(InfoHeader.Width-2)+(j-1)] = result_x;
			}
		}
		for(i = 2; i < (InfoHeader.Height-2); i++){
			for(j = 2; j < (InfoHeader.Width-2); j++){
				result_y = (sobel[((i-1)*InfoHeader.Width + (j-1))]*sobel_y[2][0] +
							sobel[((i-1)*InfoHeader.Width + (j))]*sobel_y[2][1] +
							sobel[((i-1)*InfoHeader.Width + (j+1))]*sobel_y[2][2] +
							sobel[((i)*InfoHeader.Width + (j-1))]*sobel_y[1][0] +
							sobel[((i)*InfoHeader.Width + (j))]*sobel_y[1][1] +
							sobel[((i)*InfoHeader.Width + (j+1))]*sobel_y[1][2] +
							sobel[((i+1)*InfoHeader.Width + (j-1))]*sobel_y[0][0] +
							sobel[((i+1)*InfoHeader.Width + (j))]*sobel_y[0][1] +
							sobel[((i+1)*InfoHeader.Width + (j+1))]*sobel_y[0][2]);
				sobel[(i)*(InfoHeader.Width-4)+(j)] = result_y;
			}
		}
	}

	if(SOBEL==2){
		int* sobel = (int*)m_malloc(sizeof(int)*(InfoHeader.Width-2)*(InfoHeader.Height-2));
		for(i = 1; i < (InfoHeader.Height-1); i++){
			for(j = 1; j < (InfoHeader.Width-1); j++){
				result_x = (bitmap[3*((i-1)*InfoHeader.Width + (j-1))]*sobel_x[2][0] +
							bitmap[3*((i-1)*InfoHeader.Width + (j))]*sobel_x[2][1] +
							bitmap[3*((i-1)*InfoHeader.Width + (j+1))]*sobel_x[2][2] +
							bitmap[3*((i)*InfoHeader.Width + (j-1))]*sobel_x[1][0] +
							bitmap[3*((i)*InfoHeader.Width + (j))]*sobel_x[1][1] +
							bitmap[3*((i)*InfoHeader.Width + (j+1))]*sobel_x[1][2] +
							bitmap[3*((i+1)*InfoHeader.Width + (j-1))]*sobel_x[0][0] +
							bitmap[3*((i+1)*InfoHeader.Width + (j))]*sobel_x[0][1] +
							bitmap[3*((i+1)*InfoHeader.Width + (j+1))]*sobel_x[0][2]);
				result_y = (bitmap[3*((i-1)*InfoHeader.Width + (j-1))]*sobel_y[2][0] +
							bitmap[3*((i-1)*InfoHeader.Width + (j))]*sobel_y[2][1] +
							bitmap[3*((i-1)*InfoHeader.Width + (j+1))]*sobel_y[2][2] +
							bitmap[3*((i)*InfoHeader.Width + (j-1))]*sobel_y[1][0] +
							bitmap[3*((i)*InfoHeader.Width + (j))]*sobel_y[1][1] +
							bitmap[3*((i)*InfoHeader.Width + (j+1))]*sobel_y[1][2] +
							bitmap[3*((i+1)*InfoHeader.Width + (j-1))]*sobel_y[0][0] +
							bitmap[3*((i+1)*InfoHeader.Width + (j))]*sobel_y[0][1] +
							bitmap[3*((i+1)*InfoHeader.Width + (j+1))]*sobel_y[0][2]);
				sobel[(i-1)*(InfoHeader.Width-2)+(j-1)] = sqrt(result_x*result_x + result_y*result_y);
			}
		}
	}


	for(i = 0; i < num_pixels; i++){
		//Check if black
		if(bitmap[i*3] <= 0){
			//Calculate ze hough transform
			y = i/InfoHeader.Width;
			x = i%InfoHeader.Width;
			int theta;
			for(theta = 0; theta < 180; theta += INC){
				radius = y*cos(theta*PI/180) + x*sin(theta*PI/180);
				r = (int)(radius/R_INC);
				//printf("x is %d, y is %d, r is %d, theta is %d, ", x, y, r, theta);
				hough[(r+RANGE)*(180/INC) + theta/INC]++;
				//printf("counter is %d \n", hough[(r+RANGE)*(180/INC) + theta/INC]);
				//printf(" y index: %f, x index: %f, matrix index: %f \n", (float)(r+RANGE), (float)(theta/INC), (float)((r+RANGE)*(180/INC) + theta/INC));
			}
		}
	}

	for (j = 0; j<(2*RANGE); j++)
	{
		//printf("%d : ", j-RANGE);
		for(k = 0; k<(180/INC); k++)
		{
			printf("%d ", hough[j*(180/INC) + k]);
		}
		printf("\n");
	}



	m_free(hough);
	return 0;
}
