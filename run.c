#include"prompt.h"
void run_command(char **command,int flag,int count,char *prompt_array,int *temp){
    // printf("pro:%s\n",prompt_array);
    int id=fork();
    struct timeval start,end;
    gettimeofday(&start,NULL);
    char *str=malloc(sizeof (char)*1000);
    strcpy(str,command[0]);
    int var=1;
    while(var<count){
        strcat(str,command[var]);
        var++;
    }
    if (id==0){
        if(execlp(command[0],command[0],command[1],NULL)==0){
            printf("error");
        };
    }
    else if (id>0){
        prompt_array[strlen(prompt_array)-1]='\0';
        waitpid(id,NULL,0);
         gettimeofday(&end,NULL);
        double overall_difference=end.tv_sec-start.tv_sec;
        char array[10000];
        if (overall_difference>2.00){
        snprintf(array,sizeof(array),"%s%s : %lf>",prompt_array,command[0],overall_difference);
        *temp=1;
        printf("%s",array);
    }}
}

// void run_background(char **argv,int count ,int background,int *pid_array,int size){
//     int pid=fork();
//     if (pid==0){
//         execvp(argv[0],argv);
//     }
//     else{
//         for (int i=0;i<size;i++){

//          int status;
//             pid_t result = waitpid(pid_array[i], &status, WNOHANG);
            
//             if (result > 0 && WIFEXITED(status)) {
//                 printf("Sleep exited normally (%d)\n", pid_array[i]);
//             }
//         }
//     }
//     }