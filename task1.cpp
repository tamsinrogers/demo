 /**
 * Sorts an array using parallism  
 *
 * Tamsin Rogers
 * g++ -o task1cpp task1.cpp
 * ./task1cpp
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include<chrono>
#include "my_timing.h"
#include <iostream>

#define NUM_THREADS 4 //you can change the amout of threads by changing this value 
#define arraySize 50
using namespace std; 

typedef struct {
    int *array;
    int start; //start index for thread to work 
    int count;//how many to go 
} ThreadInfo; 


int comparator(const void *a, const void *b)
{
   return(*(int*)a-*(int*)b);
  
}



void *abc(void *threadinfo) { //recursive so joins easily 
    ThreadInfo *arr=(ThreadInfo *) threadinfo; //pointer to array 

    if(arr->count <= arraySize/NUM_THREADS){
        
       qsort((void*) arr->array, arr->count,sizeof(int),comparator);
        
    }

    else{
        ThreadInfo ti[NUM_THREADS];
        pthread_t thread[NUM_THREADS]; // use 2 of the threads to count N numbers

        for (int i=0;i<NUM_THREADS;i++){ //handles n number of threads! 
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





int main(int argc, char *argv[]){

    double t1;
    double t2;


    int myArray[arraySize]; //creating an array 
    
    srand(0); //random number generator 
    int i;
    for (i = 0; i <arraySize; i++) {
        myArray[i] = rand()%10;
    }

    cout<<"Printing the unsorted array: ";
    for (int i=0; i<arraySize;i++){
        cout<<" "<<myArray[i];
        
    }
    cout<<"\n";

    
    ThreadInfo ti;
    pthread_t thread;

    ti.array=myArray;
    ti.start=0;
    ti.count=arraySize;

    t1=get_time_sec();
    
    pthread_create(&thread,NULL,abc,&ti); //creating the thread 
    
    
    pthread_join(thread,NULL);
    
    t2=get_time_sec();

    double time=t2-t1;
    cout<<"The time that it took to sort the array: "<<time<<"\n";
    cout<<"The number of threads used: "<<NUM_THREADS<<"\n";
    cout<<"Printing the sorted array: ";
    for (int i=0; i<arraySize;i++){
        cout<<" "<<myArray[i];
    }
    
    return 0;

    
    
}
    

