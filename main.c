#include <stdio.h>       // for printf()
#include <stdlib.h>      // for exit()
#include <string.h>      // for strcpy(), strcmp(), etc.
#include <libgen.h>      // for basename(), dirname()
#include <fcntl.h>       // for open(), close(), read(), write()
#include <stdbool.h>

// for stat syscalls
#include <sys/stat.h>
#include <unistd.h>

// for opendir, readdir syscalls
#include <sys/types.h>
#include <dirent.h>

char *userCommand[16];    //array to hold the strings of a command
int myargc = 0;

void tokenize(char source[]);
int myrcp(char *f1, char *f2);

int main(int argc, char *argv[]){

    printf("Hey, friends.\n");

    char lineCpy[128];
    char line[128];     //raw user line

    //Prompt user for a command
    printf("Command: ");
    fflush(stdout);

    fgets(line, 128, stdin);

    //chop the tail off the line, set to null
    line[strlen(line) - 1] = 0;

    strcpy(lineCpy, line);

    //results stored in global userCommand array
    tokenize(lineCpy);

    //check for form fitting command
    if (myargc < 3)
    {
        //print usage and exit?
        //whatever that means.. will return
        return 0;
    }


    //Let's get to it!
    return myrcp(userCommand[1], userCommand[2]);
}

void tokenize(char source[])
{

    //temp string holder of strtok vals
    char *next = strtok(source, " ");

    int i = 0;

    //grab all space-separated user input
    //put in arg array
    while (next != 0)
    {

        userCommand[i] = next;

        next = strtok(NULL, " ");

        i++;
        myargc += 1;
    }
}

int myrcp(char *f1, char *f2)
{
    

    printf("oh, hey there.\n");
    // {
    //    1. stat f1;   if f1 does not exist ==> exit.
    //                  f1 exists: reject if f1 is not REG or LNK file
    //    2. stat f2;   reject if f2 exists and is not REG or LNK file

    //    3. if (f1 is REG){
    //          if (f2 non-exist OR exists and is REG)
    //             return cpf2f(f1, f2);
    // 	 else // f2 exist and is DIR
    //             return cpf2d(f1,f2);
    //       }
    //    4. if (f1 is DIR){
    // 	if (f2 exists but not DIR) ==> reject;
    //         if (f2 does not exist)     ==> mkdir f2
    // 	return cpd2d(f1, f2);
    //       }
    return 0;
}