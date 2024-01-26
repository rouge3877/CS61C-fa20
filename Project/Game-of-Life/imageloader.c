/************************************************************************
**
** NAME:        imageloader.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Dan Garcia  -  University of California at Berkeley
**              Copyright (C) Dan Garcia, 2020. All rights reserved.
**              Justin Yokota - Starter Code
**				Rouge Lin
**
**
** DATE:        2024-01-26
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include "imageloader.h"

//Opens a .ppm P3 image file, and constructs an Image object. 
//You may find the function fscanf useful.
//Make sure that you close the file with fclose before returning.
Image *readData(char *filename) 
{
	// allocate retval
	Image* retval = (Image*)malloc(sizeof(Image));
	retval->image = NULL;
	if(!retval){
    	fprintf(stderr, "Out of memory.\n");
    	exit(-1);
	}

	// open Img file
	FILE* fp = fopen(filename, "r");
	if(!fp){
		free(retval);
    	fprintf(stderr, "Open file failed.\n");
    	exit(-1);
	}

	// read header and check format
	char format[8];
	int bits_length;
	if((fscanf(fp, "%s %d %d %d", format, &(retval->cols), &(retval->rows), &bits_length))!=4){
		free(retval);
		fclose(fp);
		fprintf(stderr, "Error when read file.\n");
    	exit(-1);
	}
	if(strcmp(format, "P3")||(bits_length!=255)){
		free(retval);
		fclose(fp);
		fprintf(stderr, "Error file format.\n");
    	exit(-1);
	}

	// allocate image memory and read pixels by pixels
	retval->image = (Color**)calloc(retval->cols * retval->rows, sizeof(Color*));
	if(!retval->image){
		free(retval);
		fclose(fp);
		fprintf(stderr, "Out of memory.\n");
    	exit(-1);
	}
	for(int i = 0; i < retval->cols * retval->rows; i++){
		retval->image[i] = (Color*)calloc(3, sizeof(Color));
		if(!retval->image[i]){
			for(int j = 0; j < i; j++)
				free(retval->image[j]);
			free(retval->image);
			free(retval);
			fclose(fp);
			fprintf(stderr, "Out of memory.\n");
			exit(-1);
		}
		if(fscanf(fp, "%" SCNu8 " %" SCNu8 " %" SCNu8" ", &(retval->image[i]->R), &(retval->image[i]->G), &(retval->image[i]->B))!=3){
			for(int j = 0; j < i+1; j++)
				free(retval->image[j]);
			free(retval->image);
			free(retval);
			fclose(fp);
			fprintf(stderr, "Error when read file.\n");
			exit(-1);		
		}
	}

	fclose(fp);
	return retval;
}

//Given an image, prints to stdout (e.g. with printf) a .ppm P3 file with the image's data.
void writeData(Image *image)
{
	// header
	fprintf(stdout, "P3\n%u %u\n255\n", image->cols, image->rows);

	// the actual pixels in the image
	for(int i = 0; i < image->cols * image->rows; i++){
		fprintf(stdout, "%3" PRIu8 " %3" PRIu8 " %3" PRIu8 , image->image[i]->R, image->image[i]->G, image->image[i]->B);
		if((i >= image->cols - 1) && ((i + 1) % image->cols == 0))
			fprintf(stdout, "\n");
		else
			fprintf(stdout, "   ");
	}

	return;
}

//Frees an image
void freeImage(Image *image)
{
	if(!image)
		;
	else if(!image->image)
		free(image);
	else{
		for(int i = 0; i < image->cols * image->rows; i++){
			if(image->image[i])
				free(image->image[i]);
		}
		free(image->image);
		free(image);
	}

	return;
}