#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include "help_func.h"

#define ll long long int
#define MAX_VAL 10000

FILE *fout;

char filenames[MAX_VAL][MAX_VAL];

void get_word(char *input, char *word , int *counter_input, int *counter_word);
void get_pos(char *word, int *line, int *start);
int char_to_num(char *s);

void re_files(char path[])
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
            if (fp != NULL) {fprintf(fout, "%s", "file is already existing\n"); fclose(fp); return;}
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

void re_creatfile(char *path)
{
    re_files(path);
    return;
}

void re_cat(char *filename)
{
    if (filename[0] == '/'){
        for (ll i = 1 ; i < strlen(filename) ; i++){
            filename[i - 1] = filename[i];
        }
        filename[strlen(filename) - 1] = '\0';
    }
    FILE *fp;
    fp = fopen(filename, "r");
    if (fp == NULL){fprintf(fout, "%s", "file not found\n"); return;}
    int c;
    while(1)
    {
        c = fgetc(fp);
        if(feof(fp)) break;
        fprintf(fout, "%c", c);
    }
    fclose(fp);
    return;
}

void re_insertstr(char *filename, char *message, int line, int start)
{
    if (filename[0] == '/'){
        for (ll i = 1 ; i < strlen(filename) ; i++){
            filename[i - 1] = filename[i];
        }
        filename[strlen(filename) - 1] = '\0';
    }
    make_copy(filename);
    FILE *fp, *fpr;
    fpr = fopen(filename, "r");
    if (fpr == NULL){fprintf(fout, "%s", "file not found\n"); return;}
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

void re_removestr(char *filename, int line, int start, int sz, char *option)
{
    if (filename[0] == '/'){
        for (ll i = 1 ; i < strlen(filename) ; i++){
            filename[i - 1] = filename[i];
        }
        filename[strlen(filename) - 1] = '\0';
    }
    make_copy(filename);
    FILE *fp, *fpr;
    fpr = fopen(filename, "r");
    if (fpr == NULL){fprintf(fout, "%s", "file not found\n"); return;}
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
    if (strcmp(option, "-f") == 0)
    {
        int to = position + sz;
        for (int i = 0 ; i < position ; i++) fprintf(fp, "%c", string[i]);
        for (int i = to ; i < strlen(string) ; i++) fprintf(fp, "%c", string[i]);
    }
    else if (strcmp(option, "-b") == 0)
    {
        int from = position - sz;
        for (int i = 0 ; i <= from ; i++) fprintf(fp, "%c", string[i]);
        for (int i = position + 1 ; i < strlen(string) ; i++) fprintf(fp, "%c", string[i]);
    }
    fclose(fp);
    return;
}

void re_copy(char *filename, int line, int start, int sz, char *option)
{
    if (filename[0] == '/'){
        for (ll i = 1 ; i < strlen(filename) ; i++){
            filename[i - 1] = filename[i];
        }
        filename[strlen(filename) - 1] = '\0';
    }
    FILE *fpr, *fp_clip;
    fpr = fopen(filename, "r");
    if (fpr == NULL){fprintf(fout, "%s", "file not found\n"); return;}
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
    }
    fclose(fpr);
    position += start;
    fpr = fopen(filename, "r");
    fp_clip = fopen(".clipboard.txt", "w+");
    fseek(fpr, position, SEEK_SET);
    if (strcmp(option, "-f") == 0)
    {
        for (int i = 0 ; i < sz ; i++)
        {
            c = fgetc(fpr);
            fputc(c, fp_clip);
        }
    }
    else if (strcmp(option, "-b") == 0)
    {
        fseek(fpr, -sz + 1, SEEK_CUR);
        for (int i = 0 ; i < sz ; i++)
        {
            c = fgetc(fpr);
            fputc(c, fp_clip);
        }
    }
    fclose(fpr);
    fclose(fp_clip);
}

void re_cut(char *filename, int line, int start, int sz, char *option)
{
    if (filename[0] == '/'){
        for (ll i = 1 ; i < strlen(filename) ; i++){
            filename[i - 1] = filename[i];
        }
        filename[strlen(filename) - 1] = '\0';
    }
    FILE *fpr;
    fpr = fopen(filename, "r");
    if (fpr == NULL){fprintf(fout, "%s", "file not found\n"); return;}
    fclose(fpr);
    re_copy(filename, line, start, sz, option);
    re_removestr(filename, line, start, sz, option);
}

void re_paste(char *filename, int line, int start)
{
    char message[MAX_VAL];
    int counter_mes = 0;
    FILE *fp_clip;
    fp_clip = fopen(".clipboard.txt", "r");
    int c;
    while (1)
    {
        c = fgetc(fp_clip);
        if (feof(fp_clip)) break;
        message[counter_mes] = c;
        counter_mes++;
    }
    fclose(fp_clip);
    re_insertstr(filename, message, line, start);
}

void re_find(char *filename, char *message, int fcount, int fat, int fbyword, int fall, int num_at)
{
    char string[MAX_VAL] = {};
    int num_of_words = 1, num_count = 0;
    if (filename[0] == '/'){
        for (ll i = 1 ; i < strlen(filename) ; i++){
            filename[i - 1] = filename[i];
        }
        filename[strlen(filename) - 1] = '\0';
    }
    FILE *fpr;
    fpr = fopen(filename, "r");
    if (fpr == NULL) {fprintf(fout, "%s", "file not found\n"); return;}
    if (fcount == 1 && fall + fat + fbyword != 0) {fprintf(fout, "%s", "Invalid set of options\n"); return;}
    if (fall == 1 && fat == 1) {fprintf(fout, "%s", "Invalid set of options\n"); return;}
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
                fprintf(fout, "%d\n", i);
                break;
            }
        }
        if (flag2 == 0) fprintf(fout, "%d\n", -1);
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
        fprintf(fout, "%d\n", num_count);
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
                    fprintf(fout, "%d, ", num_of_words);
                }
            }
            if (flag2 == 0) fprintf(fout, "%d", -1);
            fprintf(fout, "\n");
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
                    fprintf(fout, "%d, ", i);
                }
            }
            if (flag2 == 0) fprintf(fout, "%d", -1);
            fprintf(fout, "\n");
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
                fprintf(fout, "%d\n", num_of_words);
                break;
            }
        }
        if (flag2 == 0) fprintf(fout, "%d\n", -1);
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
                    if (num_at == num_count) {fprintf(fout, "%d\n", i); break;}
                }
            }
            if (num_at > num_count) fprintf(fout, "%d\n", -1);
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
                    if (num_at == num_count) {fprintf(fout, "%d\n", num_of_words); break;}
                }
            }
            if (num_at > num_count) fprintf(fout,"%d\n", -1);
            return;
        }
    }
    return;
}

void re_replace(char *filename, char *message, char *message2, int fat, int fall, int num_at)
{
    char string[MAX_VAL] = {};
    int num_count = 0;
    if (filename[0] == '/'){
        for (ll i = 1 ; i < strlen(filename) ; i++){
            filename[i - 1] = filename[i];
        }
        filename[strlen(filename) - 1] = '\0';
    }
    FILE *fpr;
    fpr = fopen(filename, "r");
    if (fall == 1 && fat == 1) {fprintf(fout, "Invalid set of options\n"); return;}
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
        if (flag2 == 0) fprintf(fout, "Not found\n");
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
        if (flag2 == 0) fprintf(fout, "Not found\n");
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
        if (flag2 == 0) fprintf(fout, "Not found\n");
        return;
    }
}

void re_undo_file(char *filename)
{
    char string[MAX_VAL] = {'\0'};
    if (filename[0] == '/'){
        for (ll i = 1 ; i < strlen(filename) ; i++){
            filename[i - 1] = filename[i];
        }
        filename[strlen(filename) - 1] = '\0';
    }
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
    if (fp == NULL) {fprintf(fout, "File not found\n"); return;}
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

void re_compare(char *filename1, char *filename2)
{
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
    if (fpr1 == NULL || fpr2 == NULL) {fprintf(fout, "File not found\n"); return;}
    char string1[MAX_VAL], string2[MAX_VAL];
    int line_num = 0, t;
    while (1)
    {
        line_num++;
        t = getting_cmp(fpr1, fpr2, string1, string2);
        if (strcmp(string1, string2) != 0)
        {
            fprintf(fout, "=============#%d==============\n", line_num);
            fprintf(fout, "%s\n%s\n", string1, string2);
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
            fprintf(fout, ">>>>>>>>>>>>#%d-#%d>>>>>>>>>>>>\n", start, line_num);
            fprintf(fout, "%s", string2);
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
            fprintf(fout, "<<<<<<<<<<<<#%d-#%d<<<<<<<<<<<<\n", start, line_num);
            fprintf(fout, "%s", string1);
            break;
        }
    }
    fclose(fpr1);
    fclose(fpr2);
}

void re_grep(int counter_files, char *text, int f_c, int f_l)
{
    char string[MAX_VAL];
    FILE *fpr;
    int num_match = 0;
    for (int i = 0 ; i < counter_files ; i++)
    {
        if (filenames[i][0] == '/'){
            for (ll j = 1 ; j < strlen(filenames[i]) ; j++){
                filenames[i][j - 1] = filenames[i][j];
            }
            filenames[i][strlen(filenames[i]) - 1] = '\0';
        }
        fpr = fopen(filenames[i], "r");
        if (fpr == NULL) {fprintf(fout, "file not found\n"); return;}
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
                fprintf(fout, "%s: %s\n", filenames[i], output); prev_line_num = line_num;}
                if (f_c == 0 && f_l == 1) {fprintf(fout, "%s\n", filenames[i]); break;}
                if (f_c == 1) num_match++;
            }
        }
        fclose(fpr);
    }
    if (f_c == 1) fprintf(fout, "%d\n", num_match);
    return;
}

void re_closing_pair(char *filename)
{
    if (filename[0] == '/'){
        for (ll i = 1 ; i < strlen(filename) ; i++){
            filename[i - 1] = filename[i];
        }
        filename[strlen(filename) - 1] = '\0';
    }
    make_copy(filename);
    FILE *fpr, *fp;
    fpr = fopen(filename, "r");
    if (fpr == NULL) {fprintf(fout, "File not found\n"); return;}
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
    char string[MAX_VAL], string2[MAX_VAL];
    int level = 0, counter = 0, counter2 = 0;
    fpr = fopen(filename, "r");
    while (1)
    {
        c = fgetc(fpr);
        if (feof(fpr)) break;
        string[counter] = c;
        counter++;
    }
    fclose(fpr);
    int index = 0;
    while (1)
    {
        if (index >= counter) break;
        if (string[index] == '{' && string[index + 1] == '}')
        {
            string2[counter2] = '{';
            counter2++;
            string2[counter2] = '\n';
            counter2++;
            for (int i = 0 ; i < 4 * level ; i++) {string2[counter2] = ' '; counter2++;}
            string2[counter2] = '}';
            counter2++;
            index+=2;
            if (index >= counter) break;
            if (string[index] != '\n')
            {
                string2[counter2] = '\n';
                counter2++;
                for (int i = 0 ; i < 4 * level ; i++) {string2[counter2] = ' '; counter2++;}
            }
            continue;
        }
        if (string[index] == '{')
        {
            string2[counter2] = string[index];
            counter2++;
            level++;
            if (string[index + 1] != '\n'){
                string2[counter2] = '\n';
                counter2++;
                for (int i = 0; i < 4 * level ; i++) {string2[counter2] = ' '; counter2++;}
            }
        }
        else if (string[index] == '}')
        {
            level--;
            if (string[index - 1] != '\n' && string[index - 1] != '}')
            {
                string2[counter2] = '\n';
                counter2++;
                for (int i = 0 ; i < 4 * level ; i++) {string2[counter2] = ' '; counter2++;}
            }
            else if (string[index - 1] != '\n' && string[index - 1] == '}')
            {
                for (int i = 0 ; i < 4 ; i++) {string2[counter2 - 1] = '\0'; counter2--;}
            }
            else if (string[index - 1] == '\n')
            {
                for (int i = 0 ; i < 4 ; i++) {string2[counter2 - 1] = '\0'; counter2--;}
            }
            string2[counter2] = '}';
            counter2++;
            if (index + 1 < counter && string[index + 1] != '\n')
            {
                string2[counter2] = '\n';
                counter2++;
                for (int i = 0 ; i < 4 * level ; i++) {string2[counter2] = ' '; counter2++;}
            }
        }
        else if (string[index] == '\n' && string2[counter2 - 1] != '\n')
        {
            string2[counter2] = '\n';
            counter2++;
            for (int i = 0 ; i < 4 * level ; i++) {string2[counter2] = ' '; counter2++;}
        }
        else if (string[index] == ' ' && (string2[counter2 - 1 - 4*level] == '\n' || string2[counter2 - 1 - 4 * level] == ' '))
        {

        }
        else
        {
            string2[counter2] = string[index];
            counter2++;
        }
        index++;
    }
    char string3[MAX_VAL], counter3 = 0;
    index = 0;
    int flag_space = 1;
    while (index < counter2)
    {
        string3[counter3++] = string2[index];
        if (string2[index] == '\n' && flag_space == 1)
        {
            while (string3[counter3 - 2] != '\n')
            {
                // string3[counter3 - 2] = '\0';
                delete_str(string3, counter3 - 2);
                counter3--;
            }
            // string3[counter3 - 1] = '\0';
            delete_str(string3, counter3 - 1);
            counter3--;
        }
        else if (string2[index] == '\n') flag_space = 1;
        else if (string2[index] != '\n' &&  string2[index] != ' ') flag_space = 0;
        index++;
    }
    index = 0;
    int non_space = 0;
    while (index < counter3)
    {
        if (string3[index] == '\n') non_space = 0;
        else if (string3[index] != ' ' && string3[index] != '{') non_space = 1;
        if (index > 0 && string3[index] == '{' && non_space == 1)
        {
            int i = index;
            while (string3[i - 1] == ' ')
            {
                // string3[i - 1] = '\0';
                delete_str(string3, i - 1);
                counter3--;
                i--;
            }
            {add_str(string3, i, ' '); counter3++;}
        }
        index++;
    }
    fp = fopen(filename, "w");
    for (int i = 0 ; i < counter3 ; i++)
    {
        fputc(string3[i], fp);
    }
    fclose(fp);
    return;
}

void re_tree(char basePath[], const int root, const int depth)
{
    if (root >  2 * depth) return;
    int i;
    char path[1000];
    struct dirent *dp;
    DIR *dir = opendir(basePath);

    if (!dir)
        return;

    while ((dp = readdir(dir)) != NULL)
    {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
        {
            for (i=0; i<root; i++) 
            {
                if (i%2 == 0 || i == 0)
                    fprintf(fout, "%s", "│");
                else
                    fprintf(fout, " ");

            }

            if (dp->d_name[0] != '.') fprintf(fout, "%s%s%s\n", "├", "─", dp->d_name);

            strcpy(path, basePath);
            strcat(path, "/");
            strcat(path, dp->d_name);
            re_tree(path, root + 2, depth);
        }
    }

    closedir(dir);
}

void re_arman(char *input, char *word, int *counter_input, int *counter_word)
{
    char out[MAX_VAL];
    int counter_out = 0;
    fclose(fout);
    fout = fopen(".output.txt", "r");
    int c;
    while (1)
    {
        c = fgetc(fout);
        if (feof(fout)) break;
        out[counter_out] = c;
        counter_out++;
    }
    fclose(fout);
    fout = fopen(".output.txt", "w");
    char command[MAX_VAL], option[MAX_VAL];
    get_word(input, word, &(*counter_input), &(*counter_word));
    strcpy(command, word);
    if (strcmp(command, "exit") == 0);
    else if (strcmp(command , "insertstr") == 0)
    {
        char filename[MAX_VAL] = {};
        int line = -1, start = -1;
        while ((*counter_input) < strlen(input))
        {
            get_word(input, word, &(*counter_input), &(*counter_word));
            strcpy(option, word);
            if (strcmp(option, "--file") == 0)
            {
                get_word(input, word, &(*counter_input), &(*counter_word));
                strcpy(filename, word);
            }
            else if (strcmp(option, "--pos") == 0)
            {
                get_word(input, word, &(*counter_input), &(*counter_word));
                get_pos(word, &line, &start);
            }
            else {fprintf(fout, "Not valid option\n");}
        }
        if (line == -1 || start == -1 || strlen(filename) == 0) {fprintf(fout, "Invalid input\n");}
        re_insertstr(filename, out, line, start);
    }
    else if (strcmp(command, "find") == 0)
    {
        int fcount = 0, fbyword = 0, fat = 0, fall = 0, num_at = -1;
        char filename[MAX_VAL] = {};
        while ((*counter_input) < strlen(input))
        {
            get_word(input, word, &(*counter_input), &(*counter_word));
            strcpy(option, word);
            if (strcmp(option, "--file") == 0)
            {
                get_word(input, word, &(*counter_input), &(*counter_word));
                strcpy(filename, word);
            }
            else if (strcmp(option, "-all") == 0) fall = 1;
            else if (strcmp(option, "-byword") == 0) fbyword = 1;
            else if (strcmp(option, "-count") == 0) fcount = 1;
            else if (strcmp(option, "-at") == 0)
            {
                fat = 1;
                get_word(input, word, &(*counter_input), &(*counter_word));
                num_at = char_to_num(word);
            }
            else {fprintf(fout, "Invalid option\n");}
        }
        if (strlen(filename) == 0) {fprintf(fout, "Invalid input\n");}
        re_find(filename, out, fcount, fat, fbyword, fall, num_at);
    }
    else if (strcmp(command, "grep") == 0)
    {
        int f_c = 0, f_l = 0;
        int counter_filenames = 0;
        while ((*counter_input) < strlen(input))
        {
            get_word(input, word, &(*counter_input), &(*counter_word));
            strcpy(option, word);
            if (strcmp(option, "--str") == 0);
            else if (strcmp(option, "-c") == 0) f_c = 1;
            else if (strcmp(option, "-l") == 0) f_l = 1;
            else if (strcmp(option, "--files") == 0)
            {
                while ((*counter_input) < strlen(input))
                {
                    get_word(input, word, &(*counter_input), &(*counter_word));
                    strcpy(filenames[counter_filenames], word);
                    counter_filenames++;
                }
            }
            else {fprintf(fout, "Invalid option\n");}
        }
        if (counter_filenames == 0) {fprintf(fout, "Invalid input");}
        re_grep(counter_filenames, out, f_c, f_l);
    }
    else {fprintf(fout, "Invalid input\n");}
    int cout;
    fclose(fout);
    fout = fopen(".output.txt", "r");
    while (1)
    {
        cout = fgetc(fout);
        if (cout == EOF) break;
        printf("%c", cout);
    }
    fclose(fout);
}

void get_word(char *input, char *word , int *counter_input, int *counter_word)
{
    empty(word);
    (*counter_word) = 0;
    if (input[*(counter_input)] != '"')
    {
        while(1)
        {
            if (input[(*counter_input)] == ' ' || input[(*counter_input)] == '\n') {(*counter_input)++; break;}
            if (input[(*counter_input)] == '\\')
            {
                if (input[*(counter_input) + 1] == '\\') {word[(*counter_word)] = '\\'; (*counter_word)++; (*counter_input) += 2;}
                else if (input[*(counter_input) + 1] == 'n') {word[(*counter_word)] = '\n'; (*counter_word)++; (*counter_input) += 2;}
                else if (input[*(counter_input) + 1] == '"') {word[(*counter_word)] = '\"'; (*counter_word)++; (*counter_input) += 2;}
            }
            else{
                word[(*counter_word)] = input[(*counter_input)];
                (*counter_word)++;
                (*counter_input)++;
            }
        }
    }
    else
    {
        (*counter_input)++;
        while(1)
        {
            if (input[(*counter_input)] == '"') {(*counter_input)+=2; break;}
            if (input[(*counter_input)] == '\\')
            {
                if (input[*(counter_input) + 1] == '\\') {word[(*counter_word)] = '\\'; (*counter_word)++; (*counter_input) += 2;}
                else if (input[*(counter_input) + 1] == 'n') {word[(*counter_word)] = '\n'; (*counter_word)++; (*counter_input) += 2;}
                else if (input[*(counter_input) + 1] == '"') {word[(*counter_word)] = '\"'; (*counter_word)++; (*counter_input) += 2;}
            }
            else{
                word[(*counter_word)] = input[(*counter_input)];
                (*counter_word)++;
                (*counter_input)++;
            }
        }
    }
}

int char_to_num(char *s)
{
    int sum = 0;
    for (int i = 0 ; i < strlen(s) ; i++)
    {
        sum += ((int) s[i] - (int) '0');
        sum*=10;
    }
    return sum / 10;
}

void get_pos(char *word, int *line, int *start)
{
    char s1[10] = {};
    int flag = 0;
    for (int i = 0 ; i < strlen(word) ; i++)
    {
        if (word[i] == ':')
        {
            (*line) = char_to_num(s1);
            flag = i + 1;
            for (int j = 0 ; j < 10 ; j++) {s1[i] = '\0';}
        }
        else s1[i - flag] = word[i];
    }
    (*start) = char_to_num(s1);
}

int main()
{
    char input[MAX_VAL];
    int counter_input = 0;
    char command[MAX_VAL], word[MAX_VAL], option[MAX_VAL];
    int counter_word = 0, flag_arman = 0;
    while (1)
    {
        flag_arman = 0;
        fout = fopen(".output.txt", "w");
        empty(input);
        counter_input = 0;
        counter_word = 0;
        while (1) // getting the input
        {
            scanf("%c", &input[counter_input++]);
            if (input[counter_input - 1] == '\n') break;
        }
        counter_input = 0;
        get_word(input, word, &counter_input, &counter_word);
        strcpy(command, word);
        if (strcmp(command, "exit") == 0) break;
        else if (strcmp(command, "createfile") == 0)
        {
            get_word(input, word, &counter_input, &counter_word);
            strcpy(option, word);
            if (strcmp(option, "--file") == 0)
            {
                get_word(input, word, &counter_input, &counter_word);
                re_creatfile(word);
            }
        }
        else if (strcmp(command, "cat") == 0)
        {
            get_word(input, word, &counter_input, &counter_word);
            strcpy(option, word);
            if (strcmp(option, "--file") == 0)
            {
                get_word(input, word, &counter_input, &counter_word);
                re_cat(word);
            }
            while (counter_input < strlen(input))
            {
                get_word(input, word, &counter_input, &counter_word);
                if (strcmp(word, "=D") == 0)
                {
                    flag_arman = 1;
                    re_arman(input, word, &counter_input, &counter_word);
                }
            }
        }
        else if (strcmp(command, "insertstr") == 0)
        {
            char filename[MAX_VAL] = {}, message[MAX_VAL] = {};
            int line = -1, start = -1;
            while (counter_input < strlen(input))
            {
                get_word(input, word, &counter_input, &counter_word);
                strcpy(option, word);
                if (strcmp(option, "--file") == 0)
                {
                    get_word(input, word, &counter_input, &counter_word);
                    strcpy(filename, word);
                }
                else if (strcmp(option, "--str") == 0)
                {
                    get_word(input, word, &counter_input, &counter_word);
                    strcpy(message, word);
                }
                else if (strcmp(option, "--pos") == 0)
                {
                    get_word(input, word, &counter_input, &counter_word);
                    get_pos(word, &line, &start);
                }
                else {fprintf(fout, "Not valid option\n");}
            }
            if (line == -1 || start == -1 || strlen(filename) == 0 || strlen(message) == 0) {fprintf(fout, "Invalid input\n"); continue;}
            re_insertstr(filename, message, line, start);
        }
        else if (strcmp(command, "removestr") == 0)
        {
            char filename[MAX_VAL], op[5];
            int line = -1, sz = -1, start = -1;
            while (counter_input < strlen(input))
            {
                get_word(input, word, &counter_input, &counter_word);
                strcpy(option, word);
                if (strcmp(option, "--file") == 0)
                {
                    get_word(input, word, &counter_input, &counter_word);
                    strcpy(filename, word);
                }
                else if (strcmp(option, "--pos") == 0)
                {
                    get_word(input, word, &counter_input, &counter_word);
                    get_pos(word, &line, &start);
                }
                else if (strcmp(option, "-size") == 0)
                {
                    get_word(input, word, &counter_input, &counter_word);
                    sz = char_to_num(word);
                }
                else if (strcmp(option, "-f") == 0 || strcmp(option, "-b") == 0)
                {
                    strcpy(op, option);
                }
                else {fprintf(fout, "Not valid option\n");}
            }
            if (line == -1 || start == -1 || sz == -1 || strlen(filename) == 0 || strlen(op) == 0) {fprintf(fout, "Invalid input\n"); continue;}
            re_removestr(filename, line, start, sz, op);
        }
        else if (strcmp(command, "undo") == 0)
        {
            get_word(input, word, &counter_input, &counter_word);
            strcpy(option, word);
            if (strcmp(option, "--file") == 0)
            {
                get_word(input, word, &counter_input, &counter_word);
                re_undo_file(word);
            }
        }
        else if (strcmp(command, "tree") == 0)
        {
            get_word(input, word, &counter_input, &counter_word);
            re_tree("root", 0, char_to_num(word));
            while (counter_input < strlen(input))
            {
                get_word(input, word, &counter_input, &counter_word);
                if (strcmp(word, "=D") == 0)
                {
                    flag_arman = 1;
                    re_arman(input, word, &counter_input, &counter_word);
                }
            }
        }
        else if (strcmp(command, "compare") == 0)
        {
            char filename1[MAX_VAL], filename2[MAX_VAL];
            get_word(input, word, &counter_input, &counter_word);
            strcpy(filename1, word);
            get_word(input, word, &counter_input, &counter_word);
            strcpy(filename2, word);
            re_compare(filename1, filename2);
            while (counter_input < strlen(input))
            {
                get_word(input, word, &counter_input, &counter_word);
                if (strcmp(word, "=D") == 0)
                {
                    flag_arman = 1;
                    re_arman(input, word, &counter_input, &counter_word);
                }
            }
        }
        else if (strcmp(command, "auto-indent") == 0)
        {
            get_word(input, word, &counter_input, &counter_word);
            re_closing_pair(word);
        }
        else if (strcmp(command, "find") == 0)
        {
            int fcount = 0, fbyword = 0, fat = 0, fall = 0, num_at = -1;
            char filename[MAX_VAL] = {}, message[MAX_VAL] = {};
            while (counter_input < strlen(input))
            {
                get_word(input, word, &counter_input, &counter_word);
                strcpy(option, word);
                if (strcmp(option, "--file") == 0)
                {
                    get_word(input, word, &counter_input, &counter_word);
                    strcpy(filename, word);
                }
                else if (strcmp(option, "--str") == 0)
                {
                    get_word(input, word, &counter_input, &counter_word);
                    strcpy(message, word);
                }
                else if (strcmp(option, "-all") == 0) fall = 1;
                else if (strcmp(option, "-byword") == 0) fbyword = 1;
                else if (strcmp(option, "-count") == 0) fcount = 1;
                else if (strcmp(option, "-at") == 0)
                {
                    fat = 1;
                    get_word(input, word, &counter_input, &counter_word);
                    num_at = char_to_num(word);
                }
                else {fprintf(fout, "Invalid option\n");}
            }
            if (strlen(filename) == 0 || strlen(message) == 0) {fprintf(fout, "Invalid input\n"); continue;}
            re_find(filename, message, fcount, fat, fbyword, fall, num_at);
            while (counter_input < strlen(input))
            {
                get_word(input, word, &counter_input, &counter_word);
                if (strcmp(word, "=D") == 0)
                {
                    flag_arman = 1;
                    re_arman(input, word, &counter_input, &counter_word);
                }
            }
        }
        else if (strcmp(command, "replace") == 0)
        {
            int fall = 0, fat = 0, num_at = -1;
            char filename[MAX_VAL] = {}, message1[MAX_VAL] = {}, message2[MAX_VAL] = {};
            while (counter_input < strlen(input))
            {
                get_word(input, word, &counter_input, &counter_word);
                strcpy(option, word);
                if (strcmp(option, "--file") == 0)
                {
                    get_word(input, word, &counter_input, &counter_word);
                    strcpy(filename, word);
                }
                else if (strcmp(option, "--str1") == 0)
                {
                    get_word(input, word, &counter_input, &counter_word);
                    strcpy(message1, word);
                }
                else if (strcmp(option, "--str2") == 0)
                {
                    get_word(input, word, &counter_input, &counter_word);
                    strcpy(message2, word);
                }
                else if (strcmp(option, "-all") == 0) fall = 1;
                else if (strcmp(option, "-at") == 0)
                {
                    fat = 1;
                    get_word(input, word, &counter_input, &counter_word);
                    num_at = char_to_num(word);
                }
                else {fprintf(fout, "Invalid option\n");}
            }
            if (strlen(filename) == 0 || strlen(message1) == 0 || strlen(message2) == 0) {fprintf(fout, "Invalid input\n"); continue;}
            re_replace(filename, message1, message2, fat, fall, num_at);
            while (counter_input < strlen(input))
            {
                get_word(input, word, &counter_input, &counter_word);
                if (strcmp(word, "=D") == 0)
                {
                    flag_arman = 1;
                    re_arman(input, word, &counter_input, &counter_word);
                }
            }
        }
        else if (strcmp(command, "grep") == 0)
        {
            int f_c = 0, f_l = 0;
            char message[MAX_VAL];
            int counter_filenames = 0;
            while (counter_input < strlen(input))
            {
                get_word(input, word, &counter_input, &counter_word);
                strcpy(option, word);
                if (strcmp(option, "--str") == 0)
                {
                    get_word(input, word, &counter_input, &counter_word);
                    strcpy(message, word);
                }
                else if (strcmp(option, "-c") == 0) f_c = 1;
                else if (strcmp(option, "-l") == 0) f_l = 1;
                else if (strcmp(option, "--files") == 0)
                {
                    while (counter_input < strlen(input))
                    {
                        get_word(input, word, &counter_input, &counter_word);
                        strcpy(filenames[counter_filenames], word);
                        counter_filenames++;
                    }
                }
                else {fprintf(fout, "Invalid option\n");}
            }
            if (strlen(message) == 0 || counter_filenames == 0) {fprintf(fout, "Invalid input"); continue;}
            re_grep(counter_filenames, message, f_c, f_l);
            while (counter_input < strlen(input))
            {
                get_word(input, word, &counter_input, &counter_word);
                if (strcmp(word, "=D") == 0)
                {
                    flag_arman = 1;
                    re_arman(input, word, &counter_input, &counter_word);
                }
            }
        }
        else if (strcmp(command, "copystr") == 0)
        {
            char filename[MAX_VAL], op[MAX_VAL];
            int line = -1, start = -1, sz = -1;
            while (counter_input < strlen(input))
            {
                get_word(input, word, &counter_input, &counter_word);
                strcpy(option, word);
                if (strcmp(option, "--file") == 0)
                {
                    get_word(input, word, &counter_input, &counter_word);
                    strcpy(filename, word);
                }
                else if (strcmp(option, "--pos") == 0)
                {
                    get_word(input, word, &counter_input, &counter_word);
                    get_pos(word, &line, &start);
                }
                else if (strcmp(option, "-size") == 0)
                {
                    get_word(input, word, &counter_input, &counter_word);
                    sz = char_to_num(word);
                }
                else if (strcmp(option, "-f") == 0 || strcmp(option, "-b") == 0) strcpy(op, option);
                else {fprintf(fout, "Invalid option\n");}
            }
            if (line == -1 || start == -1 || strlen(filename) == 0 || strlen(op) == 0) {fprintf(fout, "Invalid input\n"); continue;}
            re_copy(filename, line, start, sz, op);
        }
        else if (strcmp(command, "cutstr") == 0)
        {
            char filename[MAX_VAL], op[MAX_VAL];
            int line = -1, start = -1, sz = -1;
            while (counter_input < strlen(input))
            {
                get_word(input, word, &counter_input, &counter_word);
                strcpy(option, word);
                if (strcmp(option, "--file") == 0)
                {
                    get_word(input, word, &counter_input, &counter_word);
                    strcpy(filename, word);
                }
                else if (strcmp(option, "--pos") == 0)
                {
                    get_word(input, word, &counter_input, &counter_word);
                    get_pos(word, &line, &start);
                }
                else if (strcmp(option, "-size") == 0)
                {
                    get_word(input, word, &counter_input, &counter_word);
                    sz = char_to_num(word);
                }
                else if (strcmp(option, "-f") == 0 || strcmp(option, "-b") == 0) strcpy(op, option);
                else {fprintf(fout, "Invalid option\n");}
            }
            if (line == -1 || start == -1 || strlen(filename) == 0 || strlen(op) == 0) {fprintf(fout, "Invalid input\n"); continue;}
            re_cut(filename, line, start, sz, op);
        }
        else if (strcmp(command, "pastestr") == 0)
        {
            char filename[MAX_VAL];
            int line = -1, start = -1;
            while (counter_input < strlen(input))
            {
                get_word(input, word, &counter_input, &counter_word);
                strcpy(option, word);
                if (strcmp(option, "--file") == 0)
                {
                    get_word(input, word, &counter_input, &counter_word);
                    strcpy(filename, word);
                }
                else if (strcmp(option, "--pos") == 0)
                {
                    get_word(input, word, &counter_input, &counter_word);
                    get_pos(word, &line, &start);
                }
                else {fprintf(fout, "Invalid option\n");}
            }
            if (line == -1 || start == -1 || strlen(filename) == 0) {fprintf(fout, "Invalid input\n"); continue;}
            re_paste(filename, line, start);
        }
        else {fprintf(fout, "Invalid input\n");}
        int cout;
        if (flag_arman == 0)
        {
            fclose(fout);
            fout = fopen(".output.txt", "r");
            while (1)
            {
                cout = fgetc(fout);
                if (cout == EOF) break;
                printf("%c", cout);
            }
            fclose(fout);
        }
    }
    return 0;
}