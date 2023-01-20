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

void fix_indent(char *filename, int start, int end, int *prev_start, int prev_end[], int sz)
{
    FILE *fpr;
    fpr = fopen(filename, "r");
    char string[MAX_VAL], string2[MAX_VAL];
    int c, counter = 0, counter2 = 0;
    while (1)
    {
        c = fgetc(fpr);
        if (feof(fpr)) break;
        string[counter] = c;
        counter++;
    }
    int index = 0;
    while(1)
    {
        if (index >= counter) break;
        if (index <= start || index > end){
            string2[counter2] = string[index];
            counter2++;
            index++;
        }
        else{
            if (index == start + 1 && end == start + 1)
            {
                string2[counter2] = '\n';
                string2[counter2 + 1] = string[index];
                index++;
                counter2+=2;
                for (int i = 0 ; i < sz ; i++) if (index <= prev_end[i]) prev_end[i]+=1;
            }
            else if (index == start + 1 && string[index] != '\n')
            {
                string2[counter2] = '\n';
                counter2++;
                string2[counter2] = ' ';
                counter2++;
                string2[counter2] = ' ';
                counter2++;
                string2[counter2] = ' ';
                counter2++;
                string2[counter2] = ' ';
                counter2++;
                // (*prev_end)+=5;
                for (int i = 0 ; i < sz ; i++) if (index < prev_end[i]) prev_end[i]+=5;
                string2[counter2] = string[index];
                counter2++;
                index++;
            }
            else if (string[index] == '\n')
            {
                index++;
                string2[counter2] = '\n';
                counter2++;
                string2[counter2] = ' ';
                counter2++;
                string2[counter2] = ' ';
                counter2++;
                string2[counter2] = ' ';
                counter2++;
                string2[counter2] = ' ';
                counter2++;
                // (*prev_end)+=5;
                for (int i = 0 ; i < sz ; i++) if (index <= prev_end[i]) prev_end[i]+=4;
            }
            else if (index == end && string[end - 1] != '\n')
            {
                string2[counter2] = '\n';
                string2[counter2 + 1] = string[index];
                // (*prev_end)+=1;
                for (int i = 0 ; i < sz ; i++) if (index < prev_end[i]) prev_end[i]+=1;
                counter2+=2;
                index++;
                if (end + 1 < strlen(string) && string[end + 1] != '\n')
                {
                    printf("1\n");
                    string2[counter2] = '\n';
                    counter2++;
                    for (int i = 0 ; i < sz ; i++) if (index <= prev_end[i]) prev_end[i]+=1;
                }
            }
            else if (index == end && end + 1 < strlen(string) && string[end + 1] != '\n')
            {
                string2[counter2] = string[index];
                index++;
                counter2++;
                string2[counter2] = '\n';
                counter2++;
                for (int i = 0 ; i < sz ; i++) if (index <= prev_end[i]) prev_end[i]+=1;
            }
            else if (string[index] == ' ' && string[index - 1] == '\n')
            {
                index++;
                for (int i = 0 ; i < sz ; i++) if (index <= prev_end[i]) prev_end[i]-=1;
            }
            else{
                string2[counter2] = string[index];
                counter2++;
                index++;
            }
        }
    }
    FILE *fp;
    fp = fopen(filename, "w");
    for (int i = 0 ; i < counter2 ; i++)
    {
        fputc(string2[i], fp);
    }
    fclose(fp);
    fclose(fpr);
    return;
}

int first_last(char *filename, int *start, int *end, int *prev_start, int prev_end[], int *sz)
{
    FILE *fpr;
    fpr = fopen(filename, "r");
    int c, counter = -1;
    int flag = 0, flag_check = 0;
    while (1)
    {
        c = fgetc(fpr);
        counter++;
        if (feof(fpr)) break;
        // if (c == '{' && (*start) == -1 && counter > (*prev_start)) {(*start) = counter; (*prev_start) = (*start);}
        // if (c == '}' && counter < (*prev_end)) {(*end) = counter;flag = 1;}
        if (c == '{' && counter < (*prev_start))
        {
            (*start) = counter;
            flag = 1;
            flag_check = 1;
        }
        if (c == '}' && flag == 1)
        {
            int f = 1;
            for (int i = 0 ; i < (*sz) ; i++)
            {
                if (prev_end[i] == counter) {f = 0; break;}
            }
            if (f == 0) continue;
            (*end) = counter;
            prev_end[(*sz)] = counter;
            (*sz)++;
            flag = 0;
        }
    }
    if (flag_check == 1) (*prev_start) = (*start);
    return flag_check;
}
