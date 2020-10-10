/*
Program: Assignment 3, Question 2
Description: fork() child process and compute fibb series using shared memory
Name: Subrat Prasad Panda
Roll: CS1913
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/shm.h>
#include <fcntl.h>

//Mode for output, 1: extended; 0: minimal
// add -lrt for compilation
#define DEBUG  0

//Data type to hold memory data
#define MAX_SEQUENCE 10
typedef struct{
    int *fib_sequence; //Used pointer instead of fixed sized array
    int sequence_size;
} shared_data;

int main(int argc, char* argv[]){
//  Extracting N and error checking for negative/invalid inputs
    if( argc != 2)
        printf("Provide Correct Command Line Arguments: ./a.out 5 \n"), exit(-1);
    int N = atoi(argv[1]);
    if (N <= 0)
        printf("Negative number or Zero not allowed \n"), exit(-1);
    if (N > MAX_SEQUENCE)
        printf("Exceeds max input value \n"), exit(-1);
    
    //Init the strucutre to hold shared data
    shared_data fib;
    fib.sequence_size = N;

    #if DEBUG == 1
        printf("Num: %d \n", fib.sequence_size);
    #endif

    const int SIZE = (N+1) * sizeof(int); //size in bytes
    const char *NAME = "FIBB";

    #if DEBUG == 1
        printf("SIZE: %d \n", SIZE);
    #endif

    int fd = shm_open(NAME, O_CREAT | O_RDWR, 0666);
    if (fd < 0)
        perror("shm_open()"), exit(-1);
    ftruncate(fd, SIZE);
    // Map the shared memory to Structure
    fib.fib_sequence = (int *)mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    #if DEBUG ==1
        printf("structure address mapping to: %p\n", fib.fib_sequence);
    #endif
        
    int pid = fork();
        //  Code for Child process
    if (pid < 0)
        perror("Child Creation"), exit(-1);

    if (pid == 0)
    {
        #if DEBUG == 1
            perror("Child Creation");
        #endif
        
        int n1 = 0, n2 = 1, next;
        for (int i = 0; i < fib.sequence_size; i++)
        {   
            #if DEBUG == 1
                printf("%d ", n1);
            #endif
            fib.fib_sequence[i] = n1;
            next = n1 + n2;
            n1 = n2;
            n2 = next;
        }
        printf("\n");
        return 0;
    }
// Code for parent process
    wait(NULL); //wait for child process to finish
    #if DEBUG == 1
        perror("Child process done");
    #endif
    for(int i = 0; i < N; i++)
        printf("%d ", fib.fib_sequence[i]);
    printf("\n");
    shm_unlink(NAME); //removes the fd from fd table
    exit(1);
}