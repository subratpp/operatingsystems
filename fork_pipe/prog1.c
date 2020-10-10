/*
Program: Assignment 3, Question 1
Description: fork() child process and compute fibb series
Name: Subrat Prasad Panda
Roll: CS1913
*/


#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

//Mode for output, 1: extended; 0: minimal
#define DEBUG  0

int main(int argc, char* argv[]){
//  Extracting N and error checking for negative/invalid inputs
    if( argc != 2)
        printf("Provide Correct Command Line Arguments: ./a.out 5 \n"), exit(-1);
    int N = atoi(argv[1]);
    if (N < 0)
        printf("Negative number not allowed \n"), exit(-1);
    
    
    #if DEBUG == 1
        printf("Num: %d \n", N);
    #endif
    

    int pid = fork();
//  Code for Child process
    if (pid < 0) perror("Child Creation"), exit(-1);
    
    if (pid == 0){
        #if DEBUG == 1
            perror("Child Creation");
        #endif
        
        int n1 = 0, n2 = 1, next;
        for (int i = 0; i < N; i++){
            printf("%d ", n1);
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
    exit(1);
}