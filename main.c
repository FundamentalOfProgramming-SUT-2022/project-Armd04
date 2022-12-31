#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define ll long long int
#define MAX_VAL 10000

void files(char path[])
{
    int k = 0;
    char filename[MAX_VAL] = {}, dir[MAX_VAL] = {};
    for (ll i = 1 ; i < strlen(path) ; ++i){
        ll j = i;
        while (j < strlen(path) && path[j] != '/') j++;
        while (i < j) dir[k++] = path[i++];
        if (i == strlen(path)){
            FILE *fp = NULL;
            fp = fopen(dir, "rb");
            if (fp != NULL) {printf("file is already existing\n"); fclose(fp); return;}
            else{
                fp = fopen(dir, "a");
                fclose(fp);
                return;
            }
        }
        mkdir(dir, 0700);
        dir[k++] = '/';
    }
}


void creatfile()
{
    char option[100], path[MAX_VAL];
    scanf(" -%s", option);
    scanf(" %s", path);
    if (strcmp(option, "file") == 0){
        files(path);
    }
    // int check;
    // char* dirname = "root/dir1";
    // check = mkdir(dirname, 0777);
    // if (check == 1) printf("kir\n");


    // FILE *fp = NULL;
    // fp  = fopen("text.txt", "w");
    // if (fp == NULL) printf("kir\n");
    // fclose(fp);
}

void cat()
{
    char option[100], filename[MAX_VAL];
    scanf(" -%s", option);
    scanf("%s", filename);
    if (filename[0] == '/'){
        for (ll i = 1 ; i < strlen(filename) ; i++){
            filename[i - 1] = filename[i];
        }
        filename[strlen(filename) - 1] = '\0';
    }
    FILE *fp;
    fp = fopen(filename, "r");
    if (fp == NULL){printf("file not found\n"); return;}
    int c;
    while(1)
   {
      c = fgetc(fp);
      if(feof(fp)) break;
      printf("%c", c);
   }
}

int main()
{
    char command[100];
    int run = 1;
    while (run)
    {
        scanf("%s", command);
        if (strcmp(command ,"exit") == 0) run = 0;
        else if (strcmp(command, "createfile") == 0) creatfile();
        else if (strcmp(command, "cat") == 0) cat();
    }
    return 0;
}



