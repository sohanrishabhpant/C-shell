#include "headers.h"

void execute(char **command,int flag){
    int id=fork();
    if (id==0){
        if (execvp(command[0],command)==0){
            printf("error");
        }
    //    if(execlp(command,command,NULL)==0){
    //     printf("%s is not a valid command\n",command[0]);
    //    } }}
    }
    else{
        if (flag){
            printf("[%d]%d",1,id);
        }
        if (!flag){
            int status;
            waitpid(id,&status,0);
        }
    }
}