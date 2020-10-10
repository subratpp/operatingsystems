/*
Program: Assignment 3, Question 4
Description: Copy file using ordinary pipe
Name: Subrat Prasad Panda
Roll: CS1913
*/

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

#define BUFFER 25
#define READ_END 0
#define WRITE_END 1

int main(int argc, char *argv[]){
    char data[BUFFER] = {0};
    int fd[2];
    int pid,l;
    // Extracting input and output file name
    if (argc != 3)
        printf("Provide Correct Command Line Arguments: ./a.out in.txt out.txt \n"), exit(-1);
    
    int fd_input = open(argv[1], O_RDONLY);
    if (fd_input == -1)
        perror("File Open Status"), exit(-1);

    if (pipe(fd) == -1)
        perror("Pipe failed"), exit(-1);
    //Write data to pipe
    while((l=read(fd_input,data,BUFFER)) > 0)
        write(fd[WRITE_END], data, l);
        
    close(fd[WRITE_END]); //Close file descriptor
    close(fd_input);
    
    pid = fork(); 
    if (pid < 0)
        perror("Child Process"), exit(-1);
    
    //program for child process
    if (pid == 0)
    {
        int fd_output = open(argv[2], O_CREAT | O_RDWR | O_TRUNC, 0666);
        if (fd_output == -1)
            perror("File Open Status"), exit(-1);
        
        //write data to file from pipe
        while ((l=read(fd[READ_END], data, BUFFER)) > 0)
            write(fd_output, data, l);
        
        close(fd_output);
        close(fd[READ_END]);   
        printf("Copying Done! \n");    
        return 0;
    }
    
    close(fd[READ_END]);
    return 0;
}