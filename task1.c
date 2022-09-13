 /**
 * Sorting an array using parallism  
 *
 * Tamsin Rogers
 * gcc -o task1 task1.c
 * ./task1
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "my_timing.h"
#define NUM_THREADS 10 						// set number of threads here


typedef struct 
{
    int *array;
    int start; 								// thread start index
    int count;								
} ThreadInfo; 


int comparator(const void *a, const void *b)
{
   return(*(int*)a-*(int*)b);
}

void *abc(void *threadinfo) 
{ //recursive so joins easily 
    ThreadInfo *arr=(ThreadInfo *) threadinfo; //pointer to array 

    if(arr->count <= arraySize/NUM_THREADS)
    {
       qsort((void*) arr->array, arr->count,sizeof(int),comparator);	// quicksort
    }

    else
    {
        ThreadInfo ti[NUM_THREADS];
        pthread_t thread[NUM_THREADS]; 									// use 2 of these threads to keep track of the N numbers

        for (int i=0;i<NUM_THREADS;i++)
        { 																// this part handles N number of threads
            ti[i].array = arr->array;
            ti[i].start = arr->start+(arr->count/2);
            ti[i].count = arr->count/NUM_THREADS;
        }
        
        qsort((void*) arr->array, arr->count,sizeof(int),comparator);
        pthread_create(&thread[0], NULL, abc, &ti[0]);
        pthread_join(thread[0], NULL);
    }

    pthread_exit(NULL);
}


int main(int argc, char *argv[])
{

    double t1;
    double t2;

    int myArray[arraySize]; 					// create an array 
    
    srand(0); 									// random number generator 
    int i;
    
    for (i = 0; i <arraySize; i++) 
    {
        myArray[i] = rand()%10;
    }
    
    for (int i=0; i<arraySize;i++)
    {
        printf("%d ",myArray[i]);
    }
    
    printf("\n");

    ThreadInfo ti;
    pthread_t thread;

    ti.array = myArray;
    ti.start = 0;
    ti.count = arraySize;

    t1=get_time_sec();
    
    pthread_create(&thread,NULL,abc,&ti); 		// create thread 
    
    pthread_join(thread,NULL);
    
    t2=get_time_sec();

    double time=t2-t1;
    printf("%f",time);
    
    for (int i=0; i<arraySize;i++)
    {
        printf("%d ",myArray[i]);
    }
    
    return 0;
}
    

