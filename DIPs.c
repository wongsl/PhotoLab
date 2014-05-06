/*********************************************************************/
/* PhotoLab.c: homework assignment #2, for EECS 22,  Fall 2013       */
/*
 	Author : Steven Wong
	Assignment : Hw2, PhotoLab
	Class : EECS 22, Doemer
 
*/
/* History:                                                          */
/* 10/03/13 Che-Wei Chang  updated for EECS22 assignment2 Fall2013   */
/* 10/02/12 Weiwei Chen  updated for EECS22 assignment2 Fall2012     */
/* 09/27/11 Weiwei Chen  updated for EECS22 assignment2 Fall2011     */
/* 11/11/04 Rainer Doemer:   update for EECS 10 formatting style     */
/* 11/10/04 Rustam Sengupta: initial template version                */
/*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "DIPs.h"
/* age the image to make it look like old picture */
void Aging(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
  int x, y;

  for( y = 0; y < HEIGHT; y++ )
    for( x = 0; x < WIDTH; x++ ) {
      B[x][y] = ( R[x][y]+G[x][y]+B[x][y] )/5;
      R[x][y] = (unsigned char) (B[x][y]*1.6);
      G[x][y] = (unsigned char) (B[x][y]*1.6);
  }
}

/* change color image to black & white */
void            BlackNWhite(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])

{

int x, y = 0;
int z = 0;   /*temporary variables in the scope of the Black and White function*/

for(y = 0; y <HEIGHT; y++)
	{
	for (x = 0; x < WIDTH; x++)
		{
			z = (R[x][y] + G[x][y] + B[x][y]) / 3;
			R[x][y] = z;
			G[x][y] = z;
			B[x][y] = z;
		}
	}
}


void            VFlip(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])

{
int x, y = 0;
int r, g, b = 0;
for(y = 0; y <HEIGHT/2; y++)	/*we are flipping it vertically so therefore we only need to swap half the array*/
	{
	for (x = 0; x < WIDTH; x++)
		{
/*store temporary values of RGB and then swap with the corresponding opposite and convert stored pixel*/
/*middle stays the same*/
			r = R[x][y]; 
			g = G[x][y];
			b = B[x][y];
			R[x][y] = R[x][HEIGHT - 1 - y];
			G[x][y] = G[x][HEIGHT - 1 - y];
			B[x][y] = B[x][HEIGHT - 1 - y];
			R[x][HEIGHT - 1 - y] = r;
			G[x][HEIGHT - 1 - y] = g;
			B[x][HEIGHT - 1 - y] = b;
		}	
	}
}



/* mirror image horizontally */
void            HMirror(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
 int x, y = 0;
for(y = 0; y <HEIGHT; y++)
	{
	for (x = 0; x < WIDTH/2; x++)   /*Only want to replace half of the image*/
		{
			R[x][y] = R[WIDTH - x][y]; /*left side is replaced by corresponding right side*/
			G[x][y] = G[WIDTH - x][y];
			B[x][y] = B[WIDTH - x][y];

		}
	}
}



/* color filter */
void 		ColorFilter(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT], 
														int target_r, int target_g, int target_b, int threshold, double factor_r, double factor_g, double factor_b)  
{
int x, y = 0;


for(y = 0; y <HEIGHT; y++)
	{
	for (x = 0; x < WIDTH; x++) 
	{	
		if(((target_r - threshold) < R[x][y] && R[x][y] < (target_r + threshold)) && ((target_g - threshold) < G[x][y] && G[x][y] < (target_g + threshold)) && ((target_b - threshold) < B[x][y] && B[x][y] < (target_b + threshold)))
		
		{
		R[x][y] = R[x][y] * factor_r;
		G[x][y] = G[x][y] * factor_g;
		B[x][y] = B[x][y] * factor_b;
			if(R[x][y] > 255)
			{
			R[x][y] = 255;
			}
			if(R[x][y] < 0)
			{
			R[x][y] = 0;
			}
			if(G[x][y] > 255)
			{
			G[x][y] = 255;
			}
			if(G[x][y] < 0)
			{
			G[x][y] = 0;
			}
			if(B[x][y] > 255)
			{
			B[x][y] = 255;
			}
			if(B[x][y] < 0)
			{
			B[x][y] = 0;
			}
			else
			continue;
			}
	}
}
}
/* edge detection */
void		Edge(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
int x = 0;
int y = 0;
unsigned char R2[WIDTH][HEIGHT];
unsigned char G2[WIDTH][HEIGHT];
unsigned char B2[WIDTH][HEIGHT];
/*int A[3][3] = {-1, -1, -1; -1, 9, -1; -1, -1, -1}
*/
int Rsum, Gsum, Bsum = 0;

for(y = 0; y <HEIGHT; y++)
	{
	for (x = 0; x < WIDTH; x++) 
		{	R2[x][y] = R[x][y];
			G2[x][y] = G[x][y];
			B2[x][y] = B[x][y];
		}
	}
for(y = 1; y < HEIGHT-1;y++)
	{
	for(x = 1; x <WIDTH -1 ;x++)
			{
			
		Rsum = 8*R2[x][y] - R2[x - 1][y - 1] - R2[x][y - 1]-R2[x+1][y-1]- R2[x-1][y] - R2[x+1][y] - R2[x-1][y+1] -R2 [x][y+1] - R2[x+1][y+1];
		Gsum = 8*G2[x][y] - G2[x - 1][y - 1] - G2[x][y - 1]-G2[x+1][y-1]- G2[x-1][y] - G2[x+1][y] - G2[x-1][y+1] -G2 [x][y+1] - G2[x+1][y+1];
		Bsum = 8*B2[x][y] - B2[x - 1][y - 1] - B2[x][y - 1]-B2[x+1][y-1]- B2[x-1][y] - B2[x+1][y] - B2[x-1][y+1] -B2 [x][y+1] - B2[x+1][y+1];	
		check(R,G,B, Rsum, Gsum, Bsum, x, y);
		
	}
	}




/*

			if(Rsum <= 255 && Rsum >=0)
			{
			R[x][y] = Rsum;
			}
			if(Rsum > 255)
			{
			R[x][y] = 255;
			}
			if(Rsum < 0)
			{
			R[x][y] = 0;
			}
			if(Gsum <= 255 && Gsum >=0)
			{
			G[x][y] = Gsum;
			}
			if(Gsum > 255)
			{
			G[x][y] = 255;
			}
			if(Gsum < 0)
			{
			G[x][y] = 0;
			}
			if(Bsum <= 255 && Bsum >=0)
			{
			B[x][y] = Bsum;
			}
			if(Bsum > 255)
			{
			B[x][y] = 255;
			}
			if(Bsum < 0)
			{
			B[x][y] = 0;
		}
		}
	}
}




*/


for(y = 0; y <HEIGHT; y++)
	{
	for (x = 0; x < WIDTH; x++)
		{
			if (x == 0 && y ==0)	
				{
				Rsum = 3*R2[x][y] - R2[x+1][y]- R2[x][y-1] - R2[x+1][y-1];
				Gsum = 3*G2[x][y] - G2[x+1][y] - G2[x][y - 1]-G2[x+1][y-1];
				Bsum = 3*B2[x][y] - B2[x+1][y] - B2[x][y - 1]-B2[x+1][y-1];	
		check(R,G,B, Rsum, Gsum, Bsum, x, y);
					}
			if (x == WIDTH - 1 && y == 0)
				{	
					Rsum = 3*R2[x][y] - R2[x-1][y]- R2[x-1][y-1] - R2[x][y-1];
					Gsum = 3*G2[x][y] - G2[x-1][y]- G2[x-1][y-1] - G2[x][y-1];
					Bsum = 3*B2[x][y] - B2[x-1][y]- B2[x-1][y-1] - B2[x][y-1];	
			check(R,G,B, Rsum, Gsum, Bsum, x, y);
				}

			if (x == 0 && y == HEIGHT - 1)	
				{	
					Rsum = 3*R2[x][y] - R2[x+1][y] - R2[x][y+1] - R2[x+1][y+1];
					Gsum = 3*G2[x][y] - G2[x+1][y] - G2[x][y+1] - G2[x+1][y+1];
					Bsum = 3*B2[x][y] - B2[x+1][y] - B2[x][y+1] - B2[x+1][y+1];			
				check(R,G,B, Rsum, Gsum, Bsum, x, y);
			}

			if (x == WIDTH - 1 && y == HEIGHT - 1)
				{	
					Rsum = 3*R2[x][y] - R2[x-1][y] - R2[x][y+1] - R2[x-1][y+1];
					Gsum = 3*G2[x][y] - G2[x-1][y] - G2[x][y+1] - G2[x-1][y+1];
					Bsum = 3*B2[x][y] - B2[x-1][y] - B2[x][y+1] - B2[x-1][y+1];	
					check(R,G,B, Rsum, Gsum, Bsum, x, y);
		}	

			if (x == WIDTH - 1 && y !=0 && y != HEIGHT - 1)
				{
					Rsum = 5*R2[x][y] - R2[x - 1][y - 1] - R2[x][y - 1]- R2[x-1][y] - R2[x-1][y-1] -R2 [x][y-1];
					Gsum = 5*G2[x][y] - G2[x - 1][y - 1] - G2[x][y - 1]- G2[x-1][y] -  G2[x-1][y-1] -G2 [x][y-1];
					Bsum = 5*B2[x][y] - B2[x - 1][y - 1] - B2[x][y - 1]- B2[x-1][y] - B2[x-1][y-1] -B2 [x][y-1];	
					check(R,G,B, Rsum, Gsum, Bsum, x, y);
		}

			if (x == 0 && y != 0 && y != HEIGHT - 1)
				{
					Rsum = 5*R2[x][y] - R2[x + 1][y - 1] - R2[x][y - 1]- R2[x+1][y] - R2[x+1][y-1] -R2 [x][y-1];
					Gsum = 5*G2[x][y] - G2[x + 1][y - 1] - G2[x][y - 1]- G2[x+1][y] - G2[x+1][y-1] -G2 [x][y-1];
					Bsum = 5*B2[x][y] - B2[x + 1][y - 1] - B2[x][y - 1]- B2[x+1][y] - B2[x+1][y-1] -B2 [x][y-1];	
					check(R,G,B, Rsum, Gsum, Bsum, x, y);
		}

			if (x != 0 && x != WIDTH - 1 && y == HEIGHT - 1)
				{
					Rsum = 5*R2[x][y] - R2[x - 1][y - 1] - R2[x][y - 1]- R2[x+1][y-1] - R2[x-1][y] -R2 [x+1][y];
					Gsum = 5*G2[x][y] - G2[x - 1][y - 1] - G2[x][y - 1]- G2[x+1][y-1] - G2[x-1][y] -G2 [x+1][y];
					Bsum = 5*B2[x][y] - B2[x - 1][y - 1] - B2[x][y - 1]- B2[x+1][y-1] - B2[x-1][y] -B2 [x+1][y];	
				
					check(R,G,B, Rsum, Gsum, Bsum, x, y);
		}

			if (x != 0 && x != WIDTH - 1 && y == 0)
 				{
					Rsum = 5*R2[x][y] - R2[x - 1][y + 1] - R2[x][y + 1]- R2[x-1][y] - R2[x-1][y+1] -R2 [x+1][y];
					Gsum = 5*G2[x][y] - G2[x - 1][y + 1] - G2[x][y + 1]- G2[x-1][y] - G2[x-1][y+1] -G2 [x+1][y];
					Bsum = 5*B2[x][y] - B2[x - 1][y + 1] - B2[x][y + 1]- B2[x-1][y] - B2[x-1][y+1] -B2 [x+1][y];	
				
					check(R,G,B, Rsum, Gsum, Bsum, x, y);
		}
		/*	else
			{
			R[x][y] = 8*R2[x][y] - R2[x - 1][y - 1] - R2[x][y - 1]-R2[x+1][y+1]- R2[x-1][y] - R2[x+1][y] - R2[x-1][y-1] -R2 [x][y-1] - R2[x+1][y-1];
		G[x][y] = 8*G2[x][y] - G2[x - 1][y - 1] - G2[x][y - 1]-G2[x+1][y+1]- G2[x-1][y] - G2[x+1][y] - G2[x-1][y-1] -G2 [x][y-1] - G2[x+1][y-1];
		B[x][y] = 8*R2[x][y] - B2[x - 1][y - 1] - B2[x][y - 1]-B2[x+1][y+1]- B2[x-1][y] - B2[x+1][y] - B2[x-1][y-1] -B2 [x][y-1] - B2[x+1][y-1];	
				check(R,G,B, Rsum, Gsum, Bsum, x, y);
		}	*/
		/*	if(Rsum <= 255 && Rsum >=0)
			{
			R[x][y] = Rsum;
			}
			if(Rsum > 255)
			{
			R[x][y] = 255;
			}
			if(Rsum < 0)
			{
			R[x][y] = 0;
			}
			if(Gsum <= 255 && Gsum >=0)
			{
			G[x][y] = Gsum;
			}
			if(Gsum > 255)
			{
			G[x][y] = 255;
			}
			if(Gsum < 0)
			{
			G[x][y] = 0;
			}
			if(Bsum <= 255 && Bsum >=0)
			{
			B[x][y] = Bsum;
			}
			if(Bsum > 255)
			{
			B[x][y] = 255;
			}
			if(Bsum < 0)
			{
			B[x][y] = 0;
			}*/
		}
	}

}


/* sharpen the image*/ 
void		Sharpen(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
int x = 0;
int y = 0;
unsigned char R2[WIDTH][HEIGHT];
unsigned char G2[WIDTH][HEIGHT];
unsigned char B2[WIDTH][HEIGHT];
int Rsum, Gsum, Bsum = 0;

for(y = 0; y <HEIGHT; y++)
	{
	for (x = 0; x < WIDTH; x++) 
		{	R2[x][y] = R[x][y];
			G2[x][y] = G[x][y];
			B2[x][y] = B[x][y];
		}
	}
for(y = 1; y < HEIGHT-1;y++)
	{
	for(x = 1; x <WIDTH -1 ;x++)
		{
			
		Rsum = 9*R2[x][y] - R2[x - 1][y - 1] - R2[x][y - 1]-R2[x+1][y-1]- R2[x-1][y] - R2[x+1][y] - R2[x-1][y+1] -R2 [x][y+1] - R2[x+1][y+1];
		Gsum = 9*G2[x][y] - G2[x - 1][y - 1] - G2[x][y - 1]-G2[x+1][y-1]- G2[x-1][y] - G2[x+1][y] - G2[x-1][y+1] -G2 [x][y+1] - G2[x+1][y+1];
		Bsum = 9*B2[x][y] - B2[x - 1][y - 1] - B2[x][y - 1]-B2[x+1][y-1]- B2[x-1][y] - B2[x+1][y] - B2[x-1][y+1] -B2 [x][y+1] - B2[x+1][y+1];	
		check(R,G,B, Rsum, Gsum, Bsum, x, y);	
		}
	}
		

for(y = 0; y <HEIGHT; y++)
	{
	for (x = 0; x < WIDTH; x++)
		{	
			if (x == 0 && y ==0)	
			{
			R[x][y] = 4*R2[x][y] - R2[x+1][y]- R2[x][y-1] - R2[x+1][y-1];
			G[x][y] = 4*G2[x][y] - G2[x+1][y] - G2[x][y - 1]-G2[x+1][y-1];
			B[x][y] = 4*B2[x][y] - B2[x+1][y] - B2[x][y - 1]-B2[x+1][y-1];	
				check(R,G,B, Rsum, Gsum, Bsum, x, y);
			}
			if (x == WIDTH - 1 && y == 0)
			{	
			R[x][y] = 4*R2[x][y] - R2[x-1][y]- R2[x-1][y-1] - R2[x][y-1];
			G[x][y] = 4*G2[x][y] - G2[x-1][y]- G2[x-1][y-1] - G2[x][y-1];
			B[x][y] = 4*B2[x][y] - B2[x-1][y]- B2[x-1][y-1] - B2[x][y-1];	
				check(R,G,B, Rsum, Gsum, Bsum, x, y);
			}

			if (x == 0 && y == HEIGHT - 1)	
			{
			R[x][y] = 4*R2[x][y] - R2[x+1][y] - R2[x][y+1] - R2[x+1][y+1];
			G[x][y] = 4*G2[x][y] - G2[x+1][y] - G2[x][y+1] - G2[x+1][y+1];
			B[x][y] = 4*B2[x][y] - B2[x+1][y] - B2[x][y+1] - B2[x+1][y+1];	
			check(R,G,B, Rsum, Gsum, Bsum, x, y);
				}

			if (x == WIDTH - 1 && y == HEIGHT - 1)
				{	
					R[x][y] = 4*R2[x][y] - R2[x-1][y] - R2[x][y+1] - R2[x-1][y+1];
					G[x][y] = 4*G2[x][y] - G2[x-1][y] - G2[x][y+1] - G2[x-1][y+1];
					B[x][y] = 4*B2[x][y] - B2[x-1][y] - B2[x][y+1] - B2[x-1][y+1];	
				check(R,G,B, Rsum, Gsum, Bsum, x, y);
				}

			if (x == WIDTH - 1 && y !=0 && y != HEIGHT - 1)
				{
					R[x][y] = 6*R2[x][y] - R2[x - 1][y - 1] - R2[x][y - 1]- R2[x-1][y] - R2[x-1][y-1] -R2 [x][y-1];
					G[x][y] = 6*G2[x][y] - G2[x - 1][y - 1] - G2[x][y - 1]- G2[x-1][y] -  G2[x-1][y-1] -G2 [x][y-1];
					B[x][y] = 6*B2[x][y] - B2[x - 1][y - 1] - B2[x][y - 1]- B2[x-1][y] - B2[x-1][y-1] -B2 [x][y-1];	
				check(R,G,B, Rsum, Gsum, Bsum, x, y);
				}

			if (x == 0 && y != 0 && y != HEIGHT - 1)
				{
					R[x][y] = 6*R2[x][y] - R2[x + 1][y - 1] - R2[x][y - 1]- R2[x+1][y] - R2[x+1][y-1] -R2 [x][y-1];
					G[x][y] = 6*G2[x][y] - G2[x + 1][y - 1] - G2[x][y - 1]- G2[x+1][y] - G2[x+1][y-1] -G2 [x][y-1];
					B[x][y] = 6*B2[x][y] - B2[x + 1][y - 1] - B2[x][y - 1]- B2[x+1][y] - B2[x+1][y-1] -B2 [x][y-1];	
				check(R,G,B, Rsum, Gsum, Bsum, x, y);
				}

			if (x != 0 && x != WIDTH - 1 && y == HEIGHT - 1)
				{
					R[x][y] = 6*R2[x][y] - R2[x - 1][y - 1] - R2[x][y - 1]- R2[x+1][y-1] - R2[x-1][y] -R2 [x+1][y];
					G[x][y] = 6*G2[x][y] - G2[x - 1][y - 1] - G2[x][y - 1]- G2[x+1][y-1] - G2[x-1][y] -G2 [x+1][y];
					B[x][y] = 6*B2[x][y] - B2[x - 1][y - 1] - B2[x][y - 1]- B2[x+1][y-1] - B2[x-1][y] -B2 [x+1][y];	
				check(R,G,B, Rsum, Gsum, Bsum, x, y);
				}
			if (x != 0 && x != WIDTH - 1 && y == 0)
 				{
					R[x][y] = 6*R2[x][y] - R2[x - 1][y + 1] - R2[x][y + 1]- R2[x-1][y] - R2[x-1][y+1] -R2 [x+1][y];
					G[x][y] = 6*G2[x][y] - G2[x - 1][y + 1] - G2[x][y + 1]- G2[x-1][y] - G2[x-1][y+1] -G2 [x+1][y];
					B[x][y] = 6*B2[x][y] - B2[x - 1][y + 1] - B2[x][y + 1]- B2[x-1][y] - B2[x-1][y+1] -B2 [x+1][y];					
				check(R,G,B, Rsum, Gsum, Bsum, x, y);
				}

	
	}

}

}


/*add border*/

void AddBorder (unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT], int border_r, int border_g, int border_b, int border_width)

{
int x, y = 0;


for(y = 0; y <HEIGHT; y++)
	{
	for (x = 0; x < WIDTH; x++) 
		{	
		if(x < border_width || x > WIDTH - 1 - border_width || y < border_width || y > HEIGHT - 1 - border_width)
		{
		 R[x][y] = border_r;
		 G[x][y] = border_g;
		 B[x][y] = border_b;
		}
		}	
	}
}


void check(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT], int Rsum, int Gsum, int Bsum, int x, int y)

{
			if(Rsum <= 255 && Rsum >=0)
			{
			R[x][y] = Rsum;
			}
			if(Rsum > 255)
			{
			R[x][y] = 255;
			}
			if(Rsum < 0)
			{
			R[x][y] = 0;
			}
			if(Gsum <= 255 && Gsum >=0)
			{
			G[x][y] = Gsum;
			}
			if(Gsum > 255)
			{
			G[x][y] = 255;
			}
			if(Gsum < 0)
			{
			G[x][y] = 0;
			}
			if(Bsum <= 255 && Bsum >=0)
			{
			B[x][y] = Bsum;
			}
			if(Bsum > 255)
			{
			B[x][y] = 255;
			}
			if(Bsum < 0)
			{
			B[x][y] = 0;
			}

}



/*void	AutoTest(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
	char            fname[SLEN] = "UCI_Peter";
  char            sname[SLEN];

	ReadImage(fname, R, G, B);
	Aging(R, G, B);
	strcpy(sname, "age");
	SaveImage(sname, R, G, B);
	printf("Aging tested!\n\n");

	ReadImage(fname, R, G, B);
	BlackNWhite(R, G, B);
	strcpy(sname, "bw");
	SaveImage(sname, R, G, B);
	printf("Black & White tested!\n\n");

	ReadImage(fname, R, G, B);
	VFlip(R, G, B);
	strcpy(sname, "vflip");
	SaveImage(sname, R, G, B);
	printf("Vertical Flip tested!\n\n");

	ReadImage(fname, R, G, B);
	HMirror(R, G, B);
	strcpy(sname, "hmirror");
	SaveImage(sname, R, G, B);
	printf("Aging tested!\n\n");

	ReadImage(fname, R, G, B);
	ColorFilter(R, G, B, 250, 196, 135, 20, .25, .25, .4);
	strcpy(sname, "colorfilter");
	SaveImage(sname, R, G, B);
	printf("Color Filter tested!\n\n");

	ReadImage(fname, R, G, B);
	Edge(R, G, B);
	strcpy(sname, "edge");
	SaveImage(sname, R, G, B);
	printf("Edge tested!\n\n");

	ReadImage(fname, R, G, B);
	Sharpen(R, G, B);
	strcpy(sname, "sharpen");
	SaveImage(sname, R, G, B);
	printf("Sharpen tested!\n\n");

	ReadImage(fname, R, G, B);
	AddBorder(R, G, B, 128, 128, 128, 9);
	strcpy(sname, "border");
	SaveImage(sname, R, G, B);
	printf("Border tested!\n\n");

}
*/
