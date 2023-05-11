#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
typedef struct Hash {
	bool empty;
    char* login;
    char* password;
	Hash* next;
};
Hash* Delete(Hash* table, char* name, int Size);
unsigned int MurMurHash(char* key, unsigned int length, unsigned int seed,int Size);
char* GetPassword(char* mas);
char* GetLogin(char* mas);
Hash* CollisionSolver(char* login, char* passsword, Hash* head);
int Strlen(char* mas);
Hash* Search(Hash* Table, char* key, int Size);
Hash* SearchinList(Hash* head, char* key);
void Create(Hash* tabble, FILE* file, int Size);
void HandleCreate(Hash* tabble, char* Login, char* Password, int Size);
Hash* Change(Hash* table,char* name, char* password, int Size);