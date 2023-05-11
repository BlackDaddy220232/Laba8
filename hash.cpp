#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include"hash.h"
#include<string.h>
#include"menu.h"
int Strlen(char* mas)
{
    int i = 0;
    while (mas[i] != '\0')
    {
        i++;
    }
    return (i);
}
Hash* Delete(Hash* table,char* name,int Size)
{
    Hash* elem;
	if((elem=Search(table,name,Size))==NULL)
	{
        return NULL;
	}
    else
    {
        free(elem->login);
        free(elem->password);
        elem->empty=true;
    }
}
Hash* Change(Hash* table,char* name, char* password,int Size)
{
	Hash* elem;
	if((elem=Search(table,name,Size))==NULL)
	{
        return NULL;
	}
	else{
		elem->password=(char*)malloc(Strlen(password)+1 * sizeof(char));
        elem->password=password;
	}
}
void HandleCreate(Hash* tabble, char* Login, char* Password,int Size)
{
    Hash* elem = Search(tabble, Login, Size);
	if(elem!=NULL)
	{
        elem->login = Login;
        elem->password = Password;
	}
	unsigned int hash=MurMurHash(Login,Strlen(Login),0,Size);
	if(tabble[hash].empty==true)
	{
		tabble[hash].login =(char*)malloc(Strlen(Login)+1 * sizeof(char));
        tabble[hash].password = (char*)malloc(Strlen(Password)+1 * sizeof(char));
		strcpy(tabble[hash].login, Login);
        strcpy(tabble[hash].password, Password);
        tabble[hash].empty = false;
	}
	else{
		tabble[hash].next=CollisionSolver(Login,Password,tabble[hash].next);
	}

}
void Create(Hash* tabble, FILE* file,int Size)
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
            hashkey = MurMurHash(Login, Strlen(Login), 0,Size);
            printf("%lu\n", hashkey);
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
Hash* Search(Hash* Table,char* key,int Size)
{
    Hash* element;
    unsigned int hash;
    hash = MurMurHash(key, Strlen(key), 0,Size);
    if (Table[hash].empty != true)
    {
        if ((strcmp(Table[hash].login, key) == 0))//тут ошибка
        {
            return element = &Table[hash];
        }
    }
    else
    {
        element=SearchinList(Table[hash].next, key);
		return element;
    }
    return NULL;
}
Hash* SearchinList(Hash* head, char* key)
{
     Hash* current = head;

    while (current != NULL) {
        if (strcmp(current->login,key)==0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}
Hash* CollisionSolver(char* login, char* passsword, Hash *head)
{
    Hash* tmp = (Hash*)malloc(sizeof(Hash));
    tmp->login = (char*)malloc(Strlen(login)+1*sizeof(char));
    tmp->password = (char*)malloc(Strlen(passsword)+1*sizeof(char));
    strcpy(tmp->login, login);
    strcpy(tmp->password, passsword);
    tmp->empty = false;
    tmp->next = head;
    return tmp;
}
char* GetLogin(char* mas)
{
    int i = 0;
    int j = 1;
    char* buf = (char*)malloc(j * sizeof(char));
    while (mas[i]!='=')
    {
        buf[i] = mas[i];
        j++;
        buf = (char*)realloc(buf, j);
        i++;
    }
    buf[i] = '\0';
    return buf;
}
char* GetPassword(char* mas)
{
    int i = 0;
    int k = 0;
    int j = 1;
    int fl = 0;
    char* buf = (char*)malloc(j * sizeof(char));
    while (mas[k] != '\0')
    {
        if (fl == 1)
        {
            buf[i] = mas[k];
            j++;
            buf = (char*)realloc(buf, j);
            i++;
        }
        if (mas[k] == '=') fl = 1;
        k++;
    }
    buf[i] = '\0';
    return buf;
}
unsigned int MurMurHash(char* key, unsigned int length, unsigned int seed,int Size)
{
    const unsigned int bestnumber = 0x5bd1e995; //число 1540483477, эксперементально подобранно для улучшения оптимизации и распределения, вроде бы близко к золотому сечению
    const int r = 24;//тоже эксперементально, для того чтобы разбросать наши биты в части числа
    unsigned int h = seed ^ length;//наш хэш, XOR
    const unsigned char *data = (const unsigned char*)key; //присваеваем указателю наш ключ
    unsigned int k = 0;
    while (length >= 4)
    {//сам алгоритм MURMUR
        k = data[0];
        k |= data[1] << 8;
        k |= data[2] << 16;
        k |= data[3] << 24;
        k*= bestnumber;
        k ^= k >> r;
        k *= bestnumber;
        h *= bestnumber;
        h ^= k;
        data += 4; //сдвиг на 4 байта указатель
        length -= 4;
    }
    switch (length)//для оставшихся 3 байтов
    {
    case 1:
        h ^= data[0];
        h *= bestnumber;
        break;
    case 2:
        h ^= data[1] << 8;
        break;
    case 3:
        h ^= data[2] << 16;
        break;
    }
    h ^= h >> 13;
    h *= bestnumber;
    h ^= h >> 15;
    return h%Size;
}