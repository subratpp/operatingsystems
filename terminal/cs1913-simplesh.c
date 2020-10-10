/*
================================
Assignment 4, simlplesh terminal
Name: Subrat Prasad Panda
Roll: CS1913
================================
*/
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <stdlib.h>
#include <string.h>


#define MAX_SIZE 15
struct hist
{
	int slno;
	char cmd[MAX_SIZE];
};
extern char **environ;	
char *pwd;	// present working directory pointer
enum commands {_def, _clear, _env, _cd, _pwd, _mkdir, _rmdir, _ls1, _ls2, _history1, _history2, _ex};


#define clear() printf("\033[H\033[J") //clears console screen
#define pwd() pwd = getcwd(NULL, 0)	//get present working directory created on heap
#define print_pwd() printf("%s> ", pwd)	//print path>
#define clear_pwd()		\
	do {                    \
		free(pwd);	\
		pwd = NULL;     \
	} while(0)	// clear pwd data from heap


void print_env() // Print the environment variables
{
	int i = 0;
	char *s = *environ;
	for (; s; i++){
		printf("%s\n", s);
		s = *(environ + i);
	}	
}


void print_ll(int d) //print dir files
{
	struct dirent *de; // Pointer for directory entry, no free required
	DIR *dr = opendir(".");
	if (dr == NULL)
		perror("open dir error");
	struct stat info;
	struct passwd *user; 
	struct group *grp; 
	while ((de = readdir(dr)) != NULL){
		if (d == 1){
			stat(de->d_name, &info);
			printf("%s\t", de->d_name);
			printf((S_ISDIR(info.st_mode)) ? "d" : "-");
			printf((info.st_mode & S_IRUSR) ? "r" : "-");
			printf((info.st_mode & S_IWUSR) ? "w" : "-");
			printf((info.st_mode & S_IXUSR) ? "x" : "-");
			printf((info.st_mode & S_IRGRP) ? "r" : "-");
			printf((info.st_mode & S_IWGRP) ? "w" : "-");
			printf((info.st_mode & S_IXGRP) ? "x" : "-");
			printf((info.st_mode & S_IROTH) ? "r" : "-");
			printf((info.st_mode & S_IWOTH) ? "w" : "-");
			printf((info.st_mode & S_IXOTH) ? "x" : "-");
			user = getpwuid(info.st_uid); // don't free it
			grp = getgrgid(info.st_gid);
			printf("\t%s\t%s\t%ld\t%s", user->pw_name, grp->gr_name,
				info.st_size, ctime(&info.st_mtime));
		} else{
			printf("%s\t", de->d_name);
		}
	}
	closedir(dr);
}



int main(){
	//--------------Initiate history file and scan the command
	FILE *fptr = fopen(".hst", "a+");
	if (!fptr){
		perror("file opening failed");
		exit(-1);
	}

	struct hist icmd;	//previous command from .history binary log
	char *token, *pathname;
	enum commands command;
	int h_offset;
	
	//---------------Initiate Sl Num Count---------------------
	fseek(fptr, 0, SEEK_END); //move to the end
	if (ftell(fptr) > 0){
		fseek(fptr, -sizeof(struct hist), SEEK_CUR);
		fread(&icmd, sizeof(struct hist), 1, fptr);	//previous sl number
	} else icmd.slno = 0;	// previous sl. number start from 0
	
	clear();
	printf(">>>>>\tWelcome to Simplesh\t<<<<<\n\n");
	pwd();
	
	
	while (1){
		print_pwd();
		fgets(icmd.cmd, MAX_SIZE, stdin);
		icmd.slno++; 
		fwrite(&icmd, sizeof(struct hist), 1, fptr);//write the command to log
		
		//-------------------EXTRACT COMMAND NuMBER----------------
		command = _def; //default value for no commands
		token = strtok(icmd.cmd, " ");
		if (strcmp(token, "\n") == 0)	goto action;
		if (strcmp(token, "clear\n") == 0 || strcmp(token, "clear") == 0) {command = _clear; goto action;}
		if (strcmp(token, "env\n") == 0 || strcmp(token, "env") == 0) {command = _env; goto action;}
		if (strcmp(token, "cd") == 0) {command = _cd; goto action;}
		if (strcmp(token, "pwd\n") == 0 || strcmp(token, "pwd") == 0) {command = _pwd; goto action;}
		if (strcmp(token, "mkdir") == 0) {command = _mkdir; goto action;}
		if (strcmp(token, "rmdir") == 0) {command = _rmdir; goto action;}
		if (strcmp(token, "ls\n") == 0) {command = _ls1; goto action;}
		if (strcmp(token, "ls") == 0) {command = _ls2; goto action;}
		if (strcmp(token, "history\n") == 0) {command = _history1; goto action;}
		if (strcmp(token, "history") == 0) {command = _history2; goto action;}
		if (strcmp(token, "exit\n") == 0 || strcmp(token, "exit") == 0) command = _ex;
		
		
		
		action:
		//----------------------- ACTION --------------------
		switch(command){
		case _clear: 
			clear();
			break;
		case _env: 
			print_env();
			break;
		case _cd: 
			pathname = strtok(NULL, "\n");
			if (pathname){
				if (chdir(pathname) < 0){
					perror("dir not changed");
				} else{
					clear_pwd(); //clear previous allocation
					pwd();
				}
			} else
				perror("NULL String");
			
			break;
		case _pwd: 
			clear_pwd(); //clear previous allocation
			pwd();
			printf("%s\n", pwd);
			break;
		case _mkdir: 
			pathname = strtok(NULL, "\n");
			if (pathname){
				if (mkdir(pathname, 0777) < 0)
					perror("dir couldn't created");
			} else
				perror("null arguments");
			break;
		case _rmdir: 
			pathname = strtok(NULL, "\n");
			if (pathname){
				if (rmdir(pathname) < 0)
					perror("remove dir failed");
			} else
				perror("null arguments");
			break;
		case _ls1: 
			print_ll(0);
			printf("\n");
			break;
		case _ls2: 
			if (token = strtok(NULL, "\n")){
				if (strcmp(token, "-l") == 0)
					print_ll(1);
				else
					perror("No such commands");
			} else{
				printf("null arguments, run> ls\n");
				print_ll(0);
				printf("\n");
			}
			break;
		case _history1:
			fseek(fptr, 0, SEEK_SET);
			while(fread(&icmd, sizeof(struct hist), 1, fptr) != 0)
				printf("%d %s", icmd.slno, icmd.cmd);
			break;
		case _history2: 
			if (token = strtok(NULL, "\n"))
				h_offset = atoi(token);
			else{
				perror("null arguments, enter a number");
				break;
			}
			fseek(fptr, -sizeof(struct hist) * h_offset, SEEK_END);
			while(fread(&icmd, sizeof(struct hist), 1, fptr) != 0)
				printf("%d %s", icmd.slno, icmd.cmd);
			break;
		case _ex: 
			fclose(fptr); //clear all the variables
			clear_pwd();
			printf(">>>>>\tBye!\t<<<<<\n");
			exit(1);
			break;
		default: // for invalid commands
			printf("invalid command! try again!\n");
			break;
		}
	}
}