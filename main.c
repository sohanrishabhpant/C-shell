#include "headers.h"
#include "prompt.c"
#include "input.c"
#include "file.c"
#include "past_events.c"
#include "run.c"
#include "proclore.c"
#include "seek.c"

#define SIZE_OF_COMMAND 50
#define MAX_COMMANDS 15

int main()
{
    int temp1;
    char *file = "history.txt";
    char prompt_array[100000];
    char **history = malloc(sizeof(char *) * 15);
    for (int i = 0; i < MAX_COMMANDS; i++)
    {
        history[i] = malloc(sizeof(char) * 10000);
    }
    int it = 0;
    // Keep accepting commands
    char *dir = malloc(sizeof(char) * 1000);
    getcwd(dir, 1000);
    char *dir1 = malloc(sizeof(char) * 1000);
    getcwd(dir1, 1000);
    char *path = malloc(sizeof(char) * 1000);
    getcwd(path, 1000);
    // printf("%s",dir);
    int count1 = 0;
    int process_id = getpid();
    retrive_file(history, &it);
    temp1 = 0;
    prompt();
    printf("\n");
    while (1)
    {

        // Print appropriate prompt with username, systemname and directory before accepting input

        // printf("%s\n",dir);
        if (temp1 == 0)
        {
            prompt1(prompt_array, dir1, count1, path);
        }
        char input[4096];
        if (fgets(input, 4096, stdin) == NULL)
        {
            break;
        }
        int i;
        for (i = 0; input[i]; i++)
        {
            if (input[i] == '\n')
            {
                break;
            }
        }
        input[i] = '\0';
        if (strcmp(input, "exit") == 0)
        {
            add_to_file(history, &it, 15, input);
            break;
        }
        else if (strcmp(input, "pastevents") == 0)
        {
            printf("ite:%d\n", it);
            for (int i = 0; i <= it - 1; i++)
            {
                printf("%s", history[i]);
            }
        }
        else if (strncmp(input, "pastevents purge", 16) == 0)
        {
            it = 0;
            FILE *fp = fopen("history.txt", "w");
            fclose(fp);
        }
        else
        {
            if (strstr(input, "pastevents") == NULL)
            {
                add_to_file(history, &it, 15, input);
                char *temp = input;
                char *token = strtok_r(temp, ";", &temp);
                while (token != NULL)
                {
                    char *argv[SIZE_OF_COMMAND];
                    int count = 0;
                    char *ms = strtok_r(temp, ";", &temp);
                    // printf("ni:%s\n",ms);
                    // char *arg=strtok(token," \t");
                    // argv[count++]=arg;
                    char *arg = strtok_r(token, " \t", &token);
                    while (arg != NULL)
                    {
                        argv[count++] = arg;
                        // printf("%s\n",argv[count-1]);
                        char *msd = strtok_r(token, " \t", &token);
                        arg = msd;
                        // printf("%s\n",token);
                    }
                    argv[count] = '\0';
                    int flag = 0;
                    if (count > 0)
                    {
                        if (strcmp(argv[count - 1], "&") == 0)
                        {
                            argv[count - 1] = NULL;
                            flag = 1;
                        }
                        if (strcmp(argv[0], "warp") == 0)
                        {
                            dir1 = change_directory(argv, count, prompt_array, count1, &dir, path);
                            flag = 2;
                        }
                        if (strcmp(argv[0], "peek") == 0)
                        {
                            file_list(argv, count, prompt_array, count1, &dir, path); // printf("count:%d\n",count);
                            flag = 2;
                        }
                        if (strncmp(argv[0], "pastevents", 11) == 0)
                        {
                            int var = atoi(argv[2]);
                            execute_past_command(history, var);
                            flag = 2;
                        }
                        if (strcmp(argv[0], "proclore") == 0)
                        {
                            give_data_process(argv, count, process_id);
                            dir1 = path;
                        }
                        if (strcmp(argv[0], "seek") == 0)
                        {
                            list_all_paths(argv, count, path);
                        }
                        // if (flag!=2){
                        //     execute(argv,flag);
                        // }
                        // if (strncmp(input,"pastevents",10)!=0){
                        // printf("iterator:%d\n",it);
                        // }
                    }
                    if (flag != 2)
                    {
                        run_command(argv, flag, count, prompt_array, &temp1);
                    }
                    retrive_file(history, &it);
                    token = ms;
                }
                count1++;
            }
            else
            {
                char *temp = input;
                char *token = strtok_r(temp, ";", &temp);
                
                while (token != NULL)
                {
                    if (strstr(token,"pastevents")==NULL){
                    add_to_file(history,&it,15,token);
                }
                    char *argv[SIZE_OF_COMMAND];
                    int count = 0;
                    char *ms = strtok_r(temp, ";", &temp);
                    // printf("ni:%s\n",ms);
                    // char *arg=strtok(token," \t");
                    // argv[count++]=arg;
                    char *arg = strtok_r(token, " \t", &token);
                    while (arg != NULL)
                    {
                        argv[count++] = arg;
                        // printf("%s\n",argv[count-1]);
                        char *msd = strtok_r(token, " \t", &token);
                        arg = msd;
                        // printf("%s\n",token);
                    }
                    argv[count] = '\0';
                    int flag = 0;
                    token=ms;
                     if (strncmp(argv[0], "pastevents", 11) == 0)
                        {
                            int var = atoi(argv[2]);
                            execute_past_command(history, var);
                            flag = 2;
                        }
                }
            }
        }
    }
}