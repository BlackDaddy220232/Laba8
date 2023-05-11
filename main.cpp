#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<unordered_map>
#include"hash.h"
#include"menu.h"
#include"intcheck.h"
int main()
{
    FILE* file;
    file = fopen("password.txt", "r");
    if (!file)
    {
        printf("Not found file");
    }
    printf("Input size tabble\n");
    int Size = Inputcheck();
    Hash* HashTabble;
	HashTabble = (Hash*)malloc(Size * sizeof(Hash));
    for (int  i = 0; i < Size; i++)
    {
        HashTabble[i].empty = true;
        HashTabble[i].next = NULL;
    }
    Create(HashTabble, file,Size);
	Menu(HashTabble,Size);
}