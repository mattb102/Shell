#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
char*  ReadCommand()
{
	char* command = malloc(sizeof(char) * 20);  // to do: malloc but no free.. where should we free?
	scanf(" %[^\n]s",command);
	return command;
}


void printArt()
{
	printf("%s\n"," _______  __   __  _______  ___      ___     ");
	printf("%s\n","|       ||  | |  ||       ||   |    |   |    ");
	printf("%s\n","|  _____||  |_|  ||    ___||   |    |   |    ");
	printf("%s\n","| |_____ |       ||   |___ |   |    |   |    ");
	printf("%s\n","|_____  ||       ||    ___||   |___ |   |___ ");
	printf("%s\n"," _____| ||   _   ||   |___ |       ||       |");
	printf("%s\n","|_______||__| |__||_______||_______||_______|");
}

// note: C++ provides a popen() command which handles the forking and exec for you
// we decided to not use this and do it manually for the sake of learning 
// i.e. this is the C style of doing this
void ExecuteCommand(char* command)
{
	char *args[] = {command, NULL};
	char path[10];
	sprintf(path,"/bin/%s",command);
	int pipes[2];
	pipe(pipes);
	pid_t pid = fork();
	if (pid == 0)
	{
		dup2(pipes[1],1);
		execl(path,command , NULL);  //to do: make this work for any shell command (and allow for argument)
	}
	else
	{
		waitpid(-1,NULL,0);
		char foo[1024];
		read(pipes[0],foo, sizeof(foo));
		printf("%s\n", foo);            
		memset(foo,0,sizeof(foo)); // clears buffer
	}
	
}



int main()
{
	
	printf("%s\n","CSE 4300 PROJECT");
	printArt();
	char *history[100];
	printf("%s\n\n\n","Created by: Matt Beauvais & Jan Feyen");
	while(1)
	{
		printf("%s", "> ");
		char* command = ReadCommand();
		strcpy(history, command);
		if (!strcmp(command,"exit"))
			exit(0);
		else if(!strcmp(command,"history"))
			// to do: print history... NOTE: this should also be turned into a function later on so we dont have chains of conditionals for commands
		else
			ExecuteCommand(command);
	}
}






