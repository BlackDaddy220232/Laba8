#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<unordered_map>
#include"hash.h"
#include"menu.h"
int main()
{
    FILE* file;
    file = fopen("password.txt", "r");
    if (!file)
    {
        printf("Not found file");
    }
    Hash* HashTabble;
	HashTabble = (Hash*)malloc(400 * sizeof(Hash));
    for (int  i = 0; i < 400; i++)
    {
        HashTabble[i].empty = true;
        HashTabble[i].next = NULL;
    }
    Create(HashTabble, file);
	Menu(HashTabble);
}