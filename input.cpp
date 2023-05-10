#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include"input.h"
char* Input()
{
    char* mas;
    int N = 1;
    mas = (char*)malloc(N * sizeof(char));
    int i = 0;
    while ((mas[i] = getchar()) != '\n')
    {
        i++;
        N++;
        mas = (char*)realloc(mas, N * sizeof(char));
    }
    mas[i] = '\0';
    return mas;
}