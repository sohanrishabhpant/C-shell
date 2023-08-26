#ifndef __PROMPT_H
#define __PROMPT_H
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>
#include <pwd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <ctype.h>
#include<time.h>
#include<sys/time.h>
#include<string.h>
#include <errno.h>
#include <getopt.h>
#include <grp.h>
#include<stdbool.h>




void prompt();
void prompt1(char *command,char *other_dir,int count,char*path);
void execute(char **command,int flag);

#endif