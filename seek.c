#include "prompt.h"


#define RESET_COLOR "\033[0m"
#define GREEN_COLOR "\033[32m"
#define BLUE_COLOR "\033[34m"
char buffer[10000];
void seek_recursive( char *target,  char *dir_path, int is_directory, int is_file, int is_execute,char *home) {
    DIR *dir = opendir(dir_path);
    if (dir == NULL) {
        perror("Directory open error");
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        char full_path[500];
        snprintf(full_path, 500, "%s/%s", dir_path, entry->d_name);

        struct stat entry_info;
        if (stat(full_path, &entry_info) == -1) {
            perror("stat error");
            continue;
        }

        int is_target_directory = S_ISDIR(entry_info.st_mode);
        int is_target_file = S_ISREG(entry_info.st_mode); 

        if (is_directory && !is_target_directory) {
            continue;
        }
        if (is_file && !is_target_file) {
            continue;
        }
        char color_code[10];
        if (strcmp(target, entry->d_name) == 0) {
            
            if (is_target_directory) {
                strcpy(color_code, BLUE_COLOR);
            } else {
                strcpy(color_code, GREEN_COLOR);
            }
                
            snprintf(buffer,100000,"%s/%s", dir_path, entry->d_name);
            buffer[strlen(buffer)]='\0';

            if (is_execute && !is_target_directory) {
                FILE *file = fopen(full_path, "r");
                if (file == NULL) {
                    perror("File open error");
                    continue;
                }

                char line[256];
                while (fgets(line, sizeof(line), file)) {
                    printf("%s", line);
                }

                fclose(file);
            }
        }

        if (is_target_directory) {
            seek_recursive(target, full_path, is_directory, is_file, is_execute,home);
        }
    }

    closedir(dir);
}

void seek(char **token, int count,char *path) {
    
    int is_directory = 0;
    int is_file = 0;
    int is_execute = 0;

   int i=1;
        if (strcmp(token[i], "-d") == 0) {
            is_directory = 1;
        } else if (strcmp(token[i], "-f") == 0) {
            is_file = 1;
        } else if (strcmp(token[i], "-e") == 0) {
            is_execute = 1;
        }   if (!is_directory&&!is_file&&!is_execute){
            if (count==2){
            seek_recursive(token[1], path, is_directory, is_file, is_execute,path);}
            else{
                    // printf("%s\n",token[2]);
                char *str1=malloc(sizeof (char)*1000);
                strcpy(str1,token[2]);
                // printf("%s",str1);
                char *str3=malloc(sizeof(char)*1000);
                strcpy(str3,path);
                char *str2=malloc(sizeof(char)*1000);
                for (int i=1;str1[i];i++){
                    str2[i-1]=str1[i];
                }
                free(str1);
                strcat(str3,str2);
                free(str2);
                // printf("st1:%s",str3);
                seek_recursive(token[1],str3,is_directory,is_file,is_execute,path);
                free(str3);
            }
        }
        else{
            if (count==3){
                seek_recursive(token[2],path,is_directory,is_file,is_execute,path);
            }
            // printf("sldkndlskn");
            else{
            char *str3=change_directory(token,count,path,0,&path,path);
            // printf("%s\n",str3);
           seek_recursive(token[2],str3,is_directory,is_file,is_execute,path);
        }}
        i++;
    if (strstr(buffer,path)!=NULL){
        int j=strlen(path);
        printf("~");
        while(buffer[j]){
            printf("%c",buffer[j]);
            j++;
        }
        printf("\n");
    }
}

//  // Move this line outside the while loop