#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "get_input.h"

#define ll long long int
#define MAX_VAL 10000

char vc;

void insertstr_u(char *filename, char *message, int position)
{
    if (filename[0] == '/'){
        for (ll i = 1 ; i < strlen(filename) ; i++){
            filename[i - 1] = filename[i];
        }
        filename[strlen(filename) - 1] = '\0';
    }
    FILE *fp, *fpr;
    fpr = fopen(filename, "r");
    if (fpr == NULL){printf("file not found\n"); return;}
    int counter = 0;
    int count = 0;
    char string[MAX_VAL] = {};
    int c;
    while(1)
    {
        c = fgetc(fpr);
        if(feof(fpr)) break;
        string[count] = c;
        count++;
    }
    fclose(fpr);
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

void removestr_u(char *filename, int position, int sz, char *option)
{
    if (filename[0] == '/'){
        for (ll i = 1 ; i < strlen(filename) ; i++){
            filename[i - 1] = filename[i];
        }
        filename[strlen(filename) - 1] = '\0';
    }
    FILE *fp, *fpr;
    fpr = fopen(filename, "r");
    if (fpr == NULL){printf("file not found\n"); return;}
    int counter = 0;
    int count = 0;
    char string[MAX_VAL] = {};
    int c;
    while(1)
    {
        c = fgetc(fpr);
        if(feof(fpr)) break;
        string[count] = c;
        count++;
    }
    fclose(fpr);
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
    return;
}

void make_copy(char *filename)
{
    char filename2[100];
    strcpy(filename2, filename);
    int flag = 0;
    for (int i = strlen(filename2) - 1 ; i >= 0 ; i--)
    {
        if (filename2[i] == '/')
        {
            filename2[i + 1] = '.';
            flag = 1;
            break;
        }
        if (flag == 0) filename2[i + 1] = filename2[i];
    }
    FILE *fp1, *fp2;
    fp1 = fopen(filename, "r");
    fp2 = fopen(filename2, "w");
    int c;
    while (1)
    {
        c = fgetc(fp1);
        if (c == EOF) break;
        fputc(c, fp2); 
    }
    fclose(fp1);
    fclose(fp2);
    return;
}

void get_a_line(char *filename, int line, char *output)
{
    empty(output);
    FILE *fp;
    fp = fopen(filename, "r");
    char string[MAX_VAL];
    empty(string);
    int counter = 0, c, line_num = 1;
    while (1)
    {
        c = fgetc(fp);
        if (feof(fp)) break;
        if (c == '\n')
        {
            if (line_num == line){
                strcpy(output, string);
                return;
            }
            line_num++;
            empty(string);
            counter = 0;
        }
        else
        {
            string[counter] = c;
            counter++;
        }
    }
    return;
}