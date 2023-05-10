#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include"hash.h"
#include"menu.h"
#include"intcheck.h"
#include<unordered_map>
#include<iostream>
int main()
{
    FILE* file;
    file = fopen("password.txt", "r");
    if (!file)
    {
        printf("Not found file");
    }
    Hash* HashTabble;
    printf("Input size of tabble");
	HashTabble = (Hash*)malloc(400* sizeof(Hash));
    for (int  i = 0; i < 400; i++)
    {
        HashTabble[i].empty = true;
        HashTabble[i].next = NULL;
    }
    std::unordered_map<char*,char*> TabbleVSTR;
    Create(HashTabble, file);
	Menu(HashTabble);
}