#include "prompt.h"

void copy(char *a,char *b){
    int i;
    for ( i=0;b[i];i++)
    {
        a[i]=b[i];
    }
    a[i]='\0';
}
void save_to_file(char **history, int *it) {
    FILE *fp;

    if (*it < 15) {
        fp = fopen("history.txt", "a");
        if (fp == NULL) {
            perror("Error opening file");
            return;
        }
        printf("the iterator is *it:%d\n",*it);
        fprintf(fp, "%s\n", history[*it - 1]);
        fclose(fp);
    } else {
        fp = fopen("history.txt", "w");
        if (fp == NULL) {
            perror("Error opening file");
            return;
        }
        for (int i = 0; i < 14; i++) {
            fprintf(fp, "%s", history[i]);
        }
        fprintf(fp,"\n%s",history[14]);
        fclose(fp);
    }
}

void add_to_file(char **history, int *it, int max_count, char *command) {
    int count = *it;

    if (*it == max_count) {
        for (int i = 1; i < max_count; i++) {
            copy(history[i - 1], history[i]);
        }
        copy(history[max_count - 1], command);
        save_to_file(history, it);
    } else {
        if (*it == 0 || ((*it > 0) && strcmp(history[*it - 1], command) != 0 && (*it < 15)) || strncmp(command, "pastevents", 10) != 0) {
            copy(history[*it], command);
            *it=*it+1;
            printf("after:it%d",*it);
            save_to_file(history, it);
        }
    }
}
void add_to_file1(char **history,int *it,int max_count,char **path){
  char *str=malloc(sizeof (char)*1000);
  strcpy(str,path[0]);
  int i=1;
  while(path[i]){
    strcat(str,path[i]);
    i++;
  }
  add_to_file(history,it,max_count,str);
}
void retrive_file(char **history, int *it) {
    FILE *fp = fopen("history.txt", "r");
    char *str = malloc(sizeof(char) * 1000);
    int line_count = 0;
    while (fgets(str, 1000, fp) != NULL && line_count < 15) {
        copy(history[line_count], str);
        line_count++;
    }
    *it = line_count;
    fclose(fp);
}

void execute_past_command(char **history, int position) {
    printf("position: %d\n", position);
    
    // Create a child process using fork
    pid_t child_pid = fork();
    
    if (child_pid < 0) {
        perror("fork");
        return;
    } else if (child_pid == 0) {
        // Child process
        char *command = history[position - 1];
        
        // Remove the newline character if present
        size_t len = strlen(command);
        if (len > 0 && command[len - 1] == '\n') {
            command[len - 1] = '\0';
        }

        if (strcmp(command, "pastevents execute") == 0 && position == 100) {
            printf("Cannot execute most recent command.\n");
            exit(1);
        }

        // Execute the command in the child process
        execlp("/bin/sh", "/bin/sh", "-c", command, (char *)NULL);

        // If execlp returns, an error occurred
        perror("execlp");
        exit(1);
    } else {
        // Parent process
        int status;
        waitpid(child_pid, &status, 0); // Wait for the child process to finish
    }
}

