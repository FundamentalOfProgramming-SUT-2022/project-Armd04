#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
//#include <windows.h>
#include "help_func.h"

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
            fp = fopen(dir, "r");
            if (fp != NULL) {printf("file is already existing\n"); fclose(fp); return;}
            else{
                fp = fopen(dir, "a");
                fclose(fp);
                return;
            }
        }
        mkdir(dir, 0777);
        dir[k++] = '/';
    }
}

void creatfile()
{
    char option[100];
    char path[MAX_VAL];
    scanf(" --%s", option);
    scanf("%c", &vc);
    getting(path);
    if (strcmp(option, "file") == 0){
        files(path);
    }
    return;
}

void cat()
{
    char option[100];
    char filename[MAX_VAL];
    scanf(" --%s", option);
    scanf("%c", &vc);
    getting(filename);
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

void insertstr()
{
    char option[100];
    char message[MAX_VAL], filename[MAX_VAL];
    int line, start;
    scanf(" --%s", option);
    scanf("%c", &vc);   
    getting(filename);
    scanf(" --%s", option);
    scanf("%c", &vc);
    getting(message);
    scanf(" --%s", option);
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
    char option[100];
    char filename[MAX_VAL];
    int sz, line, start;
    scanf(" --%s", option);
    scanf("%c", &vc);
    getting(filename);
    scanf(" --%s", option);
    scanf(" %d:%d", &line, &start);
    scanf(" --%s", option);
    scanf(" %d", &sz);
    scanf(" --%s", option);
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
    return;
}

/*
void copystr()
{
    char option[100];
    char filename[MAX_VAL];
    int sz, line, start;
    scanf(" --%s", option);
    scanf("%c", &vc);
    getting(filename);
    scanf(" --%s", option);
    scanf(" %d:%d", &line, &start);
    scanf(" --%s", option);
    scanf(" %d", &sz);
    scanf(" --%s", option);
    if (filename[0] == '/'){
        for (ll i = 1 ; i < strlen(filename) ; i++){
            filename[i - 1] = filename[i];
        }
        filename[strlen(filename) - 1] = '\0';
    }
    FILE *fpr;
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
        count++;
    }
    position += start;
    fseek(fpr, position, SEEK_SET);
    if (strcmp(option, "f") == 0)
    {
        for (int i = 0 ; i < sz ; i++)
        {
            c = fgetc(fpr);
            string[i] = c;
        }
    }
    else if (strcmp(option, "b") == 0)
    {
        fseek(fpr, -sz, SEEK_CUR);
        for (int i = 0 ; i < sz ; i++)
        {
            c = fgetc(fpr);
            string[i] = c;
        }
    }
    const char *string1 = string;
    OpenClipboard(0);
    EmptyClipboard();
    const size_t ln = strlen(string1) + 1;
    HGLOBAL h = GlobalAlloc(GMEM_MOVEABLE, ln);
    memcpy(GlobalLock(h), string1, ln);
    GlobalUnlock(h);
    SetClipboardData(CF_TEXT, h);
    CloseClipboard();
    fclose(fpr);
}

void pastestr()
{
    char option[100];
    char filename[MAX_VAL];
    int line, start;
    scanf(" --%s", option);
    scanf("%c", &vc);
    getting(filename);
    scanf(" --%s", option);
    scanf(" %d:%d", &line, &start);
    if (filename[0] == '/'){
        for (ll i = 1 ; i < strlen(filename) ; i++){
            filename[i - 1] = filename[i];
        }
        filename[strlen(filename) - 1] = '\0';
    }
    OpenClipboard(0);
    HANDLE in = GetClipboardData(CF_TEXT);
    strcpy(message, (char *) in);
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

void cutstr()
{
    char option[100];
    char filename[MAX_VAL];
    int sz, line, start;
    scanf(" --%s", option);
    scanf("%c", &vc);
    getting(filename);
    scanf(" --%s", option);
    scanf(" %d:%d", &line, &start);
    scanf(" --%s", option);
    scanf(" %d", &sz);
    scanf(" --%s", option);
    if (filename[0] == '/'){
        for (ll i = 1 ; i < strlen(filename) ; i++){
            filename[i - 1] = filename[i];
        }
        filename[strlen(filename) - 1] = '\0';
    }
    FILE *fpr, *fp;
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
        count++;
    }
    position += start;
    fseek(fpr, position, SEEK_SET);
    if (strcmp(option, "f") == 0)
    {
        for (int i = 0 ; i < sz ; i++)
        {
            c = fgetc(fpr);
            string[i] = c;
        }
    }
    else if (strcmp(option, "b") == 0)
    {
        fseek(fpr, -sz, SEEK_CUR);
        for (int i = 0 ; i < sz ; i++)
        {
            c = fgetc(fpr);
            string[i] = c;
        }
    }
    const char *string1 = string;
    OpenClipboard(0);
    EmptyClipboard();
    const size_t ln = strlen(string1) + 1;
    HGLOBAL h = GlobalAlloc(GMEM_MOVEABLE, ln);
    memcpy(GlobalLock(h), string1, ln);
    GlobalUnlock(h);
    SetClipboardData(CF_TEXT, h);
    CloseClipboard();
    fclose(fpr);
    fpr = fopen(filename, "r");
    if (fpr == NULL){printf("file not found\n"); return;}
    position = 0;
    counter = 0;
    count = 0;
    strcpy(string, "");
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
*/

void find()
{
    char option[100], string[MAX_VAL] = {};
    char message[MAX_VAL], filename[MAX_VAL];
    int fcount = 0, fat = 0, fbyword = 0, fall = 0, flag_op;
    int num_of_words = 1, num_at, num_count = 0;
    scanf(" --%s", option);
    scanf("%c", &vc);
    getting(message);
    scanf(" --%s", option);
    scanf("%c", &vc);
    flag_op = getting_find(filename);
    if (filename[0] == '/'){
        for (ll i = 1 ; i < strlen(filename) ; i++){
            filename[i - 1] = filename[i];
        }
        filename[strlen(filename) - 1] = '\0';
    }
    options_find(&fcount, &fat, &fbyword, &fall, &flag_op, &num_at);
    FILE *fpr;
    fpr = fopen(filename, "r");
    if (fpr == NULL) {printf("file not found\n"); return;}
    if (fcount == 1 && fall + fat + fbyword != 0) {printf("Invalid set of option\n"); return;}
    if (fall == 1 && fat == 1) {printf("Invalid set of options\n"); return;}
    if (fcount == 0 && fat == 0 && fall == 0 && fbyword == 0)
    {
        int c, count = 0;
        while(1)
        {
            c = fgetc(fpr);
            if(feof(fpr)) break;
            string[count] = c;
            count++;
        }
        fclose(fpr);
        int flag = 1, flag2 = 0;
        for (int i = 0 ; i <= strlen(string) - strlen(message) ; i++)
        {
            flag = 1;
            for (int j = i ; j < i + strlen(message) ; j++){
                if (string[j] != message[j - i]) flag = 0;
            }
            if (flag == 1){
                flag2 = 1;
                printf("%d\n", i);
                break;
            }
        }
        if (flag2 == 0) printf("%d\n", -1);
        return;
    }
    if (fcount == 1)
    {
        int c, count = 0;
        while(1)
        {
            c = fgetc(fpr);
            if(feof(fpr)) break;
            string[count] = c;
            count++;
        }
        fclose(fpr);
        int flag = 1, flag2 = 0;
        for (int i = 0 ; i <= strlen(string) - strlen(message) ; i++)
        {
            flag = 1;
            for (int j = i ; j < i + strlen(message) ; j++){
                if (string[j] != message[j - i]) flag = 0;
            }
            if (flag == 1){
                num_count++;
            }
        }
        printf("%d\n", num_count);
        return;
    }
    if (fall == 1)
    {
        if (fbyword == 1)
        {
            int c, count = 0;
            while(1)
            {
                c = fgetc(fpr);
                if(feof(fpr)) break;
                string[count] = c;
                count++;
            }
            fclose(fpr);
            int flag = 1, flag2 = 0;
            for (int i = 0 ; i <= strlen(string) - strlen(message) ; i++)
            {
                flag = 1;
                if (string[i] == ' ' || string[i] == '\n') num_of_words++;
                for (int j = i ; j < i + strlen(message) ; j++){
                    if (string[j] != message[j - i]) flag = 0;
                }
                if (flag == 1){
                    flag2 = 1;
                    printf("%d, ", num_of_words);
                }
            }
            if (flag2 == 0) printf("%d", -1);
            printf("\n");
            return;
        }
        else
        {
           int c, count = 0;
            while(1)
            {
                c = fgetc(fpr);
                if(feof(fpr)) break;
                string[count] = c;
                count++;
            }
            fclose(fpr);
            int flag = 1, flag2 = 0;
            for (int i = 0 ; i <= strlen(string) - strlen(message) ; i++)
            {
                flag = 1;
                for (int j = i ; j < i + strlen(message) ; j++){
                    if (string[j] != message[j - i]) flag = 0;
                }
                if (flag == 1){
                    flag2 = 1;
                    printf("%d, ", i);
                }
            }
            if (flag2 == 0) printf("%d", -1);
            printf("\n");
            return; 
        }
    }
    if (fbyword == 1 && fall == 0 && fat == 0)
    {
        int c, count = 0;
        while(1)
        {
            c = fgetc(fpr);
            if(feof(fpr)) break;
            string[count] = c;
            count++;
        }
        fclose(fpr);
        int flag = 1, flag2 = 0;
        for (int i = 0 ; i <= strlen(string) - strlen(message) ; i++)
        {
            flag = 1;
            if (i != 0 && (string[i - 1] != ' ' && string[i - 1] != '\n') && (string[i] == ' ' || string[i] == '\n')) num_of_words++;
            for (int j = i ; j < i + strlen(message) ; j++){
                if (string[j] != message[j - i]) flag = 0;
            }
            if (flag == 1){
                flag2 = 1;
                printf("%d\n", num_of_words);
                break;
            }
        }
        if (flag2 == 0) printf("%d\n", -1);
        return;
    }
    if (fat == 1)
    {
        if (fbyword == 0)
        {
            int c, count = 0;
            while(1)
            {
                c = fgetc(fpr);
                if(feof(fpr)) break;
                string[count] = c;
                count++;
            }
            fclose(fpr);
            int flag = 1, flag2 = 0;
            for (int i = 0 ; i <= strlen(string) - strlen(message) ; i++)
            {
                flag = 1;
                for (int j = i ; j < i + strlen(message) ; j++){
                    if (string[j] != message[j - i]) flag = 0;
                }
                if (flag == 1){
                    num_count++;
                    if (num_at == num_count) {printf("%d\n", i); break;}
                }
            }
            if (num_at > num_count) printf("%d\n", -1);
            return; 
        }
        else
        {
            int c, count = 0;
            while(1)
            {
                c = fgetc(fpr);
                if(feof(fpr)) break;
                string[count] = c;
                count++;
            }
            fclose(fpr);
            int flag = 1, flag2 = 0;
            for (int i = 0 ; i <= strlen(string) - strlen(message) ; i++)
            {
                flag = 1;
                if (i != 0 && (string[i - 1] != ' ' && string[i - 1] != '\n') && (string[i] == ' ' || string[i] == '\n')) num_of_words++;
                for (int j = i ; j < i + strlen(message) ; j++){
                    if (string[j] != message[j - i]) flag = 0;
                }
                if (flag == 1){
                    num_count++;
                    if (num_at == num_count) {printf("%d\n", num_of_words); break;}
                }
            }
            if (num_at > num_count) printf("%d\n", -1);
            return;
        }
    }
    return;
}

void replace()
{
    char option[100];
    char message[MAX_VAL], message2[MAX_VAL], filename[MAX_VAL], string[MAX_VAL] = {};
    int fcount = 0, fat = 0, fbyword = 0, fall = 0, flag_op;
    int num_at, num_count = 0;
    scanf(" --%s", option);
    scanf("%c", &vc);
    getting(message);
    scanf(" --%s", option);
    scanf("%c", &vc);
    getting(message2);
    scanf(" --%s", option);
    scanf("%c", &vc);
    flag_op = getting_find(filename);
    if (filename[0] == '/'){
        for (ll i = 1 ; i < strlen(filename) ; i++){
            filename[i - 1] = filename[i];
        }
        filename[strlen(filename) - 1] = '\0';
    }
    options_find(&fcount, &fat, &fbyword, &fall, &flag_op, &num_at);
    FILE *fpr;
    fpr = fopen(filename, "r");
    if (fall == 1 && fat == 1) {printf("Invalid set of options\n"); return;}
    if (fall == 0 && fat == 0)
    {
        int c, count = 0;
        while(1)
        {
            c = fgetc(fpr);
            if(feof(fpr)) break;
            string[count] = c;
            count++;
        }
        fclose(fpr);
        int flag = 1, flag2 = 0;
        for (int i = 0 ; i <= strlen(string) - strlen(message) ; i++)
        {
            flag = 1;
            for (int j = i ; j < i + strlen(message) ; j++){
                if (string[j] != message[j - i]) flag = 0;
            }
            if (flag == 1){
                flag2 = 1;
                removestr_u(filename, i, strlen(message), "f");
                insertstr_u(filename, message2, i);
                break;
            }
        }
        if (flag2 == 0) printf("Not found\n");
        return;
    }
    if (fall == 1)
    {
        int c, count = 0;
        while(1)
        {
            c = fgetc(fpr);
            if(feof(fpr)) break;
            string[count] = c;
            count++;
        }
        fclose(fpr);
        int flag = 1, flag2 = 0;
        for (int i = 0 ; i <= strlen(string) - strlen(message) ; i++)
        {
            flag = 1;
            for (int j = i ; j < i + strlen(message) ; j++){
                if (string[j] != message[j - i]) flag = 0;
            }
            if (flag == 1){
                flag2 = 1;
                removestr_u(filename, i, (int) strlen(message), "f");
                insertstr_u(filename, message2, i);
                fpr = fopen(filename, "r");
                count = 0;
                while(1)
                {
                    c = fgetc(fpr);
                    if(feof(fpr)) break;
                    string[count] = c;
                    count++;
                }
                fclose(fpr);
            }
        }
        if (flag2 == 0) printf("Not found\n");
        return;
    }
    if (fat == 1)
    {
        int c, count = 0;
        while(1)
        {
            c = fgetc(fpr);
            if(feof(fpr)) break;
            string[count] = c;
            count++;
        }
        fclose(fpr);
        int flag = 1, flag2 = 0;
        for (int i = 0 ; i <= strlen(string) - strlen(message) ; i++)
        {
            flag = 1;
            for (int j = i ; j < i + strlen(message) ; j++){
                if (string[j] != message[j - i]) flag = 0;
            }
            if (flag == 1){
                num_count++;
                if (num_count == num_at)
                {
                    flag2 = 1;
                    removestr_u(filename, i, strlen(message), "f");
                    insertstr_u(filename, message2, i);
                    break;
                }
            }
        }
        if (flag2 == 0) printf("Not found\n");
        return;
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
        else if (strcmp(command, "insertstr") == 0) insertstr();
        else if (strcmp(command, "removestr") == 0) removestr();
        // else if (strcmp(command, "copystr") == 0) copystr();
        // else if (strcmp(command, "pastestr") == 0) pastestr();
        // else if (strcmp(command, "cutstr") == 0) cutstr();
        else if (strcmp(command, "find") == 0) find();
        else if (strcmp(command, "replace") == 0) replace();
        else {scanf("%[^\n]", command);printf("Invalid input\n");}
    }
    return 0;
}


