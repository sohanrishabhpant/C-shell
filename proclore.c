#include"prompt.h"

void give_data_process(char**command,int count,int process_id,char *home){
 char proc_path[100];
    snprintf(proc_path, sizeof(proc_path), "/proc/%d/stat", process_id);

    FILE *file = fopen(proc_path, "r");
    if (file == NULL) {
        perror("fopen");
        return;
    }

    int pid_val;
    char comm[256], state;
    int ppid, pgrp;
    unsigned long vsize;

    fscanf(file, "%d %s %c %d", &pid_val, comm, &state, &ppid);
    fclose(file);

    snprintf(proc_path, sizeof(proc_path), "/proc/%d/status", process_id);

    file = fopen(proc_path, "r");
    if (file == NULL) {
        perror("fopen");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, "State:", 6) == 0) {
            state = line[7];
        } else if (strncmp(line, "VmSize:", 7) == 0) {
            sscanf(line + 7, "%lu", &vsize);
        } else if (strncmp(line, "Pgrp:", 5) == 0) {
            sscanf(line + 6, "%d", &pgrp);
        }
    }
    fclose(file);

    char status_str[4];
    if (state == 'R' || state == 'S' || state == 'Z') {
        status_str[0] = state;
        status_str[1] = (pgrp == process_id) ? '+' : '\0';
        status_str[2] = '\0';
    } else {
        status_str[0] = '\0';
    }

    char exe_path[1000];
    snprintf(proc_path, sizeof(proc_path), "/proc/%d/exe", process_id);

    ssize_t len = readlink(proc_path, exe_path, sizeof(exe_path) - 1);
    if (strncmp(exe_path,home,strlen(home))==0){
        printf("pid : %d\n", process_id);
    printf("process status : %s\n", status_str);
    printf("Process Group : %d\n", pgrp);
    printf("Virtual memory : %lu\n", vsize);
    printf("Executable path:.");
            int j=strlen(home);
            while(exe_path[j]){
                printf("%c",exe_path[j]);
                j++;
            }
            printf("\n");
    }
    else{
    if (len != -1) {
        exe_path[len] = '\0';
    } else {
        strcpy(exe_path, "N/A");
    }

    printf("pid : %d\n", process_id);
    printf("process status : %s\n", status_str);
    printf("Process Group : %d\n", pgrp);
    printf("Virtual memory : %lu\n", vsize);
    printf("executable path : %s\n", exe_path);
}}
