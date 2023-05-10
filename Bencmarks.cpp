#include"hash.h"
#include<unordered_map>
void Create(Hash* tabble, FILE* file)
{
    char a;
    char* mas= (char*)malloc(1 * sizeof(char));
    char* Login = NULL;
    char* password = NULL;
    int i = 0;
    int j = 0;
    unsigned int hashkey;
    while ((a=getc(file))!=EOF)
    {
        mas[i] = a;
        i++;
        mas = (char*)realloc(mas, i+1);
        if (a == '\n')
        {
            mas[i] = '\0';
            Login=GetLogin(mas);
            password=GetPassword(mas);
            hashkey = MurMurHash(Login, Strlen(Login), 0);
            if (tabble[hashkey].empty == true)
            {
                tabble[hashkey].login =(char*)malloc(Strlen(Login)+1 * sizeof(char));
                tabble[hashkey].password = (char*)malloc(Strlen(password)+1 * sizeof(char));
                strcpy(tabble[hashkey].login, Login);
                strcpy(tabble[hashkey].password, password);
                tabble[hashkey].empty = false;
            }
            else {
                tabble[hashkey].next = CollisionSolver(Login, password, tabble[hashkey].next);
            }
            i = 0;
        }
    }
}