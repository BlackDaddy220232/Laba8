#include <iostream>
#include <string>
#include <unordered_map>
#include <chrono>
#include <random>
#include <vector>
#include"hash.h"
#include <time.h>
#include"intcheck.h"
using namespace std;
char* Generaterandomstring(int length) {
    char* str = (char*)calloc(length + 1, sizeof(char));
    if (!str)
    {
        printf("Smert");
        exit(1);
    }
    for (int i = 0; i < length; ++i) {
        str[i] = 'a' + rand()%26;
    }
    str[length] = '\0';

    return str;
}

void FillUnorderedMap(unordered_map<char*, char*, std::hash<char*>, std::equal_to<char*>>& login_password_map, const vector<pair<char*, char*>>& data) {
    for (const auto& entry : data) {
        login_password_map[entry.first] = entry.second;
    }
}

void benchmark() {
    srand(time(NULL));
    unordered_map<char*,char*> login_password_map;
    printf("Input number of data:\n");
    int num_entries;
    do
    {
        num_entries = Inputcheck();
        if (num_entries <= 0)
        {
            printf("Invalid number!\n");
        }
    } while (num_entries <= 0);
    vector<pair<char*,char*>> data;
    data.reserve(num_entries);
    for (int i = 0; i < num_entries; ++i) {
        char* login = Generaterandomstring(12); 
        char* password = Generaterandomstring(12); 
        data.emplace_back(login,password);
    }
    printf("Input table size:\n");
    int Size;
    do
    {
        Size = Inputcheck();
        if (Size <= 0)
        {
            printf("Invalid number!\n");
        }
    } while (Size <= 0);
    Hash *mas=(Hash*)malloc(Size*sizeof(Hash));
    for(int i = 0; i < Size; i++){
        mas[i].empty = true;
        mas[i].next = NULL;
    }
    auto start=clock();
    for (const auto& entry:data)
    {
        HandleCreate(mas,entry.first,entry.second,Size);
    }
    auto end=clock();
    long int MyCreate=end-start;
    FillUnorderedMap(login_password_map, data);
    end=clock();
    long int NotMyCreate=end-start;
    start=clock();
    for(const auto& entry: data)
    {
        Search(mas,entry.first,Size);
    }
    end=clock();
    long int MySearch=end-start;
    start = clock();
    for (const auto& entry : data)
    {
        Delete(mas, entry.first,Size);
    }
    end = clock();
    long int MyDelete = end - start;
    start=clock();
    for (auto& entry : login_password_map) {
        delete[] entry.first;
        delete[] entry.second;
    }
    end=clock();
    long int NotMyDelete=end-start;
    start=clock();
    for (const auto& entry: data)
    {
        char* result=login_password_map[entry.first];
    }
    end=clock();
    long int NotMySearch=end-start;
    printf("Write\nMy table\nTime:%ld\nNot my table\nTime:%ld\nK=%lf\n",MyCreate,NotMyCreate,1.0*MyCreate/NotMyCreate);
    printf("Read\nMy table\nTime:%ld\nNot my table\nTime:%ld\nK=%lf\n",MySearch,NotMySearch,1.0*MySearch/NotMySearch);
    printf("Delete\nMy table\nTime:%ld\nNot my table\nTime:%ld\nK=%lf\n",MyDelete,NotMyDelete,1.0*MyDelete/NotMyDelete);
}
