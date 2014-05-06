#ifndef Advanced_H
#define Advanced_H


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "Constants.h"
#include "FileIO.h"


void            Posterize(unsigned char R[WIDTH][HEIGHT],
		 unsigned char G[WIDTH][HEIGHT],
		 unsigned char B[WIDTH][HEIGHT], 
		 unsigned int rbits,
		 unsigned int gbits,
		 unsigned int bbits
	);

void            AddNoise(int n, unsigned char R[WIDTH][HEIGHT], 
		unsigned char G[WIDTH][HEIGHT], 
		unsigned char B[WIDTH][HEIGHT]);

void            Overlay(char fname [SLEN],
		unsigned char R[WIDTH][HEIGHT], 
		unsigned char G[WIDTH][HEIGHT], 
		unsigned char B[WIDTH][HEIGHT],
		unsigned int x_offset,
		unsigned int y_offset);
void   		Tiltshift(unsigned char R[WIDTH][HEIGHT],
		unsigned char G[WIDTH][HEIGHT],
		unsigned char B[WIDTH][HEIGHT],
		int choice,
		int x_offset, 
		int y_offset, 
		int tiltr);


#endif /* Advance.h */
