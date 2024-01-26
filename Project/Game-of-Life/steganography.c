/************************************************************************
**
** NAME:        steganography.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Dan Garcia  -  University of California at Berkeley
**              Copyright (C) Dan Garcia, 2020. All rights reserved.
**				Justin Yokota - Starter Code
**				Rouge Lin
**
** DATE:        2024-01-26
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "imageloader.h"

//Determines what color the cell at the given row/col should be. This should not affect Image, and should allocate space for a new Color.
Color *evaluateOnePixel(Image *image, int row, int col)
{
	// Check if the pixel is existed
	if(!image || !image->image || !image->image[(row - 1) * image->cols + col - 1]){
		fprintf(stderr, "Image is Null.\n");
    	exit(-1);
	}

	// Allocate space of return color
	Color* retval = (Color*)malloc(sizeof(Color));
	if(!retval){
		fprintf(stderr, "Out of memory1.\n");
    	exit(-1);
	}

	// Judge the least significant bit of the pixel’s B value
	uint8_t B_val = image->image[(row - 1) * image->cols + col - 1]->B;
	uint8_t check = 0b00000001;
	if((check & B_val) == check){ // to be white, we made that bit a 1
		retval->R = retval->G = retval->B = 255;
	}else{ // to be black, we made that bit a 0
		retval->R = retval->G = retval->B = 0;
	}

	return retval;
}

//Given an image, creates a new image extracting the LSB of the B channel.
Image *steganography(Image *image)
{
	// Check if the pixel is existed
	if(!image || !image->image){
		fprintf(stderr, "Image is Null.\n");
    	exit(-1);
	}

	// Allocate retval and image memory
	Image* retval = (Image*)malloc(sizeof(Image));
	retval->image = NULL;
	if(!retval){
    	fprintf(stderr, "Out of memory2.\n");
    	exit(-1);
	}
	retval->image = (Color**)calloc(image->cols * image->rows, sizeof(Color*));
	if(!retval->image){
		free(retval);
		fprintf(stderr, "Out of memory3.\n");
    	exit(-1);
	}

	// Copy head information
	retval->cols = image->cols;
	retval->rows = image->rows;

	// Extract the LSB of the B channel and write into the retval
	for(int i = 0; i < retval->cols * retval->rows; i++){
		int row = i / retval->cols + 1;
		int col = i % retval->cols + 1;
		retval->image[i] = evaluateOnePixel(image, row, col);
	}

	return retval;
}

/*
Loads a file of ppm P3 format from a file, and prints to stdout (e.g. with printf) a new image, 
where each pixel is black if the LSB of the B channel is 0, 
and white if the LSB of the B channel is 1.

argc stores the number of arguments.
argv stores a list of arguments. Here is the expected input:
argv[0] will store the name of the program (this happens automatically).
argv[1] should contain a filename, containing a file of ppm P3 format (not necessarily with .ppm file extension).
If the input is not correct, a malloc fails, or any other error occurs, you should exit with code -1.
Otherwise, you should return from main with code 0.
Make sure to free all memory before returning!
*/
int main(int argc, char **argv)
{
	Image* input = readData(argv[1]);
	Image* output = steganography(input);
	freeImage(input);
	writeData(output);
	freeImage(output);
	return 0;
}
