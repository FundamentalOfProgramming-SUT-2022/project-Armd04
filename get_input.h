#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ll long long int
#define MAX_VAL 10000

void getting(char *input)
{
    for (int i = 0 ; i < MAX_VAL ; i++) input[i] = '\0';
    int flag = 0;
    char vc, ghabli;
    ghabli = (char) 5;
    scanf("%c", &vc);
    if (vc != '"')
    {
        int counter = 0;
        while (1)
        {
            if (vc == '\n') break;
            if (vc == ' ') break;
            if (vc == '"') printf("error!\n");
            if (vc == '\\')
            {
                ghabli = vc;
                scanf("%c", &vc);
                if (vc == 'n'){input[counter] = '\n'; counter++;}
                else if (vc == '\\') {input[counter] = '\\'; counter++;}
                else if (vc == '"') {input[counter] = '"'; counter++;}
            }
            else {input[counter] = vc; counter++;}
            ghabli = vc;
            scanf("%c", &vc);
        }
    }
    else{
        int counter = 0;
        scanf("%c", &vc);
        while (1)
        {
            if (vc == '"' && ghabli != '\\') break;
            if (vc == '\\')
            {
                ghabli = vc;
                scanf("%c", &vc);
                if (vc == 'n'){input[counter] = '\n'; counter++;}
                else if (vc == '\\') {input[counter] = '\\'; counter++;}
                else if (vc == '"') {input[counter] = '"'; counter++;}
            }
            else {input[counter] = vc; counter++;}
            ghabli = vc;
            scanf("%c", &vc);
        }
    }
    return;
}

int getting_find(char *input)
{
    for (int i = 0 ; i < MAX_VAL ; i++) input[i] = '\0';
    int flag = 0;
    char vc, ghabli;
    ghabli = (char) 5;
    scanf("%c", &vc);
    if (vc != '"')
    {
        int counter = 0;
        while (1)
        {
            if (vc == '\n') return 0;
            if (vc == ' ') return 1;
            if (vc == '"') printf("error!\n");
            if (vc == '\\')
            {
                ghabli = vc;
                scanf("%c", &vc);
                if (vc == 'n'){input[counter] = '\n'; counter++;}
                else if (vc == '\\') {input[counter] = '\\'; counter++;}
                else if (vc == '"') {input[counter] = '"'; counter++;}
            }
            else {input[counter] = vc; counter++;}
            ghabli = vc;
            scanf("%c", &vc);
        }
    }
    else{
        int counter = 0;
        scanf("%c", &vc);
        while (1)
        {
            if (vc == '"' && ghabli != '\\') break;
            if (vc == '\\')
            {
                ghabli = vc;
                scanf("%c", &vc);
                if (vc == 'n'){input[counter] = '\n'; counter++;}
                else if (vc == '\\') {input[counter] = '\\'; counter++;}
                else if (vc == '"') {input[counter] = '"'; counter++;}
            }
            else {input[counter] = vc; counter++;}
            ghabli = vc;
            scanf("%c", &vc);
        }
        return -1;
    }
}

void options_find(int *fcount, int *fat, int *fbyword, int *fall, int *flag_op, int *num_at)
{
    char option[100], vc;
    if ((*flag_op) == 0) return;
    if ((*flag_op) == -1)
    {
        while (1)
        {
            scanf("%c", &vc);
            if (vc == '\n') return;
            if (scanf("--%s", option) == 0) return;
            if (strcmp(option, "count") == 0) (*fcount) = 1;
            else if (strcmp(option,"at") == 0) {(*fat) = 1; scanf("%d", num_at);}
            else if (strcmp(option, "byword") == 0) (*fbyword) = 1;
            else if (strcmp(option, "all") == 0) (*fall) = 1;
            else printf("Wrong option\n");
        }
        return;
    }
    if ((*flag_op) == 1)
    {
        vc = 'a';
        while (1)
        {
            if (vc == '\n') return;
            scanf("--%s", option);
            if (strcmp(option, "count") == 0) (*fcount) = 1;
            else if (strcmp(option,"at") == 0) {(*fat) = 1; scanf("%d", num_at);}
            else if (strcmp(option, "byword") == 0) (*fbyword) = 1;
            else if (strcmp(option, "all") == 0) (*fall) = 1;
            else printf("Wrong option\n");
            scanf("%c", &vc);
        }
        return;
    }
}


