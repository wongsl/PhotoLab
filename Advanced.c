#include "Advanced.h"



void            Posterize(unsigned char R[WIDTH][HEIGHT],
		 unsigned char G[WIDTH][HEIGHT],
		 unsigned char B[WIDTH][HEIGHT], 
		 unsigned int rbits,
		 unsigned int gbits,
		 unsigned int bbits)
{
	int x, y, z;
	int r, g, b, s, t, u = 0;
  for( y = 0; y < HEIGHT; y++ )
  {
	 for( x = 0; x < WIDTH; x++ )
	 {
 		r = g = b = s = t = u = 0;
		for(z = 0; z < rbits - 1; z++)
		{
			r = (r << 1) + 1;
		}
			/*r = r << (8 - rbits);*/
			R[x][y] = R[x][y] | r;    /* will binary or keeping all original digits and changing digits after targetted digit to 1*/
			s = 1 << (rbits-1);
			R[x][y] = R[x][y] & ~s;  /*shifts 1 to targetted digit and not's that acquired number and and's the notted number leaving everything what it was except for targetted digit */

		/*for(z = 0; z < rbits - 2; z++)
		{
			s = (s << 1) + 1; 
		}
			R[x][y] = R[x][y] | s;*/
		for(z = 0; z < gbits - 1; z++)
		{
			g = (g << 1) + 1;
		}
			/*g = g << (8 - gbits);*/
			G[x][y] = G[x][y] | g;
			t = 1 << (gbits-1);
			G[x][y] = G[x][y] & ~t;
		/*for(z = 0; z < gbits - 2; z++)
		{
			t = (t << 1) + 1; 
		}
			G[x][y] = G[x][y] | t;*/
		for(z = 0; z < bbits - 1; z++)
		{
			b = (b << 1) + 1;
		}
			/*b = b << (8 - bbits);*/
			B[x][y] = B[x][y] | b;
			u = 1 << (bbits-1);
			B[x][y] = B[x][y] & ~u;
	
 	}
  }
}

void            AddNoise(int n, unsigned char R[WIDTH][HEIGHT], 
		unsigned char G[WIDTH][HEIGHT], 
		unsigned char B[WIDTH][HEIGHT])
{
int x, k, y = 0;
int num_noise_pixels = 0;
srand(0);
 /*with respect to time, it will generate a random digit*/


num_noise_pixels = n * WIDTH * HEIGHT / 100;

/*sets a number of pixels to be targetted due to the percentage and width and height*/

for(k = 0; k < num_noise_pixels; k++) /*counts off the number of noise pixels to make sure the right percentage is modified*/
	{
	x = rand() % WIDTH;
	y = rand() % HEIGHT;
	R[x][y] = G[x][y] = B[x][y] = 255;
/*randomly changed the pixels to white noise*/


	}
}

void            Overlay(char fname [SLEN],
		unsigned char R[WIDTH][HEIGHT], 
		unsigned char G[WIDTH][HEIGHT], 
		unsigned char B[WIDTH][HEIGHT],
		unsigned int x_offset,
		unsigned int y_offset)
{
int x, y = 0;
unsigned char R2[WIDTH][HEIGHT], G2[WIDTH][HEIGHT], B2[WIDTH][HEIGHT];


ReadImage(fname, R2, G2, B2);

/* loads second image to second array*/

for(x = 0; x < WIDTH; x++)
{
        for(y = 0; y < HEIGHT; y++){
	if(!(R2[x][y] >= 250 && R2[x][y] <= 255  && G2[x][y] >= 250 && G2[x][y] <= 255 && B2[x][y] >= 250 && B2[x][y] <= 255))
	/*makes sure the it only replaces pixes that arent white*/
	{
	R[x_offset + x][y_offset + y] = R2[x][y];
	G[x_offset + x][y_offset + y] = G2[x][y];
	B[x_offset + x][y_offset + y] = B2[x][y];
	}
					}
}
}



void     Tiltshift(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT], int choice, int x_offset, int y_offset, int tiltr)

/*looked up how to make a blur function*/
/*with the blur you can select a region horizontal or vertical to make clear (tiltshift effect) you are able to select how big of a radius and where the clear line will be*/

{
int x, y, i, j = 0;
unsigned char R2[WIDTH][HEIGHT], G2[WIDTH][HEIGHT], B2[WIDTH][HEIGHT];
int SUMR, SUMG, SUMB = 0;

/*for(y = 0; y < HEIGHT; y ++)
{
	for(x = 0; x < WIDTH; x++)
	{
		R3[x][y] = R[x][y];
		G3[x][y] = G[x][y];
		B3[x][y] = B[x][y];
	}
}*/
for(x = 2; x < WIDTH-2; x++) {  /*creates a secondary photo completely blurred using 5 x 5 squares*/
        for(y = 2; y < HEIGHT-2; y++){
		SUMR = 0;
		SUMG = 0;
		SUMB = 0; /*resets sum for every pixel*/
		for(i = x-2; i <= x+2; i++){
			for(j = y-2; j <= y+2; j++){
				SUMR += R[i][j]; /*summation of surrounding pixels*/
				SUMG += G[i][j];
				SUMB += B[i][j];				
			}	
		}
		R2[x][y] = SUMR/25;
		G2[x][y] = SUMG/25;
		B2[x][y] = SUMB/25;	/*averages those pixels*/
	}
}

/*if(choice == 1) circular
{
for(x = 2; x < WIDTH-2; x++){   
        for(y = 2; y < HEIGHT-2; y++){
	{
	R[x][y] = R2[x][y];
	G[x][y] = G2[x][y];
	B[x][y] = B2[x][y];
	}
	
	}
}
}*/
if(choice == 1)/*vert*/
{
        for(y = 2; y < HEIGHT-2; y++)
	{
		for(x = 2; x < WIDTH-2; x++)
		{
		if (x < x_offset - tiltr/2 || x > x_offset + tiltr/2)
		{
		R[x][y] = R2[x][y];
		G[x][y] = G2[x][y];
		B[x][y] = B2[x][y];
		}
		}
	}
	/*for(y = 0; y < HEIGHT; y++)
	{
	for(x = x_offset - tiltr/2; x  < (x + x_offset + tiltr); x++ )
		{
		R[x][y] = R3[x][y];
		G[x][y] = G3[x][y];
		B[x][y] = B3[x][y];	
		}
	}*/
}
if(choice == 2) /*horizontal*/
{        for(y = 2; y < HEIGHT-2; y++)
	{
		for(x = 2; x < WIDTH-2; x++)
		{
		if (y < y_offset - tiltr/2 || y > y_offset + tiltr/2)
		{
		R[x][y] = R2[x][y];
		G[x][y] = G2[x][y];
		B[x][y] = B2[x][y];
		}
		}
	}
}
}
	/*for(y = y_offset - tiltr; (y < (y + y_offset +  tiltr)) ; y++)
	{
	for(x=0; x < WIDTH; x++ )
		{
		R[x][y] = R3[x][y];
		G[x][y] = G3[x][y];
		B[x][y] = B3[x][y];	
		}
	}
}*/


