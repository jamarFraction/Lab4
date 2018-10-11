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
int cpf2f(char *f1, char *f2);


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
    int result = myrcp(userCommand[1], userCommand[2]);

    return 0;
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
    
    struct stat f1Stat;
    struct stat f2Stat;

    int status = lstat(f1, &f1Stat);

    //Does file 1 exist?
    if (status == -1){

        //err
        printf("Argument 1 does not exist!\n");
        return status;
    }

    //Is File 1 Regular or a Link?
    if(S_ISREG(f1Stat.st_mode) || (S_ISLNK(f1Stat.st_mode))){

        //Stat file 2
        status = lstat(f2, &f2Stat);

        //If f2 DNE OR exists AND is a regular
        if (status == -1 || (status == 0 && (S_ISREG(f2Stat.st_mode))))
        {

            //file to file copy
            return cpf2f(f1, f2);

        }else{  //f2 exists and is a dir

            printf("F2 is a directory\n");

            //return cpf2d(f1,f2);
        }

        //All else has failed for argument 2
        printf("Argument 2 is not REG or LNK\n");
        return -1;
    }else if(S_ISDIR(f1Stat.st_mode)){  //Is F1 a Directory?

        //Stat file 2
        status = stat(f2, &f2Stat);

        if(status == 0 && !(S_ISDIR(f2Stat.st_mode))){

            printf("Argument 2 is not also a directory!\n");
            return -1;
        }

        //F2 DNE and needs to be a directory, so let's create one
        if(status = -1){

            //create the dir
            mkdir(f2, 0744);
        }

        //return cpd2d(f1, f2);
    }else{
        
        //err
        printf("File 1 is not REG or LNK or DIR\n");
        return -1;
    }

    return 0;
}

// cp file to file
int cpf2f(char *f1, char *f2)
{
    //stat structures for f1 and f2
    struct stat f1StatStruct;
    struct stat f2StatStruct;

    //f1 & f2 lstat status
    int f1Status = lstat(f1, &f1StatStruct);
    int f2Status = lstat(f2, &f2StatStruct);


    //check the std_ino to verify if the two files are the same (actual or link)
    if(f1StatStruct.st_ino == f2StatStruct.st_ino){

        printf("File 1 and File 2 are the same file!\n");
        return -1;
    }else if((S_ISLNK(f1StatStruct.st_mode) && f2Status == 0)){   //link to existing file check

        printf("Cannot copy link to existing file!\n");
        return -1;
    }else if((S_ISLNK(f1StatStruct.st_mode) && f2Status == -1)){

        //create a symbolic link between f1 and f2 to whatever f1 is already linked to
        return symlink(f1, f2); 
    }else{

        int fd0, fd1;
        int result = 0;
        char buffer[4096];
        
        //open f1 for reading
        fd0 = open(f1, O_RDONLY);
        
        //read the data from f1's fd to the buffer
        read(fd0, buffer , sizeof(buffer));
        
        //close f1's fd
        close(fd0);

        //open f2 (or create it if nonexistent) for reading 
        fd1 = open(f2, O_WRONLY | O_CREAT | O_TRUNC);

        //duplicate the permissions for File 1 to File 2
        chmod(f2, f1StatStruct.st_mode);

        //write to f2
        result = write(fd1, buffer, strlen(buffer));

        //close f2's fd
        close(fd1);    

        printf("Copy %s to %s successful!\n", f1, f2); 
        return 1;   
    }

    //Print a generic failure message
    printf("Copy %s to %s failed!\n", f1, f2);
}