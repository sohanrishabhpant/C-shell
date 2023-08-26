#include "prompt.h"
#include "warp.c"

void display_extra_info(char *filename, char *full_path,int extra_info,int hidden_files) {
    struct stat info;
        if (extra_info){
           if (stat(full_path, &info) == 0) {
        printf("%10ld ", info.st_size);
        printf((S_ISDIR(info.st_mode)) ? "d" : "-");
        printf((info.st_mode & S_IRUSR) ? "r" : "-");
        printf((info.st_mode & S_IWUSR) ? "w" : "-");
        printf((info.st_mode & S_IXUSR) ? "x" : "-");
        printf((info.st_mode & S_IRGRP) ? "r" : "-");
        printf((info.st_mode & S_IWGRP) ? "w" : "-");
        printf((info.st_mode & S_IXGRP) ? "x" : "-");
        printf((info.st_mode & S_IROTH) ? "r" : "-");
        printf((info.st_mode & S_IWOTH) ? "w" : "-");
        printf((info.st_mode & S_IXOTH) ? "x" : "-");
        }
        struct tm *timeinfo;
        char time_buffer[80];
        timeinfo = localtime(&info.st_mtime);
        strftime(time_buffer, sizeof(time_buffer), " %b %d %H:%M", timeinfo);
        printf("%s ", time_buffer);
        }
        if (stat(full_path,&info)==0){
         if (S_ISDIR(info.st_mode)) {
            printf("\033[1;34m"); 
            // Blue for directories
        } else if (info.st_mode & S_IXUSR || info.st_mode & S_IXGRP || info.st_mode & S_IXOTH) {
            printf("\033[0;32m"); // Green for executables
        } else {
            printf("\033[0m"); // Reset color
        }
        
        // Print filename
        printf("%s\n", filename); // Reset color
        
        fflush(stdout); // Flush stdout to ensure immediate output
    }
}
int comparator(const void *a, const void *b) {
     const char *filename1 = *(const char **)a;
    const char *filename2 = *(const char **)b;
    
    return strcmp(filename1, filename2);
   
}


char **function(char *path, int extra_info, int hidden_files, int *count) {
    char **temp = malloc(sizeof(char *) * 25);
    for (int i = 0; i < 25; i++) {
        temp[i] = malloc(sizeof(char) * 100);  // Adjust the size as needed
    }

    struct dirent *var;
    DIR *dp = opendir(path);


    while (1) {
       var=readdir(dp);
       if(var==NULL){
       break;
       }

        if (!hidden_files) {
            if (var->d_name[0] == '.') {
                continue;
            }
        }
        strcpy(temp[*count], var->d_name);

        *count = *count + 1;
    }

    qsort(temp, *count, sizeof(char *), comparator);

    closedir(dp);
    return temp;
}






void file_list(char **argv, int size,char *prompt_array,int ris,char**previous_array,char*home_dir) {
    int extra_info = 0;
    int hidden_files = 0;
    char *path=malloc(sizeof(char)*10000);
    if (size==1){
        getcwd(path,10000);
        hidden_files=0;
    }
    if (size > 1) {
        // for (int i = 1; i < size; i++) {
            // printf("%s\n",argv[i]);
            if (strcmp(argv[1], "-al") == 0||strcmp(argv[1],"-l")==0||strcmp(argv[1],"-l-a")==0||strcmp(argv[1],"-a-l")==0) {
                // pr1ntf("r1sha\n");
                extra_info = 1;
            }
            if (strcmp(argv[1], "-al") == 0||strcmp(argv[1],"-a")==0||strcmp(argv[1],"-l-a")==0||strcmp(argv[1],"-a-l")==0)
            {
                hidden_files = 1;
            }
            
            path=change_directory(argv,size,prompt_array,ris,previous_array,home_dir);
        }
    // printf("pa:%s\n",path);
    int k=0;
    char **temp=function(path, extra_info, hidden_files,&k);
    char full_path[2500];
    
    // if (hidden_files){
    if (hidden_files&&extra_info||extra_info||!hidden_files&&extra_info){
    for (int i=0;i<k;i++){
        snprintf(full_path,2500,"%s/%s",path,temp[i]);
        display_extra_info(temp[i],full_path,extra_info,hidden_files);
    }}
    if (hidden_files&&!extra_info){
        for (int i=0;i<k;i++){
            // display_info(temp[i]);
             snprintf(full_path,2500,"%s/%s",path,temp[i]);
            display_extra_info(temp[i],full_path,extra_info,hidden_files);
        }
    }
    if (!hidden_files&&!extra_info){
        for (int i=0;i<k;i++){
            // display_info(temp[i]);
             snprintf(full_path,2500,"%s/%s",path,temp[i]);
            display_extra_info(temp[i],full_path,extra_info,hidden_files);
        }
    }
    
     for (int i = 0; i < k; i++) {
        free(temp[i]);  // This is fine as long as k <= 15// This is fine as long as k <= 15
    // free(path);
    // free(path);
}free(temp);  
}