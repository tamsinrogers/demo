CS333 - Project #8 - README
Tamsin Rogers
11/23/21

Project 8
├── bold.ppm
├── colorize
├── colorize.c
├── image.ppm
├── my_timing.h
├── ppmIO.c
├── ppmIO.h
├── task1
└── task1.c


Run and build configuration for C:
macOS Big Sur 11.5.2 - Apple LLVM version 12.0.5 (clang-1205.0.22.11)

Description for each subsection:
C:

This is a C programming task. 

Project 8 incorporates parallel programing using threads that breaks tasks into individual sections 
to make them run more efficiently. Task 1 implements threads that break an array into multiple threads 
and runs them at the same time.  The result is the sorted array.  The array is divided into equal parts 
that each sort themselves recursively at the same time. The global NUM_THREADS variable that is a gobal 
controls the number N to be used for making arrays arrays. In this part of the project, an array of 50 
random integers was created.  These integers are sorted using quicksort.  I recording the time that it took
to merge and sort the below array.

The unsorted array:
0 1 5 2 1 1 0 7 8 1 4 0 6 6 0 8 9 5 4 4 6 3 3 4 7 1 6 7 3 9 0 1 4 8 4 6 1 6 0 4 2 0 7 7 6 0 7 2 8 6 

The sorted array:
0 0 0 0 0 0 0 1 1 1 1 1 1 1 2 2 2 3 3 3 4 4 4 4 4 4 4 5 5 6 6 6 6 6 6 6 6 7 7 7 7 7 7 8 8 8 8 9 9 

Runtime for 1, 2, 4, and 10 threads. Task1.c has the ability to handle N threads (the number of threads 
is defined in line 13). 

1 thread: 0.0025450
2 threads: 0.0015500
4 threads :0.0022110
10 threads: 0.0016690

We can see that this result follows Amdahls Law because the speed eventually plateaus (at 2 threads).

Compile: gcc -o task1 task1.c
Run: ./task1


Task 2 incorporates a pixel wise operator using parallelism. This part relies on threads to speed 
up the computation time. In this case, we made the picutre bolder. 

Runtime for 1,2,4, and 10 threads:

1 Thread: 0.032792
2 Threads: 0.014351
4 Threads: 0.010771
10 threads: 0.009309

We can see that the runtime increases as the number of threads increases, so parallelism is more efficient.

I used the bolded picture bold.ppm for this part.


compile: gcc -o colorize -I. colorize.c ppmIO.c -lm
run:  ./colorize image.ppm 

** EXTENSIONS **

In tasks 1 and 2 of the C part of this project, I wrote the programs to handle N threads, which can be redefined in line 13 with the NUM_THREADS variable.



