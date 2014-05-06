#ifndef FILE_IO_H
#define FILE_IO_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Constants.h"

int ReadImage(
		char Filename[SLEN],
		unsigned char R[WIDTH][HEIGHT],
		unsigned char G[WIDTH][HEIGHT],
		unsigned char B[WIDTH][HEIGHT]);
int SaveImage(
		char Filename[SLEN],
		unsigned char R[WIDTH][HEIGHT],
		unsigned char G[WIDTH][HEIGHT],
		unsigned char B[WIDTH][HEIGHT]);

#endif /* FILE_IO_H */
/*EOF FileIO.h*/
