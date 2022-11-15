#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>

char*  ReadCommand()
{
	char* command = malloc(sizeof(char) * 10);  // to do: malloc but no free.. where should we free?
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
		int code = execl(path,command , NULL);
		if (code == -1)
		{
			char error_message[] = "Command does not exist!";
			write(pipes[1], error_message ,strlen(error_message) + 1);
			_exit(0);
		} 	
	}
	else
	{
		
		waitpid(-1,NULL,0);
		char foo[500];	
		memset(foo,0,sizeof(foo)); // clears buffer
		int size = read(pipes[0],foo, sizeof(foo));
		printf("%s\n", foo);            
	}
}



int main()
{
	
	printf("%s\n","CSE 4300 PROJECT");
	printArt();
	char **history = malloc(sizeof(char*)*sizeof(char*));
	int num_commands = 0;
	printf("%s\n\n\n","Created by: Matt Beauvais & Jan Feyen");
	while(1)
	{
		printf("\n%s", "> ");
		char* command = ReadCommand();
		history[num_commands] = command;
		num_commands++;
		if (!strcmp(command,"exit"))
		{
			free(command);
			break;
		}
		else if(!strcmp(command,"history"))
		{
			for(int i = 0; i < num_commands - 1; ++i) 
				printf("%s\n",history[i]);
		}
		else
			ExecuteCommand(command);
		free(command);
		
		
	}
		free(history);
}






