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
    make_copy(filename);
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
    scanf(" -%s", option);
    scanf(" %d", &sz);
    scanf(" -%s", option);
    if (filename[0] == '/'){
        for (ll i = 1 ; i < strlen(filename) ; i++){
            filename[i - 1] = filename[i];
        }
        filename[strlen(filename) - 1] = '\0';
    }
    make_copy(filename);
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
    scanf(" -%s", option);
    scanf(" %d", &sz);
    scanf(" -%s", option);
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
    scanf(" -%s", option);
    scanf(" %d", &sz);
    scanf(" -%s", option);
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
    // make_copy(filename);
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

void undo_file()
{
    char filename[MAX_VAL], option[100], string[MAX_VAL] = {'\0'};
    scanf(" --%s", option);
    scanf("%c", &vc);
    getting(filename);
    if (filename[0] == '/'){
        for (ll i = 1 ; i < strlen(filename) ; i++){
            filename[i - 1] = filename[i];
        }
        filename[strlen(filename) - 1] = '\0';
    }
    //make_copy(filename);
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
    FILE *fp;
    fp = fopen(filename, "r");
    if (fp == NULL) {printf("File not found\n"); return;}
    fclose(fp);
    fp = fopen(filename2, "r");
    int k, counter = 0;
    while (1)
    {
        k = fgetc(fp);
        string[counter] = k;
        if (k == EOF) break;
        counter++;
    }
    fclose(fp);
    make_copy(filename);
    FILE *fp2;
    fp2 = fopen(filename, "w");
    int c;
    counter = 0;
    while (1)
    {
        c = string[counter];
        if (c == EOF) break;
        fputc(c, fp2); 
        counter++;
    }
    fclose(fp2);
    return;
}

void compare()
{
    char filename1[MAX_VAL], filename2[MAX_VAL];
    scanf("%c", &vc);
    getting(filename1);
    scanf("%c", &vc);
    getting(filename2);
    if (filename1[0] == '/'){
        for (ll i = 1 ; i < strlen(filename1) ; i++){
            filename1[i - 1] = filename1[i];
        }
        filename1[strlen(filename1) - 1] = '\0';
    }
    if (filename2[0] == '/'){
        for (ll i = 1 ; i < strlen(filename2) ; i++){
            filename2[i - 1] = filename2[i];
        }
        filename2[strlen(filename2) - 1] = '\0';
    }
    FILE *fpr1, *fpr2;
    fpr1 = fopen(filename1, "r");
    fpr2 = fopen(filename2, "r");
    if (fpr1 == NULL || fpr2 == NULL) {printf("File not found\n"); return;}
    char string1[MAX_VAL], string2[MAX_VAL];
    int line_num = 0, t;
    while (1)
    {
        line_num++;
        t = getting_cmp(fpr1, fpr2, string1, string2);
        if (strcmp(string1, string2) != 0)
        {
            printf("=============#%d==============\n", line_num);
            printf("%s\n%s\n", string1, string2);
        }
        if (t == 3) break;
        if (t == 1)
        {
            int start = line_num + 1;
            int c, counter = 0;
            empty(string2);
            while (1)
            {
                c = fgetc(fpr2);
                if (c == '\n') line_num++;
                if (c == EOF) break;
                string2[counter] = c;
                counter++;
            }
            printf(">>>>>>>>>>>>#%d-#%d>>>>>>>>>>>>\n", start, line_num);
            printf("%s", string2);
            break;
        }
        if (t == 2)
        {
            int start = line_num + 1;
            int c, counter = 0;
            empty(string1);
            while (1)
            {
                c = fgetc(fpr1);
                if (c == '\n') line_num++;
                if (c == EOF) break;
                string1[counter] = c;
                counter++;
            }
            printf("<<<<<<<<<<<<#%d-#%d<<<<<<<<<<<<\n", start, line_num);
            printf("%s", string1);
            break;
        }
    }
    fclose(fpr1);
    fclose(fpr2);
}

void grep()
{
    char option[100], text[MAX_VAL], string[MAX_VAL], filename[MAX_VAL];
    char filenames[10][MAX_VAL];
    int flag_op;
    scanf(" --%s", option);
    scanf("%c", &vc);
    getting(text);
    scanf(" --%s", option);
    scanf("%c", &vc);
    FILE *fpr;
    int counter_files = 0, f_c = 0, f_l = 0, num_match = 0;
    while (vc != '\n')
    {
        flag_op = getting_find(filename);
        if (filename[0] == '-')
        {
            if (flag_op == -1) {printf("Invalid input\n"); return;}
            if (flag_op == 1) {printf("Invalid option\n"); scanf("%[^\n]", option); return;}
            if (strcmp(filename, "-c") == 0) {f_c = 1; break;}
            else if (strcmp(filename, "-l") == 0) {f_l = 1; break;}
            else {printf("Invalid option\n"); return;}
        }
        if (filename[0] == '/'){
            for (ll i = 1 ; i < strlen(filename) ; i++){
                filename[i - 1] = filename[i];
            }
            filename[strlen(filename) - 1] = '\0';
        }
        strcpy(filenames[counter_files], filename);
        counter_files++;
        if (flag_op == 0) break;
        if (flag_op == -1) scanf("%c", &vc);
    }
    for (int i = 0 ; i < counter_files ; i++)
    {
        fpr = fopen(filenames[i], "r");
        empty(string);
        int c, counter = 0;
        while (1)
        {
            c = fgetc(fpr);
            if (feof(fpr)) break;
            string[counter] = (char)c;
            counter++;
        }
        int flag_check = 1;
        int line_num = 1, prev_line_num = 0;
        for (int j = 0 ; j <= strlen(string) - strlen(text) ; j++)
        {
            if (string[j] == '\n') line_num++;
            flag_check = 1;
            for (int k = j ; k < j + strlen(text) ; k++)
            {
                if (string[k] != text[k - j]) {flag_check = 0; break;}
            }
            if (flag_check == 1)
            {
                if (f_c == 0 && f_l == 0 && line_num != prev_line_num) {char output[MAX_VAL]; get_a_line(filenames[i], line_num, output);
                printf("%s: %s\n", filenames[i], output); prev_line_num = line_num;}
                if (f_c == 0 && f_l == 1) {printf("%s\n", filenames[i]); break;}
                if (f_c == 1) num_match++;
            }
        }
        fclose(fpr);
    }
    if (f_c == 1) printf("%d\n", num_match);
    return;
}

void closing_pair()
{
    char filename[MAX_VAL], option[100];
    scanf(" --%s", option);
    scanf("%c", &vc);
    getting(filename);
    if (filename[0] == '/'){
        for (ll i = 1 ; i < strlen(filename) ; i++){
            filename[i - 1] = filename[i];
        }
        filename[strlen(filename) - 1] = '\0';
    }
    FILE *fpr, *fp;
    fpr = fopen(filename, "r");
    int c, counter_pair = 0;
    while (1)
    {
        c = fgetc(fpr);
        if (feof(fpr)) break;
        if (c == '{') counter_pair++;
        else if (c == '}') counter_pair--;
    }
    fclose(fpr);
    if (counter_pair != 0) return;
    int start = 0 , end = 0, prev_start = MAX_VAL, prev_end[100], sz = -1;
    for (int i = 0 ; i < 100 ; i++) prev_end[i] = -1;
    while (1)
    {
        fpr = fopen(filename, "r");
        printf("Ghabl:\n");
        while (1)
        {
            c = fgetc(fpr);
            if (feof(fpr)) break;
            printf("%c", c);
        }
        fclose(fpr);
        printf("\n\n");
        sz++;
        int check = first_last(filename, &start, &end, &prev_start, prev_end, &sz);
        if (check == 0) break;
        printf("%d %d\n", start, end);
        fix_indent(filename, start, end, &prev_start, prev_end, sz);
        fpr = fopen(filename, "r");
        printf("Baad:\n");
        while (1)
        {
            c = fgetc(fpr);
            if (feof(fpr)) break;
            printf("%c", c);
        }
        fclose(fpr);
        printf("\n\n");
    }
    return;
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
        else if (strcmp(command, "undo") == 0) undo_file();
        else if (strcmp(command, "compare") == 0) compare();
        else if (strcmp(command, "grep") == 0) grep();
        else if (strcmp(command, "auto-indent") == 0) closing_pair();
        else {scanf("%[^\n]", command);printf("Invalid input\n");}
    }
    return 0;
}


