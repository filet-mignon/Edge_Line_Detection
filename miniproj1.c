#include "bmp.h"
#include "m_mem.h"
#include <math.h>

#define PI 3.1415926535
#define INC 6
#define R_INC 4

unsigned char *bitmap;
int num_pixels;


int main(void)
{
	bitmap = imread("C:\\Users\\EE113D\\Desktop\\image1.bmp");
	
	num_pixels = InfoHeader.Width*InfoHeader.Height;
	
	int i, j, k, x, y, r;
	double radius;
	
	int RANGE = sqrt(InfoHeader.Width*InfoHeader.Width + InfoHeader.Height*InfoHeader.Height)/R_INC;
	
	int* hough = (int*)m_malloc(sizeof(int) *2* RANGE * 180/INC);
		
	for (i = 0; i<(2*RANGE*(180/INC)); i++)
	{
		hough[i] = 0;
	}

	
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
				r *= R_INC;
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
