/*
Program: Assignment 3, Question 5
Description: System V commands for Shared Segment Memory information
Name: Subrat Prasad Panda
Roll: CS1913
*/

#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>

// DEBUG 1: Self test mode, DEBUG 0: Submission Mode
#define DEBUG 0

void main(int argc, char *argv[] )
{

//Use it for DEBUGGING >>> Generate the Segment ID to test the program
    key_t i;
    #if DEBUG == 1
    int shm;
    void *addr;
    i = ftok("/usr", 3);
    printf("Test (key)i:%x \n", i);
    shm = shmget(i, 8000, IPC_CREAT | 0666);
    addr = shmat(shm, NULL, 0);
    #endif

//Extract input data if Debug is 0
    #if DEBUG == 0
    if (argc != 2)
        printf("Provide Correct Command Line Arguments: ./a.out <segment ID> \n"), exit(-1);
    int shm = atoi(argv[1]);
    #endif

//Get the data from segment ID
    struct shmid_ds buf;
    i = shmctl(shm, IPC_STAT, &buf);

 // to exit in case of invalid ID
    printf("shmctl return: %d\n",i);
    if (i < 0)
        perror("Invalid ID"), exit(-1);

//Print Details
    printf("Segment ID: %d \n", shm);
    printf("Key: %x \n", buf.shm_perm.__key);
    printf("Mode:%u \n",buf.shm_perm.mode);
    printf("Owner UID:%d \n",buf.shm_perm.uid);
    printf("Size: %zu bytes\n", buf.shm_segsz);
    printf("Number of Attaches: %ld \n", buf.shm_nattch);
}