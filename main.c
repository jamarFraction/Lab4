#include <stdio.h>       // for printf()
#include <stdlib.h>      // for exit()
#include <string.h>      // for strcpy(), strcmp(), etc.
#include <libgen.h>      // for basename(), dirname()
#include <fcntl.h>       // for open(), close(), read(), write()

// for stat syscalls
#include <sys/stat.h>
#include <unistd.h>

// for opendir, readdir syscalls
#include <sys/types.h>
#include <dirent.h>



int main(int argc, char *argv[]){

    printf("Hey, friends.\n");

    if (argc < 3)
        //print usage and exit;
    return myrcp(argv[1], argv[2]);

    return 0;
}

int myrcp(char *f1, char *f2)
{
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