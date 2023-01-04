#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define ll long long int
#define MAX_VAL 10000

char vc;

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
    if (scanf(" \"%[^\"]", path) != 0) scanf("%c", &vc);
    else scanf(" %s", path);
    if (strcmp(option, "file") == 0){
        files(path);
    }
}

void cat()
{
    char option[100], filename[MAX_VAL];
    scanf(" -%s", option);
    if (scanf(" \"%[^\"]", filename) != 0) scanf("%c", &vc);
    else scanf(" %s", filename);
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
   fclose(fp);
   return;
}

void insert()
{
    char option[100], filename[MAX_VAL], message[MAX_VAL];
    int line, start;
    scanf(" -%s", option);
    if (scanf(" \"%[^\"]", filename) != 0) scanf("%c", &vc);
    else scanf(" %s", filename);
    scanf(" -%s", option);
    if (scanf(" \"%[^\"]", message) != 0) scanf("%c", &vc);
    else scanf(" %s", message);
    scanf(" -%s", option);
    scanf(" %d:%d", &line, &start);
    if (filename[0] == '/'){
        for (ll i = 1 ; i < strlen(filename) ; i++){
            filename[i - 1] = filename[i];
        }
        filename[strlen(filename) - 1] = '\0';
    }
    FILE *fp, *fpr;
    fpr = fopen(filename, "r");
    if (fpr == NULL){printf("file not found\n"); return;}
    int position = 0, counter = 0;
    int count = 0;
    char string[MAX_VAL] = {};
    int c;
    while(1)
    {
        c = fgetc(fpr);
        if(feof(fpr)) break;
        if (counter < line  - 1)
        {
        if (c == (int)'\n') counter++;
        position++;
        }
        string[count] = c;
        count++;
    }
    fclose(fpr);
    position += start;
    fp = fopen(filename, "w+");
    fseek(fp, 0, SEEK_SET);
    for (int i = 0 ; i < position ; i++){
        fprintf(fp, "%c", string[i]);
    }
    int index = 0;
    while (index < strlen(message))
    {
        if (index < strlen(message) - 1 && message[index] == '\\' && message[index + 1] == 'n'){
            if (index > 0 && message[index - 1] == '\\') index++;
            else{
                fputc('\n', fp);
                index += 2;
            }
        }
        else{
            fputc(message[index], fp);
            index ++;
        }
    }
    for (int i = position ; i < strlen(string) ; i++){
        fprintf(fp, "%c", string[i]);
    }

    fclose(fp);
    return;
}

void removestr()
{
    char option[100], filename[MAX_VAL];
    int sz, line, start;
    scanf(" -%s", option);
    if (scanf(" \"%[^\"]", filename) != 0) scanf("%c", &vc);
    else scanf(" %s", filename);
    scanf(" -%s", option);
    scanf(" %d:%d", &line, &start);
    scanf(" -%s", option);
    scanf(" %d", &sz);
    scanf(" -%s", option);
    if (filename[0] == '/'){
        for (ll i = 1 ; i < strlen(filename) ; i++){
            filename[i - 1] = filename[i];
        }
        filename[strlen(filename) - 1] = '\0';
    }
    FILE *fp, *fpr;
    fpr = fopen(filename, "r");
    if (fpr == NULL){printf("file not found\n"); return;}
    int position = 0, counter = 0;
    int count = 0;
    char string[MAX_VAL] = {};
    int c;
    while(1)
    {
        c = fgetc(fpr);
        if(feof(fpr)) break;
        if (counter < line  - 1)
        {
        if (c == (int)'\n') counter++;
        position++;
        }
        string[count] = c;
        count++;
    }
    fclose(fpr);
    position += start;
    fp = fopen(filename, "w+");
    if (strcmp(option, "f") == 0)
    {
        int to = position + sz;
        for (int i = 0 ; i < position ; i++) fprintf(fp, "%c", string[i]);
        for (int i = to ; i < strlen(string) ; i++) fprintf(fp, "%c", string[i]);
    }
    else if (strcmp(option, "b") == 0)
    {
        int from = position - sz;
        for (int i = 0 ; i <= from ; i++) fprintf(fp, "%c", string[i]);
        for (int i = position + 1 ; i < strlen(string) ; i++) fprintf(fp, "%c", string[i]);
    }
    fclose(fp);
}

int main()
{
    char command[100];
    int run = 1;
    while (run)
    {
        //printf("$");
        scanf("%s", command);
        if (strcmp(command ,"exit") == 0) run = 0;
        else if (strcmp(command, "createfile") == 0) creatfile();
        else if (strcmp(command, "cat") == 0) cat();
        else if (strcmp(command, "insertstr") == 0) insert();
        else if (strcmp(command, "removestr") == 0) removestr();
        else {scanf("%[^\n]", command);printf("Invalid input\n");}
    }
    return 0;
}



