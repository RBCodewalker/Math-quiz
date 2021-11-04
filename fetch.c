#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/types.h>

#include "quiz.h"

char* fetch(char *url)
{
    pid_t pid;
    
    int ref[2];
    int ret = pipe(ref);

    pid = fork();
    
    if(ret == -1)
    {
        perror("ERROR CREATING PIPE!!!");
    }

    if(pid < 0)
    {
        perror("FORK ERROR!!!");
        exit(1);
    }
    // in case of child process, the fetching is carried out
    else if(pid == 0)
    {
        close(ref[0]); //closes the first file descriptor(fd)
        dup2(ref[1], STDOUT_FILENO); // duplicating the second fd

        char *cl = "curl";
        char *args[] = {cl, "-s", url, NULL};
        if(execvp(cl, args) == -1)
        {
            printf("ERROR WITH EXECUTION!!!\n"); //execvp returns -1 in case of
                                                 // error with the execution
            exit(2);
        };
        close(ref[1]);
        // flush the standard output stream to avoid errors
        // fflush(stdout);
        // close(STDOUT_FILENO);
        // exit(EXIT_SUCCESS);
    }
    // if parent is encountered, wait for child and fetch
    else
    {
        // while(wait(NULL) != pid) continue; 
        
        close(ref[1]);
        
        
        char *buffr = (char*) malloc (4096);
        if(!buffr)
        {
            perror("MALLOC ERROR!!!");
            exit(3);
        }
        
        while(read(ref[0], buffr, 4096) != 0){}
        // buffr[x]='\0';
        // if(x < 0) perror("ERROR READING FILE DESCRIPTOR");

        close(ref[0]);
        
        return buffr;
    }
}