/*
Program: Assignment 3, Question 3
Description: Ordinary pipe to reverse case of string.
Name: Subrat Prasad Panda
Roll: CS1913
*/

#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <ctype.h>

#define BUFFER 25
#define READ_END 0
#define WRITE_END 1

int main(){
   
    char wrt_msg[BUFFER] = "Hello THere"; //Please change the size of BUFFER according to string length
    char read_msg[BUFFER];

    int fd[2];
    int pid;

    if(pipe(fd) == -1)
        perror("Pipe failed"), exit(-1);
    
    // Write string to pipe
    write(fd[WRITE_END], wrt_msg, BUFFER);
    
    
    pid = fork();

    if (pid < 0)
        perror("Child Process"), exit(-1);
    
    //program for child process
    if (pid == 0)
    {
        read(fd[READ_END], read_msg, BUFFER);
        char rev[BUFFER];
        int len = strlen(read_msg), i;
        char temp;
        for(i = 0; i <= len; i++){ //loop to reverse the case in string by looping over each char
            temp = read_msg[i];
            if(islower(temp)) rev[i] = toupper(temp);
            else rev[i] = tolower(temp);
        }
        //printf("Child Send: %s\n", rev);
        write(fd[WRITE_END], rev, BUFFER);
        close(fd[READ_END]);
        close(fd[WRITE_END]);
        return 0;
    }
    wait(NULL); //Wait till the child process
    read(fd[READ_END], read_msg, BUFFER);
    printf("Resulting String: %s\n",read_msg);
    close(fd[READ_END]);
    close(fd[WRITE_END]);
    return 0;
}