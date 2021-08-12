/*
 * Lambda is a C++ based shell program to learn more complicated Linux and to use for my bigger shell
 * project Yaksha. Yaksha, a custom Linux shell program.
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <string>

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<readline/readline.h>
#include<readline/history.h>

#include <iostream>
#include <string>
using namespace std;

#define clear() printf("\033[H\033[J")

int break_signal = 0;
const char*directory;

void init_shell() 
{
    clear();
    printf("--IMPORTANT:----------------------------------");
    printf("Welcome to Yaksha :)");
    printf("----------------------------------------------");
    char*username = getenv("USER");
    printf("\n\n\nUser is: @%s", username);
    printf("\n");
    sleep(1);
    clear();
}

void list_directories()
{
    DIR *direct = opendir(".");
    struct dirent *dp;
 
    while ((dp = readdir(direct)))
    {
        if (dp->d_type == DT_DIR)
        {
            continue;
        }
        else
        {
            if (dp->d_type == DT_REG)
            {
                int fd = open(dp->d_name, O_RDONLY);
                int size = lseek(fd, 0, SEEK_END);
                printf("%s\n", dp->d_name);
                close(fd);
            }
        }
    }
 
    closedir(direct);
}

char* get_directory(){
    char cwd[1024];
    return getcwd(cwd, sizeof(cwd));
}

void process_input(string input, const char*current_directory){
    
    //ls command
    if (input.compare("ls") == 0) 
    {
        list_directories();
    }
    
    //clear command or ^L
    if (input.compare("clear") == 0 || input.compare("^L") == 0)
    {
        clear();
    }

    //exit out of the program itself
    if (input.compare("exit") == 0) 
    {
        break_signal = 1;
    }

    // after we clear out the possibilities of single arguments, we can begin with multiple arguments

}

int main()
{
    init_shell();
    while(1)
    {
        directory = get_directory();
        printf("%s\n", directory);
        string input;
        cout << ">";
        cin >> input;
        process_input(input, directory);
        if (break_signal == 1) 
        {
            break;
        }
    }
    return 0; 
}