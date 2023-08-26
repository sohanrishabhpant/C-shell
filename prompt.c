#include "headers.h"
#define MAX_SIZE (PATH_MAX+_SC_LOGIN_NAME_MAX+_SC_HOST_NAME_MAX+26)


void prompt1(char*prompt_array,char *other_dir,int count,char*path) {
    struct passwd *pw = getpwuid(getuid());
    char *user=pw->pw_name;
    char host[10000];
    char *dir=malloc(sizeof(char)*10000);
    gethostname(host,sizeof(host));
    int flag=0;
         int i;
     getcwd(dir,100000);
    char a[10000];
    int m;
    for (m=1;dir[m+7];m++){
        a[m]=dir[m+7];
    }
    a[m]='\0';
    a[0]='~';
    for ( i=0;user[i];i++){
        prompt_array[i]=user[i];
    }
    prompt_array[i++]='@';
    // printf("%s\n",prompt_array);
    int j=i;
    while((host[i-j])){
        prompt_array[i]=host[i-j];
        i++;
    }
    prompt_array[i++]=':';
    // printf("%s\n",prompt_array);
    int k=i;
    // printf("%d\n",i);
    int var=0;
    if (other_dir==NULL){
        prompt_array[i++]='~';
    }
    else if (strncmp(path,other_dir,strlen(path))==0){   
        prompt_array[i++]='~';
        int j=strlen(path);
        while(other_dir[j]){
        prompt_array[i++]=other_dir[j];
        j+=1;
        }
        }
     else{
        while(other_dir[i-k]){
                prompt_array[i]=other_dir[i-k];
                i++;
            }
        }

     prompt_array[i++]='>';
     prompt_array[i]='\0';
     printf("%s",prompt_array);


}
void prompt(){
    printf("<Everything is a file>");
}