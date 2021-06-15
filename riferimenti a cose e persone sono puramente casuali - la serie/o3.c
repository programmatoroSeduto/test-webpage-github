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

// https://stackoverflow.com/questions/597311/why-does-the-child-process-here-not-print-anything

int main(int argc, char *argv[]){

    int numb2;
    int result;
    int result1;
    char sign;
    int fd[2];
    
    //fd[1] = atoi(argv[1]); //takes file descriptor from the father
    // fd[0] = atoi(argv[0]);
    fd[0] = atoi(argv[1]);
    fd[1] = -1;
    //printf( "(O3) fd{ %d, %d }", fd[0], fd[1] ); fflush(stdout);
    
    //read the message
    if(read(fd[0], &result, sizeof(result)) < 0){
        perror("Error in read");
        exit(-1);
    }

    //print the operation result
    printf("Choose new operation: "); 
    //scanf("%c %d", &sign, &numb2);
    printf("%d ", result); fflush(stdout); scanf("%c %d", &sign, &numb2);

    //check what is the operation to compute
    switch (sign)
        {
        case 'P':  result1 = (result + numb2);
            break;
        case 'M':  result1 = (result - numb2);
            break;
        case 'T':  result1 = (result * numb2);
            break;
        case 'D':  result1 = (result / numb2);
            break;
        
        default:  printf("Wrong command");
            break;
        }
    printf("The final result is: %d\n", result1);

    // se questo fd viene aperto dal master, fallo chiudere al master
    // altrimenti avrai un errore bad file descriptor
    // perchè stai chiudendo questo fd 2 volte
    //close(fd[0]);
    //exit(1);

    return 0;
}