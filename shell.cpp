#include <sys/wait.h>
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
using namespace std;

string ReadCommand()
{
	string command;
	cin >> command;
	return command;
}


void printArt()
{
	cout << " _______  __   __  _______  ___      ___     "<< endl;
	cout << "|       ||  | |  ||       ||   |    |   |    "<< endl;
	cout << "|  _____||  |_|  ||    ___||   |    |   |    "<< endl;
	cout << "| |_____ |       ||   |___ |   |    |   |    "<< endl;
	cout << "|_____  ||       ||    ___||   |___ |   |___ "<< endl;
	cout << " _____| ||   _   ||   |___ |       ||       |"<< endl;
	cout << "|_______||__| |__||_______||_______||_______|"<< endl << endl;
}

// note: C++ provides a popen() command which handles the forking and exec for you
// we decided to not use this and do it manually for the sake of learning 
// i.e. this is the C style of doing this
void ExecuteCommand(string command)
{
	string commandcopy = command;
	const char *c1 = commandcopy.c_str();
	command = "/bin/" + command;
	const char * c = command.c_str();
	int pipes[2];
	pipe(pipes);
	pid_t pid = fork();
	if (pid == 0)
	{
		dup2(pipes[1],1);
		execl(c, c1, NULL);	
	}
	else
	{
		waitpid(-1,NULL,0);
		char foo[1024];
		read(pipes[0],foo, sizeof(foo));
		cout << foo << endl;
	}
	
}

int main()
{
	
	cout << "CSE 4300 PROJECT" << endl;
	printArt();
	cout << "Created by: Matt Beauvais & Jan Feyen" << endl << endl << endl;
	while(1)
	{
		cout << "> ";
		string command = ReadCommand();
		if (command == "exit")
			exit(0);
		else
			//cout << "notd yet implemented!" << endl;
			ExecuteCommand(command);
	}
}






