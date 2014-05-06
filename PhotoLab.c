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
#include "Advanced.h"
#include "FileIO.h"
#include "Constants.h"
#include "DIPs.h"

void PrintMenu(void);

void AutoTest(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);

int main()
{
	/*
	 * Two dimensional arrays to hold the current image data. One array
	 * for each color component
	 */
	unsigned char   R[WIDTH][HEIGHT];
	unsigned char   G[WIDTH][HEIGHT];
	unsigned char   B[WIDTH][HEIGHT];
	char fname[SLEN];
	int selection = 0; 
	int R_target, B_target, G_target;
	int border_r, border_g, border_b, border_width;
	int threshold = 0;
	int tiltr, choice;
	double factor_r, factor_g, factor_b = 0;
	int rbits, gbits, bbits;	
	int n;
	int x_offset, y_offset;

	#ifdef DEBUG
	AutoTest(R,G,B);
	return 0;
	#endif

while(1)
{
	PrintMenu();
	scanf("%d", &selection);
	switch (selection)
	{
		case 1: 
			printf("Please input a file name to load: \n");
			scanf("%s", fname);
			ReadImage(fname, R, G, B);
			break;

		case 2:
			printf("Please input the file name to save: \n");	
			scanf("%79s", &fname[0]);
			SaveImage(fname, R, G, B);
			break;
		case 3:	
			BlackNWhite(R, G, B);
			printf("\"Black & White\" Operation Done!\n");
			break;
		case 4:
			VFlip(R,G,B);
			printf("\"Vertical Flip\" Operation Done!\n");
			break;
		case 5:
			HMirror(R,G,B);
			printf("\"Horizontal Mirror\" Operation Done!\n");
			break;
		case 6: 
			printf("Enter Red component for the target color: \n");
			scanf("%d", &R_target);
			printf("Enter Green component for the target color: \n");
			scanf("%d", &G_target);
			printf("Enter Blue component for the target color: \n");
			scanf("%d", &B_target);
			printf("Enter threshold for the color difference: \n");
			scanf("%d", &threshold);
			printf("Enter factor for Red component in the target color: \n");
			scanf("%lf", &factor_r);
			printf("Enter factor for Green component in the target color: \n");
			scanf("%lf", &factor_g);
			printf("Enter factor for Blue component in the target color: \n");
			scanf("%lf", &factor_b);
			ColorFilter(R, G, B, R_target, G_target, B_target, threshold, factor_r, factor_g, factor_b);
			printf("\"Color Filter\" Operation Done!\n");
			break;
		case 7: 
			Sharpen(R,G,B);
			printf("\"Sharpen\" Operation Done!\n");
			break;
		case 8:	
			Edge(R,G,B);
			printf("\"Edge\" Operation Done!\n");
			break;
		case 9:
			printf("Please Enter the Border Width\n");
			scanf("%d", &border_width);
			printf("Please Enter the R value of the border color (0 to 255)\n");
			scanf("%d", &border_r);
			printf("Please Enter the G value of the border color (0 to 255)\n");
			scanf("%d", &border_g);
			printf("Please Enter the B value of the border color (0 to 255)\n");
			scanf("%d", &border_b);
			AddBorder(R, G, B, border_r, border_g, border_b, border_width);
			printf("Add border Operation done!\n");
			break;
		case 10:
			printf("Enter the number of posterization bits for R channel(1 to 8) :\n");
			scanf("%d", &rbits);
			printf("Enter the number of posterization bits for G channel(1 to 8):\n");
			scanf("%d", &gbits);
			printf("Enter the number of posterization bits for B channel(1 to 8):\n ");
			scanf("%d", &bbits);
			Posterize(R, G, B, rbits, gbits, bbits);
			break;
		case 11:
			printf("Please input noise percentage: \n");
			scanf("%d", &n);
			AddNoise(n, R, G, B);
			break;
		case 12:
			printf("Please input a file name to load: \n");
			scanf("%s", fname);
			printf("Please input x coordinate of the overlay image: \n");
			scanf("%d", &x_offset);
			printf("Please input y coordinate of the overlay image: \n");
			scanf("%d", &y_offset);
			Overlay(fname, R, G, B, x_offset, y_offset);
			printf("Overlay operation Done!\n");
			break;
		case 13: 
			printf("Please input choice of Tiltshift(1 for vertical line, 2 for horizontal line:\n");
			scanf("%d", &choice);
			if(choice == 1)
			{
			printf("Please input x offset\n");
			scanf("%d", &x_offset);
			}
			if(choice == 2)
			{
			printf("Please input y offset\n");
			scanf("%d", &y_offset);
			}
			/*if(choice != 1 || choice != 2)
			{
			printf("You did not input a correct choice, Aborted!\n");
			break;
			}*/
			printf("Please input a radius for your circle or line tilt shift\n");
			scanf("%d", &tiltr);
			Tiltshift(R, G, B, choice, x_offset, y_offset, tiltr);
		case 14 :
			AutoTest(R,G,B);
			return 0;
		case 15 : return 0;
		default: break;

	}
}

	return 0;
}



void PrintMenu()
{
	printf("1: Load a PPM image\n");
	printf("2: Save an image in PPM and JPEG format\n");
	printf("3: Change a color image to Black & White\n");
	printf("4: Flip an image vertically\n");
	printf("5: Mirror an image horizontally\n");
	printf("6: Color-Filter an image (Red, Green, or Blue)\n");
	printf("7: Sharpen an image\n");
	printf("8: Sketch the edge of an image\n");
	printf("9: BONUS Add Border to an image\n");
	printf("10: Posterize the image\n");
	printf("11: Add noise to an image\n");
	printf("12: Overlay an image\n");
	printf("13: Bonus, Surprise Filter\n");
	printf("14: AutoTest \n");
	printf("15: Exit\n");	
	printf("Please make your choice\n");
}



void	AutoTest(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
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

	ReadImage(fname, R, G, B);
	Posterize(R, G, B, 6, 7, 8);
	strcpy(sname, "poster");
	SaveImage(sname, R, G, B);
	printf("Posterize tested!\n\n");


	ReadImage(fname, R, G, B);
	AddNoise(10, R, G, B);
	strcpy(sname, "noise");
	SaveImage(sname, R, G, B);
	printf("Noise tested!\n\n");

	ReadImage(fname, R, G, B);
	Overlay("halloweenBat", R, G, B, 100, 150);
	strcpy(sname, "overlay");
	SaveImage(sname, R, G, B);
	printf("Overlay tested!\n\n");

	ReadImage(fname, R, G, B);
	Tiltshift(R, G, B, 1, 200, 200, 100);
	strcpy(sname, "surprise");
	SaveImage(sname, R, G, B);
	printf("Surprise tested!\n\n");







}

