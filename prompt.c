#include "headers.h"
#define MAX_SIZE (PATH_MAX+_SC_LOGIN_NAME_MAX+_SC_HOST_NAME_MAX+26)


void prompt1(char*prompt_array,char *other_dir,int count,char*path) {
    struct passwd *pw = getpwuid(getuid());
    char *user=pw->pw_name;
    char host[10000];
    char dir[10000];
    gethostname(host,sizeof(host));
    int flag=0;
    // if (flag==0){
        if (count==0){
    getcwd(dir,sizeof(dir));}
    // }
    // printf("%s\n",dir);
    char a[1000];
    int m;
    for (m=1;dir[m+7];m++){
        a[m]=dir[m+7];
    }
    a[m]='\0';
    a[0]='~';
    // printf("%s",a);
    // printf("%s %s %s\n",user,host,a);
    int i;
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
    if (strncmp(dir,other_dir,strlen(dir))==0){    
        prompt_array[i++]='~';
        int j=strlen(dir);
        while(other_dir[j]){
        prompt_array[i++]=other_dir[j];
        j+=1;
        }
        prompt_array[i]='\0';
        }
     else{
        // printf("hello");
        while(other_dir[i-k]){
                prompt_array[i]=other_dir[i-k];
                i++;
            }
        }

     prompt_array[i++]='>';
     prompt_array[i]='\0';
     printf("%s",prompt_array);

    // Do not hardcode the prmopt
    // printf("<Everything is a file> ");    
}
void prompt(){
    printf("<Everything is a file>");
}
