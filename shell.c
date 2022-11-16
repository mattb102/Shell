#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>

char* wordLis[20];

char** parseString (char* str)
{
	char* args = strtok(str, " ");
	int i = 0;
	int j = 0;
	int k = 0;
	char** argsList = malloc(500);
	for(int i = 0; i < strlen(args); ++i)
	{
		if(str[i] != '\0')
			argsList[j][k] = args[i];
		else
		{
			j++;
			k = 0;
		}
	}
	argsList[j+1] = NULL;
	return argsList;
	/*
	int i = 0;
	int j =0;
	int k = 0;
	while (str[i] != '\0')
	{
		if(str[i] != 32)
		{
			wordLis[j][k] = str[i];
			k++;

		}
		else
		{
			wordLis[j][k] = '\0';
			j++;
			k = 0;
		}
		i++;
	}
	//wordLis[j][k] = '\0';
	//wordLis[j + 1] = NULL;
	//printf("%s\n%s\n",wordLis[0], wordLis[1]);
	*/
}

char*  ReadCommand()
{
	char* command = malloc(sizeof(char) * 10);
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

// note: C provides a popen() and also a system() command which handles the forking and exec for you
// we decided to not use this and do it manually for the sake of learning 
void ExecuteCommand(char* command)
{
	char** argsList = parseString(command);
	char path[30];
	sprintf(path,"/usr/bin/%s",command);
	int pipes[2];
	pipe(pipes);
	pid_t pid = fork();
	if (pid == 0)
	{
		dup2(pipes[1],1);
		int code = execv(path, argsList);
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
		write(pipes[1], "\0", 1);	
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
			break;
		}
		else if(!strcmp(command,"history"))
		{
			for(int i = 0; i < num_commands - 1; ++i) 
				printf("%s\n",history[i]);
		}
		else
			//parseString(command);
			ExecuteCommand(command);
		
		
	}
		for(int i = 0; i < num_commands; ++i)
			free(history[i]);
		free(history);
}






