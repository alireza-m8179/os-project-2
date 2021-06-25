#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

// text colors
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#define BUFFER_SIZE 64 
#define ARGS_SIZE 16

// Getting input from user and save into buffer
int getInput(char *str)
{

	char *buffer;
	buffer = readline(ANSI_COLOR_GREEN "FarabiShell>>> " ANSI_COLOR_RESET);
	// printf("buffer: %s\n", buffer); 
	if (strlen(buffer) != 0)
	{
	add_history(buffer);
	strcpy(str, buffer);
	return 0;
	} 
	else
	{
	return 1;
	}
}

// helloShell built-in command
void hello() 
{
	printf(ANSI_COLOR_CYAN "Hello, welcome, nice to meet you!\n" ANSI_COLOR_RESET);
	// another features...
}

// cd built-in command
int changeDirectory(char *path) 
{
	char s[100];

	if (chdir(path) != 0) {
		perror("chdir() is failed!");
	}
	
	// printing current working directory
    printf(ANSI_COLOR_BLUE "%s\n" ANSI_COLOR_RESET, getcwd(s, 100));

	return 0;
}

int main() 
{	
	char *clear[] = {"clear", NULL};
	
	while (1) {

		pid_t pid;
		char *args[ARGS_SIZE];
		char str[BUFFER_SIZE];
		getInput(str);
		
		char *token = strtok(str, " ");
		int counter = 0;
		
		while (token != NULL)
		{
			args[counter++] = token;
			token = strtok(NULL, " ");
		}
		args[counter] = NULL;
				
		if (strcmp(args[0],"byeShell") != 0) 
		{
			if (strcmp(args[0],"helloShell") == 0) 
			{
				hello();
			} 
			else if (strcmp(args[0],"cd") == 0) 
			{
				// cd os992 : args[0] = cd, args[1] = path (e.g, os992)
				changeDirectory(args[1]); // passing path to the function
			} 
			else 
			{
				// TODO e,g. fork
				
				pid = fork();	
				if (pid < 0)
				{
					// failure 
					printf("error!");
				} 
				else if (pid == 0)
				{
					// pid process
					execvp(args[0], args);
				}
				else if (pid > 0)
				{
					// parent process
					wait(NULL);
				}
			}
		} 
		else 
		{
			// exit from loop
			printf(ANSI_COLOR_RED "See you later! bye...\n" ANSI_COLOR_RESET);
			return 0;
		}
	}	
	
}
