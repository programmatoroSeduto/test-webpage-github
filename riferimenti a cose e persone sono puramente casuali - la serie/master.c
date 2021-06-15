#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char* argv){

    int fd[2];
    int numb1, numb2 = 0;
    int result;
    char sign; 
    if(pipe(fd)<0) perror("pipe"); //create pipe
    //printf( "(MASTER) fd{ %d, %d }\n", fd[0], fd[1] ); fflush(stdout);
    char strFd[16];
    //sprintf(strFd, "%d", fd[1]);
    sprintf(strFd, "%d", fd[0]);
    
    int o3id; //first fork o1
    o3id = fork(); fflush(stdout);
    if(o3id<0) perror("O1 fork"); //check error in first fork
    if(o3id == 0){ //first son o1
        if(close(fd[1])!=0) perror("Closing file descriptor");
        int err1;
        char *argv1[]={"o3", strFd, NULL}; //pass file descriptor
        err1 = execv("o3", argv1);
        if(err1<0) perror("exec o3");
    }
  
    //read the user operation
    printf("Write the operation in the form:\n n P m -> sum \n n M m -> substraction \n n T m -> multiplication \n n D m -> division:\n");
    scanf("%d %c %d", &numb1, &sign, &numb2);

    //check what is the operation to compute
    switch (sign)
        {
        case 'P':  result = (numb1 + numb2);
            break;
        case 'M':  result = (numb1 - numb2);
            break;
        case 'T':  result = (numb1 * numb2);
            break;
        case 'D':  result = (numb1 / numb2);
            break;
        
        default:  printf("Wrong command"); 
            break;
        }
    //printf("%d", result);
    // non chiudere 2 volte!
    //close(fd[0]);
    fflush(stdout);
    if(write(fd[1], &result, sizeof(result))<0) perror("Error in write");
    
    int status;
    wait(&status);
   
    // a meno che tu non stia usando i socket o altri meccanismi,
    // l'error handling per i close non ha molto senso
    if(close(fd[1])!=0) perror("closing file descriptor");
    if(close(fd[0])!=0) perror("closing file descriptor");
    

    exit(1);

}