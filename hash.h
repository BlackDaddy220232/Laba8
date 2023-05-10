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
Hash* Delete(Hash* table,char* name);
unsigned int MurMurHash(char* key, unsigned int length, unsigned int seed);
char* GetPassword(char* mas);
char* GetLogin(char* mas);
Hash* CollisionSolver(char* login, char* passsword, Hash* head);
int Strlen(char* mas);
Hash* Search(Hash* Table, char* key);
Hash* SearchinList(Hash* head, char* key);
void Create(Hash* tabble, FILE* file);
void HandleCreate(Hash* tabble, char* Login, char* Password);
Hash* Change(Hash* table,char* name, char* password);