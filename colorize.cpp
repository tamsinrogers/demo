 /**
 * Colorizing a pixel uisng threads 
 *
 * Tamsin Rogers
 * g++ -o colorizecpp -I. colorize.cpp ppmIO.cpp -lm
 * ./colorizecpp image.ppm 
 */
#include <stdio.h>
#include <stdlib.h>

#include "ppmIO.h"
#include <pthread.h>
#include "my_timing.h"
#include<chrono>
#include <iostream>
#define NUM_THREADS 4//you can change the amount of threads by changing the value
using namespace std; 

typedef struct {
		
    Pixel *src;
    int start; //start index for thread to work 
    int end ;//  ending index 
} PixelInfo; 


void *abc(void *pixelInfo) {

    PixelInfo *arr=(PixelInfo *) pixelInfo; //pointer to array 
	// process image
	for(int i=arr->start;i<arr->end;i++) {
		(arr->src)[i].r = (arr->src)[i].r > 128 ? (220+(arr->src)[i].r)/2 : (30+(arr->src)[i].r)/2;
		(arr->src)[i].g = (arr->src)[i].g > 128 ? (220+(arr->src)[i].g)/2 : (30+(arr->src)[i].g)/2;
		(arr->src)[i].b = (arr->src)[i].b > 128 ? (220+(arr->src)[i].b)/2 : (30+(arr->src)[i].b)/2;
	}

 
    pthread_exit(NULL);
}


int main(int argc, char *argv[] ) {
	

	Pixel *src;
	int rows, cols, colors;
	int i;

	double t1;
    double t2;

	// check usage
	if( argc < 2 ) {

		cout<< "Usage: <image filename>\n"<< argv[0];
		exit(-1);
	}
			
	// read image and check for errors
	src = ppm_read( &rows, &cols, &colors, argv[1] );
	if( !src ) {
		cout<<"Unable to read file \n"<< argv[1];

		exit(-1);
	}
	
	PixelInfo ti[NUM_THREADS];
    pthread_t thread[NUM_THREADS];

	int numPix=rows*cols;

	
	for(int i=0;i<NUM_THREADS;i++){
		ti[i].src=src;
		ti[i].start=(numPix/NUM_THREADS)*i;
		
		ti[i].end = (numPix/NUM_THREADS)*(i+1);
		


	}
	
	
	t1=get_time_sec();
	for (int i = 0; i < NUM_THREADS; i++) {
 		pthread_create(&thread[i], NULL, abc, &ti[i]);
 	}
	
	for (int i = 0; i < NUM_THREADS; i++) {
 		pthread_join(thread[i], NULL);
 	}
	
	t2=get_time_sec();	

    double time=t2-t1;
    cout<<"The time: "<<time;
    cout<<"\nNumber of threads used: "<<NUM_THREADS;
    

	// write out the image
	ppm_write( src, rows, cols, colors,(char *) "bold2.ppm" );
	
	free(src);
	

    return 0;

}

	
