#include "headers.h"

char* change_directory(char **command, int size, char *prompt_array, int ris, char **prev_dir,char *home_dir) {
    char *dir = malloc(sizeof(char) * 1000);
    getcwd(dir, 1000);

    // for (int i=0;i<size;i++){
    //     for (int j=0;command[i][j];j++){
    //         printf("%c\n",command[i][j]);
    //     }
    // }
    if (size == 1) {
        printf("error in warp");
    } else {
        // printf("size:%d\n",size);
        int flag = 0;
        int count = 0;
    for (int i=1;i<size;i++){
        if (strcmp(command[i], ".") == 0) {
            // No change, stay in the current directory
        } else if (strcmp(command[i], "..") == 0) {
            char*dir=malloc(sizeof(char)*1000);
            getcwd(dir,1000);
            chdir("..");
            *prev_dir=dir;
        } else if (strncmp(command[i], "~",1) == 0) {
            char *dir=malloc(sizeof(char)*1000);
            getcwd(dir,1000);
            *prev_dir=dir;
            chdir(home_dir);
            flag = 2;
            if (strlen(command[i])>1){
            int j=2;
            int k=2;
            while(command[i][j]!='\0'){
             char *arr=malloc(sizeof(char)*1000);
            //  printf("char:%c,i:%d,j:%d",command[i][j],i,j);
            while(command[i][j]!='/'&&command[i][j]!='\0'){
                arr[k-2]=command[i][j];
                j++;
                k++;
            }arr[k-2]='\0';
            // printf("nee:%s\n",arr);
            chdir(arr);
            j++;
            k=2;
            free(arr);
            }
            
        }} else if (strcmp(command[i], "-") == 0) {
            if (*prev_dir) {
                chdir(*prev_dir);
                char *temp = *prev_dir;
                *prev_dir = dir;
                dir = temp;
            } else {
                printf("No previous directory stored.\n");
            }
        } else {
            char *dir=malloc(sizeof(char)*1000);
            getcwd(dir,1000);
            *prev_dir=dir;
            chdir(command[i]);
            flag = 3;
        }
        if (command[i]==NULL){
            chdir(home_dir);
        }
        count++;
    

    getcwd(dir, 256);
    
    // printf("prev: %s\n", *prev_dir);
    }
    printf("%s\n", dir);
    }
    return dir;
}