#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ll long long int
#define MAX_VAL 10000

void getting(char *input)
{
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
}



