/************************************************************************
**
** NAME:        gameoflife.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Justin Yokota - Starter Code
**				Rouge Lin
**
**
** DATE:        2024-01-26
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "imageloader.h"

uint8_t getState(Image *image, int row, int col){

	// Handle row and col: 
	//   the top row as adjacent to the bottom row
	// 	 and the left column as adjacent to the right column.
	if(row == 0) row = image->rows;
	else if(row == image->rows+1) row = 1;
	if(col == 0) col = image->cols;
	else if(col == image->cols+1) col = 1;

	// Check if the pixel is existed
	if(!image || !image->image || !image->image[(row - 1) * image->cols + col - 1]){
		fprintf(stderr, "Image is Null.\n");
    	exit(-1);
	}

	// Get the state of current pixel
	uint8_t retval;
	if((image->image[(row - 1) * image->cols + col - 1]->R == 255) && 
	(image->image[(row - 1) * image->cols + col - 1]->G == 255) &&
	(image->image[(row - 1) * image->cols + col - 1]->B == 255))
		retval = 1; // black(255,255,255) for 1
	else
		retval = 0; // white(0,0,0) for 0

	return retval;
}


//Determines what color the cell at the given row/col should be. This function allocates space for a new Color.
//Note that you will need to read the eight neighbors of the cell in question. The grid "wraps", so we treat the top row as adjacent to the bottom row
//and the left column as adjacent to the right column.
Color *evaluateOneCell(Image *image, int row, int col, uint32_t rule)
{
	// Check if the pixel is existed
	if(!image || !image->image || !image->image[(row - 1) * image->cols + col - 1]){
		fprintf(stderr, "Image is Null.\n");
    	exit(-1);
	}

	// Get the state of current pixel
	uint8_t _dead_0_or_live_1_ = getState(image, row, col);
	uint8_t alive_neighbors = 0;
	alive_neighbors += getState(image, row - 1, col - 1);
	alive_neighbors += getState(image, row - 1, col - 0);
	alive_neighbors += getState(image, row - 1, col + 1);
	alive_neighbors += getState(image, row - 0, col - 1);
	alive_neighbors += getState(image, row + 0, col + 1);
	alive_neighbors += getState(image, row + 1, col - 1);
	alive_neighbors += getState(image, row + 1, col - 0);
	alive_neighbors += getState(image, row + 1, col + 1);

	// Allocate space of return color
	Color* retval = (Color*)malloc(sizeof(Color));
	if(!retval){
		fprintf(stderr, "Out of memory.\n");
    	exit(-1);
	}

	// Calculate and assign the next state
	uint32_t _1_bit = 1;
	uint8_t next_state = ((rule >> (9 * _dead_0_or_live_1_ + alive_neighbors)) & _1_bit);
	if(next_state == 1)
		retval->R = retval->G = retval->B = 255;
	else
		retval->R = retval->G = retval->B = 0;

	return retval;
}

//The main body of Life; given an image and a rule, computes one iteration of the Game of Life.
//You should be able to copy most of this from steganography.c
Image *life(Image *image, uint32_t rule)
{
	// Check if the pixel is existed
	if(!image || !image->image){
		fprintf(stderr, "Image is Null.\n");
    	exit(-1);
	}

	// Allocate retval and image memory, and Copy head information
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
	retval->cols = image->cols;
	retval->rows = image->rows;


	// Extract the LSB of the B channel and write into the retval
	for(int i = 0; i < retval->cols * retval->rows; i++){
		int row = i / retval->cols + 1;
		int col = i % retval->cols + 1;
		retval->image[i] = evaluateOneCell(image, row, col, rule);
	}

	return retval;
}

/*
Loads a .ppm from a file, computes the next iteration of the game of life, then prints to stdout the new image.

argc stores the number of arguments.
argv stores a list of arguments. Here is the expected input:
argv[0] will store the name of the program (this happens automatically).
argv[1] should contain a filename, containing a .ppm.
argv[2] should contain a hexadecimal number (such as 0x1808). Note that this will be a string.
You may find the function strtol useful for this conversion.
If the input is not correct, a malloc fails, or any other error occurs, you should exit with code -1.
Otherwise, you should return from main with code 0.
Make sure to free all memory before returning!

You may find it useful to copy the code from steganography.c, to start.
*/
int main(int argc, char **argv)
{
	if(argc != 3){
		printf("    usage: ./gameOfLife filename rule\n");
		printf("    filename is an ASCII PPM file (type P3) with maximum value 255.\n");
		printf("    rule is a hex number beginning with 0x; Life is 0x1808.\n");
		exit(-1);
	}

	uint32_t rule = strtol(argv[2], NULL, 16); 
	Image* input = readData(argv[1]);
	Image* output = life(input, rule);
	
	freeImage(input);
	writeData(output);
	freeImage(output);

	return 0;
}
