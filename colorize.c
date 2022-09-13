 /**
 * Coloriezes a pixel using threads 
 *
 * Tamsin Rogers
 * gcc -o colorize -I. colorize.c ppmIO.c -lm
 * ./colorize image.ppm 
 */
#include <stdio.h>
#include <stdlib.h>

#include "ppmIO.h"
#include <pthread.h>
#include "my_timing.h"


#define NUM_THREADS 10							// change # of threads here


typedef struct {
		
    Pixel *src;
    int start; 									// start index for thread 
    int end ;									// end index for thread
} PixelInfo; 


void *abc(void *pixelInfo) {

    PixelInfo *arr=(PixelInfo *) pixelInfo; 	// pointer to array 
    
	
	for(int i=arr->start;i<arr->end;i++) 		// processes image
	{
		(arr->src)[i].r = (arr->src)[i].r > 128 ? (220+(arr->src)[i].r)/2 : (30+(arr->src)[i].r)/2;
		(arr->src)[i].g = (arr->src)[i].g > 128 ? (220+(arr->src)[i].g)/2 : (30+(arr->src)[i].g)/2;
		(arr->src)[i].b = (arr->src)[i].b > 128 ? (220+(arr->src)[i].b)/2 : (30+(arr->src)[i].b)/2;
	}

 
    pthread_exit(NULL);
}


int main(int argc, char *argv[] ) 
{
	Pixel *src;
	int rows, cols, colors;
	int i;

	double t1;
    double t2;

	
	if( argc < 2 ) 										// check usage statement
	{
		printf("Usage: %s <image filename>\n", argv[0]);
		exit(-1);
	}
			
	
	src = ppm_read( &rows, &cols, &colors, argv[1] );	// read image and check for errors
	if( !src ) 
	{
		printf("Unable to read file %s\n", argv[1]);
		exit(-1);
	}
	
	PixelInfo ti[NUM_THREADS];
    pthread_t thread[NUM_THREADS];

	int numPix=rows*cols;

	
	for(int i=0;i<NUM_THREADS;i++)
	{
		ti[i].src=src;
		ti[i].start=(numPix/NUM_THREADS)*i;
		ti[i].end = (numPix/NUM_THREADS)*(i+1);
	}
	
	t1=get_time_sec();
	
	for (int i = 0; i < NUM_THREADS; i++) 
	{
 		pthread_create(&thread[i], NULL, abc, &ti[i]);
 	}
	
	for (int i = 0; i < NUM_THREADS; i++) 
	{
 		pthread_join(thread[i], NULL);
 	}
	
	t2=get_time_sec();	

    double time=t2-t1;
    printf("%f",time);

	ppm_write( src, rows, cols, colors, "bold.ppm" );	// write image
	
	free(src);
	
    return 0;

}

	
